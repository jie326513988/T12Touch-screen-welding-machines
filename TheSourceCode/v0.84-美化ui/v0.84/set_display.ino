//设置界面的显示

void setDisplay()
{
  if (display_state == SetDisplay1)
  {
    uint8_t y = 40;
    //my_lcd.Set_Draw_color(LGRAY);
    //my_lcd.Draw_Fast_VLine(159, 0, 239);

    my_lcd.Set_Text_colour(255, 105, 180); //热情的粉红
    show_string_no_fc("PID", SetParameterX, SetParameterY, 3, BLACK, 0);
    show_number_float(p, SetParameterX - 15, SetParameterY + 30, 1, fc2, BLACK, 0);
    show_number_float(i, SetParameterX + 16, SetParameterY + 30, 1, fc2, BLACK, 0);
    show_number_float(d, SetParameterX + 40, SetParameterY + 30, 1, fc2, BLACK, 0);

    my_lcd.Set_Text_colour(255, 140, 0); //深橙色
    show_string_no_fc("Sleep", SetParameterX + 152, SetParameterY, 3, BLACK, 1);
    show_number_int(sleep_temp, SetParameterX + 152 + 5, SetParameterY + 30, 1, fc2, BLACK, 0);
    show_number_int(sleep_count_set, SetParameterX + 152 + 60, SetParameterY + 30, 1, fc2, BLACK, 0);

    my_lcd.Set_Text_colour(124, 252, 0); //草坪绿
    show_string_no_fc("Screen Set", CENTER, SetParameterY + 80, 3, BLACK, 0);

    my_lcd.Set_Text_colour(221, 160, 221); //李子
    show_string_no_fc("V0.84  By:LCJ", CENTER, 231, 1, BLACK, 0);

    show_string("Back", 276, 225, 2, RED, BLACK, 0);

    display_state = 0;
  }
  my_lcd.Set_Text_colour(fc1);
  show_string_no_fc("T12AD", 127, 176, 1, BLACK, 0);
  show_string_no_fc("T12temp", 127, 184, 1, BLACK, 0);
  show_string_no_fc("PidOut", 127, 192, 1, BLACK, 0);
  show_string_no_fc("Sleep", 127, 200, 1, BLACK, 0);
  //show_number_int(MAX_PX, 125 , 176, 1, fc2, BLACK, 0);
  //show_number_int(MIN_PX, 205, 176, 1, fc2, BLACK, 0);
  //show_number_int(MIN_PY, 125, 186, 1, fc2, BLACK, 0);
  //show_number_int(MAX_PY, 205, 186, 1, fc2, BLACK, 0);
  show_number_int(t12_temp, 46 + 130, 184, 1, fc2, BLACK, 0);
  my_lcd.Print_Number_Int(t12_ad, 40 + 130, 176, 5, '0', 10);
  my_lcd.Print_Number_Int(pid_out, 46 + 130, 192, 4, ' ', 10);
  my_lcd.Print_Number_Int(sleep_count, 46 + 130, 200, 4, ' ', 10);
  //show_number_int(pid_out, 46, 192, 1, fc2, BLACK, 0);
  //show_number_int(sleep_count, 46, 200, 1, fc2, BLACK, 0);
  //show_number_int(digitalRead(sleep_pin), 40, 200, 1, fc2, BLACK, 0);
}

void pid_display() //pid界面
{
  if (display_state == PidDisplay)
  {
    my_lcd.Set_Text_colour(255, 105, 180); //热情的粉红
    show_string_no_fc("P", 0, 0, 3, BLACK, 0);
    show_string_no_fc("I", 117, 0, 3, BLACK, 0);
    show_string_no_fc("D", 234, 0, 3, BLACK, 0);

    show_string("Back", 276, 225, 2, RED, BLACK, 0);

    my_lcd.Fill_Rect(0, 30, 320, 24, BLACK); //用黑色矩形填充掉原来的数值
    show_number_float(p, 0, 30, 3, fc2, BLACK, 0);
    show_number_float(i, 117, 30, 3, fc2, BLACK, 0);
    show_number_float(d, 233, 30, 3, fc2, BLACK, 0);

    display_state = 0;
  }
  switch (change_num)
  {
    case p_change_num:
      show_number_float(p, 0, 30, 3, WHITE, BLACK  , 0);
      break;
    case i_change_num:
      show_number_float(i, 117, 30, 3, WHITE, BLACK  , 0);
      break;
    case d_change_num:
      show_number_float(d, 233, 30, 3, WHITE, BLACK  , 0);
      break;
  }
}
void sleep_display() //sleep界面
{
  if (display_state == SleepDisplay)
  {
    my_lcd.Set_Text_colour(255, 140, 0); //深橙色
    show_string_no_fc("SLEEP", CENTER, 0, 2, BLACK, 0);
    show_string_no_fc("temp", 50, 20, 2, BLACK, 0);
    show_string_no_fc("time", 220, 20, 2, BLACK, 0);

    show_string("Back", 276, 225, 2, RED, BLACK, 0);

    my_lcd.Fill_Rect(50, 40, 320, 24, BLACK); //用黑色矩形填充掉原来的数值
    show_number_int(sleep_temp, 50, 40, 2, fc2, BLACK  , 0);
    show_number_int(sleep_count_set, 220, 40, 2, fc2, BLACK  , 0);
    display_state = 0;
  }
  switch (change_num)
  {
    case sleep_temp_change_num:
      show_number_int(sleep_temp, 50, 40, 3, WHITE, BLACK  , 0);
      break;
    case sleep_count_set_change_num:
      show_number_int(sleep_count_set, 220, 40, 3, WHITE, BLACK  , 0);
      break;
  }
}

void screen_set_display() //屏幕设置界面
{
  if (display_state == ScreenSetDisplay)
  {
    //校准屏幕开关
    show_string("Screen Calibration", CENTER, 50, 2, GREEN, BLACK, 0);
    if (calibration_state == 1)
    {
      show_string_no_fc("MAX    MIN", CENTER, 80, 2, BLACK, 0);
      show_string_no_fc("X", 50, 120, 2, BLACK, 0);
      show_string_no_fc("Y", 50, 160, 2, BLACK, 0);

      //4个校准点
      my_lcd.Set_Draw_color(DGRAY); //深灰色
      my_lcd.Fill_Rectangle(0, 0, 4, 4);
      my_lcd.Fill_Rectangle(315, 0, 319, 4);
      my_lcd.Fill_Rectangle(315, 235, 319, 239);
      my_lcd.Fill_Rectangle(0, 235, 4, 239);

      if (calibration_location > 4) show_string_no_fc("OK", 270, 135, 3, BLACK, 0);
    }
    //显示坐标开关
    else if (calibration_state == 0)
    {
      if (coordinates_state == 0) show_string("Coordinate Display", CENTER, 140, 2, DGRAY, BLACK, 0);
      else show_string_no_fc("Coordinate Display", CENTER, 140, 2, BLACK, 0);
    }
    show_string("Back", CENTER, 225, 2, RED, BLACK, 0);
    display_state = 0;
  }
  if (calibration_state == 1) //进入校准模式
  {
    //4个校准点
    my_lcd.Set_Draw_color(GREEN);
    if (calibration_location == 1) my_lcd.Fill_Rectangle(0, 0, 4, 4);
    else if (calibration_location == 2) my_lcd.Fill_Rectangle(315, 0, 319, 4);
    else if (calibration_location == 3) my_lcd.Fill_Rectangle(315, 235, 319, 239);
    else if (calibration_location == 4) my_lcd.Fill_Rectangle(0, 235, 4, 239);

    show_number_int(calibration_count, CENTER, 20, 2, fc2, BLACK, 0);
    show_number_int(max_px, 100, 120, 2, fc2, BLACK, 0);
    show_number_int(min_px, 185, 120, 2, fc2, BLACK, 0);
    show_number_int(max_py, 100, 160, 2, fc2, BLACK, 0);
    show_number_int(min_py, 185, 160, 2, fc2, BLACK, 0);
  }
}

void keyboard_display() //键盘显示
{

  my_lcd.Set_Text_colour(fc3);
  show_string_no_fc("1", keyboard_x1, keyboard_y1, 3, BLACK , 0);
  show_string_no_fc("2", keyboard_x2, keyboard_y1, 3, BLACK, 0);
  show_string_no_fc("3", keyboard_x3, keyboard_y1, 3, BLACK, 0);
  show_string_no_fc("<", keyboard_x4, keyboard_y1, 3, BLACK, 0);

  show_string_no_fc("4", keyboard_x1, keyboard_y2, 3, BLACK, 0);
  show_string_no_fc("5", keyboard_x2, keyboard_y2, 3, BLACK, 0);
  show_string_no_fc("6", keyboard_x3, keyboard_y2, 3, BLACK, 0);
  show_string_no_fc("0", keyboard_x4, keyboard_y2, 3, BLACK, 0);

  show_string_no_fc("7", keyboard_x1, keyboard_y3, 3, BLACK, 0);
  show_string_no_fc("8", keyboard_x2, keyboard_y3, 3, BLACK, 0);
  show_string_no_fc("9", keyboard_x3, keyboard_y3, 3, BLACK, 0);
  if (dotFlag == 0) show_string_no_fc(".", keyboard_x4, keyboard_y3, 3, BLACK, 0);
  else if (dotFlag == 1) show_string(".", keyboard_x4, keyboard_y3, 3, YELLOW, BLACK , 0);
  show_string("Ok", keyboard_x + 135, keyboard_y - 129, 3, fc3, BLACK, 0);
}
