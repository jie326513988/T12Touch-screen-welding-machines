#include <TouchScreen.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>
#include <EEPROM.h>
#include <avr/wdt.h>

LCDWIKI_KBV mylcd(ILI9341, A2, A1, 13, A0, 12); //model,cs,cd,wr,rd,resett
#define YP A2  // must be an analog pin, use "An" notation!
#define XM A1  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

//原始X触摸范围
/*#define min_px 125
  #define max_px 910
  //原始Y触摸范围
  #define min_py 85
  #define max_py 895*/
//原始Z压力范围
#define MIN_PZ 300
#define MAX_PZ 1000
//x+ x-的电阻值
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
// 我们有一个状态栏，显示FONA是否正常工作
#define STATUS_X 10
#define STATUS_Y 65
//16进制颜色
#define BLACK     0x0000          //黑色    0,   0,   0
#define NAVY      0x000F          //深蓝色  0,   0, 127
#define DGREEN    0x03E0          //深绿色  0,  127,  0
#define DCYAN     0x03EF          //深青色  0,  127, 127       
#define MAROON    0x7800          //深红色  127,   0,   0      
#define PURPLE    0x780F          //紫色    127,   0, 127      
#define OLIVE     0x7BE0          //橄榄绿  127, 127,   0      
#define LGRAY     0xC618          //灰白色  192, 192, 192      
#define DGRAY     0x7BEF          //深灰色  127, 127, 127      
#define BLUE      0x001F          //蓝色    0,   0, 255        
#define GREEN     0x07E0          //绿色    0, 255,   0        
#define CYAN      0x07FF          //青色    0, 255, 255        
#define RED       0xF800          //红色    255,   0,   0      
#define MAGENTA   0xF81F          //品红    255,   0, 255      
#define YELLOW    0xFFE0          //黄色    255, 255, 0        
#define WHITE     0xFFFF          //白色    255, 255, 255      
#define PINK      0xD2F5          //粉红色
#define fc1 PURPLE  //变量名 紫色
#define fc2 DCYAN   //数值 深青色
#define fc3 DGRAY   //键盘字体颜色 深灰色

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
int16_t pid_out = 0; //pid输出
int16_t ek1 = 0; //上一次差值
int16_t ek2 = 0; //上上一次差值
int16_t ek0 = 0; //现在差值
float p = 45.0;
float i = 0.4;
float d = 35.0;

//eeprom
#define p_eeprom  0                       //pid-p的eeprom地址，占用4位
#define i_eeprom  4                       //pid-i的eeprom地址，占用4位
#define d_eeprom  8                       //pid-d的eeprom地址，占用4位
#define sleep_count_set_eeprom  12        //休眠设置计数，占用4位
#define sleep_temp_eeprom  16             //休眠温度，占用1位0-255
#define MIN_PX_eeprom  17                 //校准min_px，占用4位
#define MAX_PX_eeprom  21                 //校准max_px，占用4位
#define MIN_PY_eeprom  25                 //校准min_py，占用4位
#define MAX_PY_eeprom  29                 //校准max_py，占用4位

//键盘
#define keyboard_x 80 //键盘起点X
#define keyboard_y 218 //键盘起点Y
boolean keyboard_state = 0; //键盘显示
boolean keyboard_touch_state = 0; //键盘触摸
float keyboard_cache = 0; //键盘输出数值缓存
boolean dotFlag = 0;  //小数点标志位

//计数相关
uint32_t t12_temp_time = 0;         //t12温度计算 定时运行的对比时间
uint16_t t12_temp_read_time = 800;  //t12温度计算 定时运行的时间
uint32_t sleep_read_time = 0;       //读取休眠 定时运行的对比时间
uint32_t volage_time = 0;           //电压、NTC读取 定时运行的对比时间
uint32_t touch_time = 0;            //触摸消抖的对比时间

//T12及温度相关
float t12_ad = 0.0;        //T12原始AD
uint16_t t12_temp = 0.0;   //T12温度
boolean t12_switch = 0;    //T12加热总开关
int16_t set_temp = 260;    //设置温度
float ntc_temp = 0;        //ntc温度

//电压电流、休眠
float volage = 0.0;             //电源电压
float ec = 0.0;                 //T12工作电流
boolean sleep_state = 0;        //休眠状态
uint16_t sleep_count = 0;       //休眠计数
uint16_t sleep_count_set = 150;  //进入休眠的阈值
uint8_t sleep_temp = 180;       //休眠时的温度
uint16_t sleep_temp_cache = 0;  //休眠前的温度
//触屏校准、设置相关
int px, py;                      //p.x,p.y转换后的值
boolean coordinates_state = 0;  //显示坐标的标志位
boolean calibration_state = 0;   //校准屏幕的标志位
uint16_t min_px, max_px, min_py, max_py;
uint16_t MIN_PX = 125;
uint16_t MAX_PX = 910;
uint16_t MIN_PY = 85;
uint16_t MAX_PY = 895;
uint8_t calibration_location = 0;   //校准的位置
uint16_t calibration_count = 0;     //校准触摸时间计数

//显示、触屏标志位
uint8_t display_state = 1;      //显示界面的标志位
uint8_t display_touch = 1;      //显示界面触摸的标志位
//0-空，1-主界面，2-设置界面1p，3-设置界面2p，4-pid界面，5-休眠界面
#define MainDisplay   1
#define SetDisplay1   2
#define SetDisplay2   3
#define PidDisplay    4
#define SleepDisplay  5
#define ScreenSetDisplay 6
uint8_t change_num = 0;         //需要改变的数值标志位
//0-空，1-p，2-i，3-d，
#define p_change_num                1
#define i_change_num                2
#define d_change_num                3
#define sleep_temp_change_num       4
#define sleep_count_set_change_num  5

void setup()
{
  //Serial.begin(9600);
  /*pinMode(sleep_pin, INPUT_PULLUP);//设置上拉模式
    pinMode(t12_temp_pin, 0);
    pinMode(ec_pin, 0);
    pinMode(ec_pin, 0);
    pinMode(volage_pin, 0);
    pinMode(ntc_pin, 0);
    pinMode(t12_pwm_pin, 1);
    pinMode(buzzer_pin, 1);*/

  //直接操作寄存器节省内存
  bitWrite(DDRC, 3, 0);     //pinMode(sleep_pin, INPUT_PULLUP);
  bitWrite(PORTC, 3, 1);    //设置上拉
  bitWrite(DDRC, 5, 0);     //pinMode(t12_temp_pin, 0);
  //bitWrite(PORTC, 5, 0);
  bitWrite(DDRC, 4, 0);     //pinMode(ec_pin, 0);
  //bitWrite(PORTC, 4, 0);
  bitWrite(DDRC, 6, 0);     // pinMode(volage_pin, 0);
  //bitWrite(PORTC, 6, 0);
  bitWrite(DDRC, 7, 0);     //pinMode(ntc_pin, 0);
  //bitWrite(PORTC, 7, 0);
  bitWrite(DDRB, 2, 1);     // pinMode(t12_pwm_pin, 1);
  bitWrite(DDRB, 3, 1);     //pinMode(buzzer_pin, 1);

  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Rotation(1);  //设置屏幕的旋转旋转90度，即横屏显示

  volage_read(); //读取电源电压
  ntc_temp_read(); //读取ntc温度
  ec_read(); //读取电流

  //*********第一次刷入去掉注释，第二次刷入注释上*********//
  /*EEPROM.put(p_eeprom, p);
    EEPROM.put(i_eeprom, i);
    EEPROM.put(d_eeprom, d);
    EEPROM.put(sleep_count_set_eeprom, sleep_count_set);
    EEPROM.update(sleep_temp_eeprom, sleep_temp);
    EEPROM.put(MIN_PX_eeprom, MIN_PX);
    EEPROM.put(MAX_PX_eeprom, MAX_PX);
    EEPROM.put(MIN_PY_eeprom, MIN_PY);
    EEPROM.put(MAX_PY_eeprom, MAX_PY);*/
  //*********第一次刷入注释上，第二次刷入去掉注释*********//
  EEPROM.get(p_eeprom, p);
  EEPROM.get(i_eeprom, i);
  EEPROM.get(d_eeprom, d);
  EEPROM.get(sleep_count_set_eeprom, sleep_count_set);
  EEPROM.get(sleep_temp_eeprom, sleep_temp);
  EEPROM.get(MIN_PX_eeprom, MIN_PX);
  EEPROM.get(MAX_PX_eeprom, MAX_PX);
  EEPROM.get(MIN_PY_eeprom, MIN_PY);
  EEPROM.get(MAX_PY_eeprom, MAX_PY);
  //******************************************************//
  
  wdt_enable(WDTO_1S);  //开启看门狗，超时为1秒
}

void loop()
{
  touch();               //触摸
  timing_volage_ntc();   //定时读取电压电流ntc温度
  read_t12_temp();       //读取T12温度
  sleep_read();          //休眠检测
  wdt_reset();           //喂狗
  //t12_display();
  /*Serial.print("PidOut："); Serial.print(pid_out); Serial.print("||");
    Serial.print("ek0："); Serial.print(ek0); Serial.print("||");
    Serial.print("ek1："); Serial.print(ek1); Serial.print("||");
    Serial.print("ek2："); Serial.println(ek2);*/
  //t12_pid();
}
