//主界面的显示

void mainDisplay()
{
  if (display_state == MainDisplay)
  {
    my_lcd.Set_Text_colour(fc1);
    show_string_no_fc("SetTemp", parameterX, parameterY, 1, BLACK, 0);
    show_string_no_fc("V", parameterX + 14, parameterY + 40, 1, BLACK, 0);
    show_string_no_fc("A", parameterX + 49, parameterY + 40, 1, BLACK, 0);
    show_string_no_fc("NTC", parameterX + 14, parameterY + 55, 1, BLACK, 0);

    //show_string("SET", 0,  226, 2, YELLOW, BLACK, 1);
    my_lcd.Set_Draw_color(YELLOW);
    my_lcd.Draw_Fast_HLine(0, 239, 16);
    my_lcd.Draw_Fast_HLine(303, 239, 16);

    my_lcd.Set_Text_colour(106, 90, 205); // 板岩暗蓝灰色
    show_string_no_fc("400", 83,  226, 2, BLACK, 0);
    show_string_no_fc("320", 83 + 60,  226, 2, BLACK, 0);
    show_string_no_fc("240", 83 + 60 * 2,  226, 2, BLACK, 0);

    my_lcd.Set_Draw_color(  106, 90, 205); //  紫色
    my_lcd.Draw_Triangle(159, 90, 159 - 30, 90 + 40, 159 + 30, 90 + 40); //上三角
    my_lcd.Draw_Triangle(159, 190, 159 - 30, 190 - 40, 159 + 30, 190 - 40); //下三角

    if (t12_switch == 0)
    {
      show_string("ON", 268,  130, 3, DGRAY, BLACK, 0);
      show_string("OFF", 258,  180, 3, fc1, BLACK, 0);
    }
    else if (t12_switch == 1)
    {
      show_string("ON", 268,  130, 3, fc1, BLACK, 0);
      show_string("OFF", 258,  180, 3, DGRAY, BLACK, 0);
    }
    display_state = 0;
  }

  show_number_float(volage, parameterX - 11, parameterY + 40, 1, fc2, BLACK, 0);   //电源电压
  show_number_float(ec, parameterX + 29, parameterY + 40, 1, fc2, BLACK, 0);       //T12电流
  show_number_float(ntc_temp, parameterX + 11, parameterY + 65, 1, fc2, BLACK, 0); //NTC温度
  //当前温度
  my_lcd.Set_Text_Size(8);
  my_lcd.Set_Text_colour(fc2); 
  my_lcd.Print_Number_Int(t12_temp, 90, 10, 4, '0', 10);
  //设置温度
  my_lcd.Set_Text_Size(3);
  my_lcd.Set_Text_colour(fc2); //设置文本颜色值
  if (set_temp < 100 && set_temp > 10) my_lcd.Print_Number_Int(set_temp, parameterX - 14, parameterY + 10, 4, ' ', 10);
  else if (set_temp >= 100) my_lcd.Print_Number_Int(set_temp, parameterX - 5, parameterY + 10, 4, ' ', 10);
}
