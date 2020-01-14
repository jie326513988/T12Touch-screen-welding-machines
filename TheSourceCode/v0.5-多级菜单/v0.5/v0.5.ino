#include <TouchScreen.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>
#include <MsTimer2.h>
#include <EEPROM.h>

LCDWIKI_KBV mylcd(ILI9341, A2, A1, 13, A0, 12); //model,cs,cd,wr,rd,resett
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//原始X触摸范围
#define TS_MINX 140
#define TS_MAXX 893
//原始Y触摸范围
#define TS_MINY 98
#define TS_MAXY 870
//原始Z压力范围
#define MINPRESSURE 10
#define MAXPRESSURE 1000
//x+ x-的电阻值
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
// 我们有一个状态栏，显示FONA是否正常工作
#define STATUS_X 10
#define STATUS_Y 65
//16进制颜色
#define  BLACK   0x0000 //黑
#define BLUE    0x001F  //蓝
#define RED     0xF800  //红
#define GREEN   0x07E0  //绿
#define CYAN    0x07FF  //青
#define MAGENTA 0xF81F  //洋红
#define YELLOW  0xFFE0  //黄
#define WHITE   0xFFFF  //白

#define t12_temp_pin A5      //T12温度读取引脚
#define sleep_pin A3         //休眠状态读取引脚
#define ec_pin A4            //电流读取引脚
#define volage_pin A6        //电源电压读取引脚
#define ntc_pin A7           //ntc读取引脚
#define t12_pwm_pin 10       //T12加热控制引脚
#define buzzer_pin 11        //蜂鸣器控制引脚
#define vcc_refer 4.98       //arduino的电压
#define vcc_refer_ec vcc_refer/2       //电流传感器的计算电压
#define vcc_refer_1024 vcc_refer/1024   //参考电压每级分量

//PID
volatile uint16_t pid_out = 0; //pid输出
int16_t ek1 = 0; //上一次误差
int16_t ek2 = 0; //上上一次误差
int16_t ek0 = 0; //现在误差
float p = 38.0;
float i = 0.5;
float d = 5.0;

const uint8_t p_eeprom = 0; //pid-p的eeprom地址，占用4位
const uint8_t i_eeprom = 4; //pid-i的eeprom地址，占用4位
const uint8_t d_eeprom = 8; //pid-d的eeprom地址，占用4位

//键盘
#define keyboard_x 90 //键盘起点X
#define keyboard_y 218 //键盘起点Y
boolean keyboard_state = 0; //键盘显示
boolean keyboard_touch_state = 0; //键盘触摸
float keyboard_cache = 0; //键盘输出数值缓存
boolean dotFlag = 0;  //小数点标志位
boolean p_change = 0; //按下P的标志位
boolean i_change = 0; //按下i的标志位
boolean d_change = 0; //按下d的标志位

//计数相关、标志位
uint32_t t12_temp_time = 0; //t12温度计算 定时运行的对比时间
uint32_t t12_pid_time = 0;  //pid温度计算 定时运行的对比时间
uint32_t display_time = 0;  //屏幕显示 定时运行的对比时间
uint16_t t12_temp_read_time = 800; //t12温度计算 定时运行的时间
uint8_t fps_0 = 0;
uint8_t fps_1 = 0;

//T12及温度相关
float t12_ad = 0.0; //T12原始AD
uint16_t t12_temp = 0.0; //T12温度
boolean t12_switch = 0; //T12加热总开关
volatile int16_t set_temp = 200; //设置温度

volatile float ntc_temp = 0; //ntc温度

//电压电流
float volage = 0.0;
uint32_t volage_time = 0;
float ec = 0.0;

//显示、触屏标志位
boolean main_display_state = 1; //主界面显示
boolean main_display_touch = 1; //主界面触摸

boolean set_display_state = 0; //设置界面显示
boolean set_display_touch = 0;//设置界面触摸

void setup()
{
  Serial.begin(9600);
  pinMode(t12_temp_pin, 0);
  pinMode(sleep_pin, INPUT_PULLUP);
  pinMode(ec_pin, 0);
  pinMode(volage_pin, 0);
  pinMode(ntc_pin, 0);
  pinMode(t12_pwm_pin, 1);
  pinMode(buzzer_pin, 1);

  mylcd.Init_LCD();
  mylcd.Read_ID();
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Rotation(1);//1比0快

  volage_read(); //读取电源电压
  ntc_temp_read(); //读取ntc温度
  ec_read(); //读取电流

  /*EEPROM.put(p_eeprom, p);
    EEPROM.put(i_eeprom, i);
    EEPROM.put(d_eeprom, d);*/

  EEPROM.get(p_eeprom, p);
  EEPROM.get(i_eeprom, i);
  EEPROM.get(d_eeprom, d);

  //MsTimer2::set(3000, FPS);
  //MsTimer2::start();
}

void loop()
{
  touch();//触摸
  timing_volage_ntc();//定时读取电压电流ntc温度
  read_t12_temp1();
  /*Serial.print("PidOut："); Serial.print(pid_out); Serial.print("||");
    Serial.print("ek0："); Serial.print(ek0); Serial.print("||");
    Serial.print("ek1："); Serial.print(ek1); Serial.print("||");
    Serial.print("ek2："); Serial.println(ek2);*/
  //mainDisplay();//显示
  t12_pid();
  //fps_0++;
}

//计算fps
void FPS()
{
  fps_1 = fps_0 / 3;
  fps_0 = 0;
}
