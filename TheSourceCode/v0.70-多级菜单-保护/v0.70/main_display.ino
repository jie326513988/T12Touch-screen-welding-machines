//主界面的显示
void mainDisplay()
{
  if (display_state == MainDisplay)
  {
    show_string("Temp", 50, 5, 2, fc1, BLACK, 1);
    show_string("SetTemp", 30, 125, 2, fc1, BLACK, 1);
    show_string("V", 252, 232, 1, fc1, BLACK, 1);
    show_string("A", 283, 232, 1, fc1, BLACK, 1);
    show_string("SET", 0,  226, 2, YELLOW, BLACK, 1);

    mylcd.Set_Text_colour(123, 104, 238); // 适中的板岩暗蓝灰色
    show_string_no_fc("400", 60,  226, 2, BLACK, 1);
    show_string_no_fc("320", 120,  226, 2, BLACK, 1);
    show_string_no_fc("240", 180,  226, 2, BLACK, 1);

    mylcd.Set_Draw_color(0, 191, 255);
    mylcd.Draw_Triangle(275, 5, 250, 45, 300, 45);//上三角
    mylcd.Draw_Triangle(275, 110, 250, 70, 300, 70);//下三角

    if (t12_switch == 0)
    {
      show_string("ON", 258,  144, 3, DGRAY, BLACK, 1);
      mylcd.Set_Text_colour(  255, 0, 0); //  纯红
      show_string_no_fc("OFF", 248,  188, 3, BLACK, 1);
    }
    else if (t12_switch == 1)
    {
      mylcd.Set_Text_colour(  255, 0, 0); //  纯红
      show_string_no_fc("ON", 258,  144, 3, BLACK, 1);
      show_string("OFF", 248,  188, 3, DGRAY, BLACK, 1);
    }
    display_state = 0;
  }
  show_number_int_0(t12_temp, 5, 30, 8, fc2, BLACK, 0);
  show_number_int_0(set_temp, 45, 150, 3, fc2, BLACK, 0);
  show_number_float(volage, 226, 232, 1, fc2, BLACK, 0);
  show_number_float(ec, 263, 232, 1, fc2, BLACK, 0);
  show_number_float(ntc_temp, RIGHT, 232, 1, fc2, BLACK, 0);
}
