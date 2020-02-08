//主界面的显示
void mainDisplay()
{
  if (display_state == MainDisplay)
  {
    my_lcd.Set_Text_colour(fc1);
    show_string_no_fc("Temp", 50, 5, 2, BLACK, 1);
    show_string_no_fc("SetTemp", 30, 125, 2, BLACK, 1);
    show_string_no_fc("V", 252, 232, 1, BLACK, 1);
    show_string_no_fc("A", 283, 232, 1, BLACK, 1);
    show_string("SET", 0,  226, 2, YELLOW, BLACK, 1);

    my_lcd.Set_Text_colour(106,90,205); //板岩暗蓝灰色
    show_string_no_fc("400", 60,  226, 2, BLACK, 1);
    my_lcd.Set_Text_colour(147, 112, 219); // 适中的紫色
    show_string_no_fc("320", 120,  226, 2, BLACK, 1);
    my_lcd.Set_Text_colour(123, 104, 238); // 适中的板岩暗蓝灰色
    show_string_no_fc("240", 180,  226, 2, BLACK, 1);

    my_lcd.Set_Draw_color(0, 191, 255);
    my_lcd.Draw_Triangle(275, 5, 250, 45, 300, 45);//上三角
    my_lcd.Draw_Triangle(275, 110, 250, 70, 300, 70);//下三角

    if (t12_switch == 0)
    {
      show_string("ON", 258,  144, 3, DGRAY, BLACK, 1);
      show_string("OFF", 248,  188, 3, RED, BLACK, 1);
    }
    else if (t12_switch == 1)
    {
      show_string("ON", 258,  144, 3, RED, BLACK, 1);
      show_string("OFF", 248,  188, 3, DGRAY, BLACK, 1);
    }
    display_state = 0;
  }
  show_number_float(volage, 226, 232, 1, fc2, BLACK, 0);
  show_number_float(ec, 263, 232, 1, fc2, BLACK, 0);
  show_number_float(ntc_temp, RIGHT, 232, 1, fc2, BLACK, 0);
  my_lcd.Set_Text_Size(8);
  my_lcd.Print_Number_Int(t12_temp, 5, 30, 4, '0', 10);
  my_lcd.Set_Text_Size(3);
  my_lcd.Print_Number_Int(set_temp, 45, 150, 4, '0', 10);
  //my_lcd.Set_Text_Size(1);
  //my_lcd.Print_Number_Int(t12_temp_read_time, 150, 150, 5, '0', 10);
}
