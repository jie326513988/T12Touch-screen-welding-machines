//指定位置画字符
void show_string(uint8_t *str, int16_t x, int16_t y, uint8_t csize, uint16_t fc, uint16_t bc, boolean mode0)
{
  mylcd.Set_Text_Mode(mode0); //设置文本的重叠模式 0不重叠，1重叠
  mylcd.Set_Text_Size(csize); //设置字体大小
  mylcd.Set_Text_colour(fc); //设置文本颜色值
  mylcd.Set_Text_Back_colour(bc);  //设置文本背景颜色值
  mylcd.Print_String(str, x, y); //在指定的坐标处打印常量字符串,可以使用LEFT ,CENTER, RIGHT文字作为x坐标来对齐屏幕上的字符串
}

//指定位置画整数
void show_number_int(long num, int16_t x, int16_t y, uint8_t csize, uint16_t fc, uint16_t bc, boolean mode0)
{
  mylcd.Set_Text_Mode(mode0);
  mylcd.Set_Text_Size(csize);
  mylcd.Set_Text_colour(fc);
  mylcd.Set_Text_Back_colour(bc);
  mylcd.Print_Number_Int(num, x, y, 5, '0', 10);
}

//指定位置画浮点数
void show_number_float(uint8_t ws,double num, int16_t x, int16_t y, uint8_t csize, uint16_t fc, uint16_t bc, boolean mode0)
{
  mylcd.Set_Text_Mode(mode0);
  mylcd.Set_Text_Size(csize);
  mylcd.Set_Text_colour(fc);
  mylcd.Set_Text_Back_colour(bc);
  mylcd.Print_Number_Float(num, ws, x, y, '.', 0, ' ');
}
