#include <TouchScreen.h>
#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>
#include <MsTimer2.h>

LCDWIKI_KBV mylcd(ILI9341, A3, A2, 12, A1, 10); //model,cs,cd,wr,rd,resett
#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin
//X触摸灵敏度
#define TS_MINX 124
#define TS_MAXX 906
//Y触摸灵敏度
#define TS_MINY 83
#define TS_MAXY 893
//压力触摸灵敏度
#define MINPRESSURE 10
#define MAXPRESSURE 900
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

int analog_num = 0;
uint32_t a = 0;
uint8_t fps = 0;
void show_string(uint8_t *str, int16_t x, int16_t y, uint8_t csize, uint16_t fc, uint16_t bc, boolean mode)
{
  mylcd.Set_Text_Mode(mode);
  mylcd.Set_Text_Size(csize);
  mylcd.Set_Text_colour(fc);
  mylcd.Set_Text_Back_colour(bc);
  mylcd.Print_String(str, x, y);
}
void show_number_int(long num, int16_t x, int16_t y, uint8_t csize, uint16_t fc, uint16_t bc, boolean mode)
{
  mylcd.Set_Text_Mode(mode);
  mylcd.Set_Text_Size(csize);
  mylcd.Set_Text_colour(fc);
  mylcd.Set_Text_Back_colour(bc);
  mylcd.Print_Number_Int(num, x, y, 5, '0', 10);
}

void setup()
{
  pinMode(A5, 0);
  pinMode(A6, 0);
  pinMode(A7, 0);
  mylcd.Init_LCD();
  mylcd.Read_ID();
  mylcd.Fill_Screen(BLACK);
  mylcd.Set_Rotation(1);//1比0快
  MsTimer2::set(1000, flash); // 500ms period
  MsTimer2::start();
}

void loop()
{
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
  show_string("Read A5:", 0, 0, 3, RED, BLACK, 1);
  show_number_int(analogRead(A5), 150, 0, 3, BLUE, BLACK  , 0);
  show_string("Read A6:", 0, 34, 3, RED, BLACK, 1);
  show_number_int(analogRead(A6), 150, 34, 3, BLUE, BLACK  , 0);
  show_string("Read A7:", 0, 68, 3, RED, BLACK, 1);
  show_number_int(analogRead(A7), 150, 68, 3, BLUE, BLACK  , 0);

  show_string("Fps", 280, 0, 1, RED, BLACK, 1);
  show_number_int(fps, 280, 10, 1, BLUE, BLACK  , 0);

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
  a++;
}
void flash()
{
  fps = a;
  a = 0;
}
