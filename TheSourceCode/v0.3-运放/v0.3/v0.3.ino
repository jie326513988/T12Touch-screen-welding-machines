#include <TouchScreen.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>
#include <MsTimer2.h>

LCDWIKI_KBV mylcd(ILI9341, A3, A2, 13, A1, 12); //model,cs,cd,wr,rd,resett
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
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
#define MAXPRESSURE 800
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

#define t12_temp_pin A5   //T12温度读取引脚
#define sleep_pin A3      //休眠状态读取引脚
#define ec_pin A4         //电流读取引脚
#define volage_pin A6     //电源电压读取引脚
#define ntc_pin A7        //ntc读取引脚
#define t12_pwm_pin 10    //T12加热控制引脚
#define buzzer_pin 11     //蜂鸣器控制引脚

#define vcc_refer 0.00488 //5V
uint8_t fps_0 = 0;
uint8_t fps_1 = 0;
uint16_t t12_temp = 0;
uint32_t t12_temp_time = 0;

void setup()
{
  //Serial.begin(9600);
  pinMode(t12_temp_pin,0);
  pinMode(sleep_pin,0);
  pinMode(ec_pin,0);
  pinMode(volage_pin,0);
  pinMode(ntc_pin,0);
  pinMode(t12_pwm_pin,1);
  pinMode(buzzer_pin,1);
  mylcd.Init_LCD();
  mylcd.Read_ID();
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Rotation(1);//1比0快
  MsTimer2::set(1000, FPS);
  MsTimer2::start();
}

void loop()
{
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  read_wen_du();
  show_string("T12_AD:", 0, 0, 3, RED, BLACK, 1);
  show_number_int(t12_temp, 150, 0, 3, BLUE, BLACK  , 0);
  show_string("Fps", 280, 0, 1, RED, BLACK, 1);
  show_number_int(fps_1, 280, 10, 1, BLUE, BLACK  , 0);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

    show_string("Read p.x:", 0, 136, 3, RED, BLACK, 1);
    show_number_int(p.x, 160, 136, 3, BLUE, BLACK  , 0);

    show_string("Read p.y:", 0, 170, 3, RED, BLACK, 1);
    show_number_int(p.y, 160, 170, 3, BLUE, BLACK  , 0);

    show_string("Read p.z:", 0, 204, 3, RED, BLACK, 1);
    show_number_int(p.z, 160, 204, 3, BLUE, BLACK  , 0);
  }
  fps_0++;

}
