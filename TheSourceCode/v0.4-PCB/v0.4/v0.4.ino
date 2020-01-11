#include <TouchScreen.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>
#include <MsTimer2.h>

LCDWIKI_KBV mylcd(ILI9341, A2, A1, 13, A0, 12); //model,cs,cd,wr,rd,resett
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//X触摸灵敏度
#define TS_MINX 140
#define TS_MAXX 893
//Y触摸灵敏度
#define TS_MINY 98
#define TS_MAXY 870
//压力触摸灵敏度
#define MINPRESSURE 10
#define MAXPRESSURE 600
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
int16_t ek1 = 0; //上一次误差
int16_t ek2 = 0; //上上一次误差
int16_t ek0 = 0;
float p = 6.00;
float i = 0.06;
float d = 0.02;
//计数相关、标志位
uint32_t t12_temp_time = 0;
uint32_t t12_pid_time = 0;
uint32_t display_time = 0;

uint8_t fps_0 = 0;
uint8_t fps_1 = 0;

//T12及温度相关
uint16_t t12_ad = 0;
uint16_t t12_temp = 0.0;
boolean t12_switch = 0;
volatile int16_t set_temp = 0;
volatile uint16_t pid_out = 0;

volatile float ntc_temp = 0;

//电压电流
float volage = 0.0;
uint32_t volage_time = 0;
float ec = 0.0;

//显示、触屏标志位
boolean main_display_state = 1;
boolean main_display_touch = 1;

boolean temp_meas_state = 0;
boolean warm_meas_state = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(t12_temp_pin, 0);
  pinMode(sleep_pin, 0);
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
  MsTimer2::set(1000, FPS);
  MsTimer2::start();
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
  mainDisplay();//显示
  t12_pid();
  fps_0++;
}

//计算fps
void FPS()
{
  fps_1 = fps_0;
  fps_0 = 0;
}
