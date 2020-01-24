//设置界面的显示
void setDisplay()
{
  if (display_state == SetDisplay1)
  {
    uint8_t y = 40;
    mylcd.Set_Text_colour(255, 105, 180); //热情的粉红
    show_string_no_fc("PID", CENTER, 0 * y, 3, BLACK, 1);
    mylcd.Set_Text_colour(255, 140, 0); //深橙色
    show_string_no_fc("Sleep", CENTER, 1 * y, 3, BLACK, 1);
    mylcd.Set_Text_colour(124, 252, 0); //草坪绿
    show_string_no_fc("Screen Set", CENTER, 2 * y, 3, BLACK, 1);

    mylcd.Set_Text_colour(221, 160, 221); //李子
    show_string_no_fc("V0.80  By:LCJ", CENTER, 233, 1, BLACK, 1);

    show_string("Back", 276, 225, 2, RED, BLACK, 1);

    display_state = 0;
  }
  mylcd.Set_Text_colour(fc1);
  //show_string_no_fc("MAX_PX", 80, 176, 1, BLACK, 1);
  //show_string_no_fc("MIN_PX", 160, 176, 1, BLACK, 1);
  //show_string_no_fc("MIN_PY", 80, 186, 1, BLACK, 1);
  //show_string_no_fc("MAX_PY", 160, 186, 1, BLACK, 1);
  show_string_no_fc("T12AD", 0, 176, 1, BLACK, 1);
  show_string_no_fc("T12temp", 0, 184, 1, BLACK, 1);
  show_string_no_fc("PidOut", 0, 192, 1, BLACK, 1);
  show_string_no_fc("Sleep", 0, 200, 1, BLACK, 1);
  //show_number_int(MAX_PX, 125 , 176, 1, fc2, BLACK, 0);
  //show_number_int(MIN_PX, 205, 176, 1, fc2, BLACK, 0);
  //show_number_int(MIN_PY, 125, 186, 1, fc2, BLACK, 0);
  //show_number_int(MAX_PY, 205, 186, 1, fc2, BLACK, 0);
  show_number_int(t12_temp, 46, 184, 1, fc2, BLACK, 0);
  mylcd.Print_Number_Int(t12_ad, 40, 176, 5, '0', 10);
  show_number_int(pid_out, 46, 192, 1, fc2, BLACK, 0);
  show_number_int(sleep_count, 46, 200, 1, fc2, BLACK, 0);
  //show_number_int(digitalRead(sleep_pin), 40, 200, 1, fc2, BLACK, 0);
}

void pid_display() //pid界面
{
  if (display_state == PidDisplay)
  {
    mylcd.Set_Text_colour(255, 105, 180); //热情的粉红
    show_string_no_fc("P", 0, 0, 3, BLACK, 1);
    show_string_no_fc("I", 117, 0, 3, BLACK, 1);
    show_string_no_fc("D", 234, 0, 3, BLACK, 1);

    show_string("Back", 276, 225, 2, RED, BLACK, 1);

    mylcd.Fill_Rect(0, 30, 320, 24, BLACK); //用黑色矩形填充掉原来的数值
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
    mylcd.Set_Text_colour(255, 140, 0); //深橙色
    show_string_no_fc("SLEEP", CENTER, 0, 2, BLACK, 1);
    show_string_no_fc("temp", 50, 20, 2, BLACK, 1);
    show_string_no_fc("time", 220, 20, 2, BLACK, 1);

    show_string("Back", 276, 225, 2, RED, BLACK, 1);

    mylcd.Fill_Rect(50, 40, 320, 24, BLACK); //用黑色矩形填充掉原来的数值
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
    show_string("Screen Calibration", CENTER, 50, 2, GREEN, BLACK, 1);
    if (calibration_state == 1)
    {
      show_string_no_fc("MAX    MIN", CENTER, 80, 2, BLACK, 1);
      show_string_no_fc("X", 50, 120, 2, BLACK, 1);
      show_string_no_fc("Y", 50, 160, 2, BLACK, 1);

      mylcd.Set_Draw_color(DGRAY); //深灰色
      mylcd.Fill_Rectangle(0, 0, 4, 4);
      mylcd.Fill_Rectangle(315, 0, 319, 4);
      mylcd.Fill_Rectangle(315, 235, 319, 239);
      mylcd.Fill_Rectangle(0, 235, 4, 239);

      if (calibration_location > 4) show_string_no_fc("OK", 270, 135, 3, BLACK, 1);
    }
    //显示坐标开关
    else if (calibration_state == 0)
    {
      if (coordinates_state == 0) show_string("Coordinate Display", CENTER, 140, 2, DGRAY, BLACK, 1);
      else show_string_no_fc("Coordinate Display", CENTER, 140, 2, BLACK, 1);
    }
    show_string("Back", CENTER, 225, 2, RED, BLACK, 1);
    display_state = 0;
  }
  if (calibration_state == 1) //进入校准模式
  {
    mylcd.Set_Draw_color(GREEN);
    if (calibration_location == 1) mylcd.Fill_Rectangle(0, 0, 4, 4);
    else if (calibration_location == 2) mylcd.Fill_Rectangle(315, 0, 319, 4);
    else if (calibration_location == 3) mylcd.Fill_Rectangle(315, 235, 319, 239);
    else if (calibration_location == 4) mylcd.Fill_Rectangle(0, 235, 4, 239);

    show_number_int(calibration_count, CENTER, 20, 2, fc2, BLACK, 0);
    show_number_int(max_px, 100, 120, 2, fc2, BLACK, 0);
    show_number_int(min_px, 185, 120, 2, fc2, BLACK, 0);
    show_number_int(max_py, 100, 160, 2, fc2, BLACK, 0);
    show_number_int(min_py, 185, 160, 2, fc2, BLACK, 0);
  }
}

void keyboard_display() //键盘显示
{
  mylcd.Set_Text_colour(fc3);
  show_string_no_fc("1", keyboard_x, keyboard_y, 3, WHITE, 1);
  show_string_no_fc("2", keyboard_x + 50, keyboard_y, 3, WHITE, 1);
  show_string_no_fc("3", keyboard_x + 100, keyboard_y, 3, WHITE, 1);
  show_string_no_fc("<", keyboard_x + 150, keyboard_y , 3, WHITE, 1);

  show_string_no_fc("4", keyboard_x , keyboard_y - 50, 3, WHITE, 1);
  show_string_no_fc("5", keyboard_x + 50, keyboard_y - 50, 3, WHITE, 1);
  show_string_no_fc("6", keyboard_x + 100, keyboard_y - 50, 3, WHITE, 1);
  show_string_no_fc("0", keyboard_x + 150, keyboard_y - 50, 3, WHITE, 1);

  show_string_no_fc("7", keyboard_x , keyboard_y - 100, 3, WHITE, 1);
  show_string_no_fc("8", keyboard_x + 50, keyboard_y - 100, 3, WHITE, 1);
  show_string_no_fc("9", keyboard_x + 100, keyboard_y - 100, 3, WHITE, 1);
  if (dotFlag == 0) show_string_no_fc(".", keyboard_x + 150, keyboard_y - 100, 3, BLACK, 0);
  else if (dotFlag == 1) show_string(".", keyboard_x + 150, keyboard_y - 100, 3, YELLOW, BLACK , 0);
  show_string("Ok", keyboard_x + 135, keyboard_y - 129, 3, fc3, BLACK, 1);
}
