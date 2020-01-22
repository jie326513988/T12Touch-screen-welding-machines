//设置界面的显示
void setDisplay()
{
  if (display_state == SetDisplay1)
  {
    uint8_t y = 40;
    mylcd.Set_Text_colour(255, 105, 180); //热情的粉红
    show_string_no_fc("PID", CENTER, 0 * y, 3, BLACK, 1);

    mylcd.Set_Text_colour(60, 179, 113); //春天的绿色
    show_string_no_fc("Sleep", CENTER, 1 * y, 3, BLACK, 1);

    mylcd.Set_Text_colour(255, 140, 0); //  深橙色
    show_string_no_fc("Screen Set", CENTER, 2 * y, 3, BLACK, 1);

    mylcd.Set_Text_colour(221, 160, 221); //李子
    show_string_no_fc("V0.70 By:LCJ", CENTER, 233, 1, BLACK, 1);

    show_string("Back", 276, 225, 2, RED, BLACK, 1);

    display_state = 0;
  }
  show_string("T12AD", 0, 176, 1, fc1, BLACK, 1);
  show_number_int_5(t12_ad, 40, 176, 1, fc2, BLACK, 0);

  show_string("T12temp", 0, 184, 1, fc1, BLACK, 1);
  show_number_int(t12_temp, 45, 184, 1, fc2, BLACK, 0);

  show_string("PidOut", 0, 192, 1, fc1, BLACK, 1);
  show_number_int(pid_out, 40, 192, 1, fc2, BLACK, 0);

  show_string("Sleep", 0, 200, 1, fc1, BLACK, 1);
  show_number_int(sleep_count, 40, 200, 1, fc2, BLACK, 0);

  mylcd.Set_Draw_color(random(255), random(255), random(255));
  mylcd.Draw_Pixel(random(320), random(240));
}

void pid_display()
{
  if (display_state == PidDisplay)
  {
    show_string("P", 0, 0, 3, fc1, BLACK, 1);
    show_string("I", 117, 0, 3, fc1, BLACK, 1);
    show_string("D", 234, 0, 3, fc1, BLACK, 1);

    show_string("Back", 276, 225, 2, RED, BLACK, 1);

    mylcd.Fill_Rect(0, 30, 320, 24, BLACK); //用黑色矩形填充掉原来的数值
    show_number_float(p, 0, 30, 3, fc2, BLACK  , 0);
    show_number_float(i, 117, 30, 3, fc2, BLACK  , 0);
    show_number_float(d, 233, 30, 3, fc2, BLACK  , 0);
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
void sleep_display()
{
  if (display_state == SleepDisplay)
  {
    show_string("SLEEP", CENTER, 0, 2, fc1, BLACK, 1);
    show_string("temp", 50, 20, 2, fc1, BLACK, 1);
    show_string("time", 220, 20, 2, fc1, BLACK, 1);

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
    //校准屏幕
    show_string("Coordinate display", CENTER, 70, 2, fc1, BLACK, 1);

    //是否显示坐标
    if (coordinates_state == 0) show_string("screen calibration", CENTER, 120, 2, LGRAY, BLACK, 1);
    else show_string("screen calibration", CENTER, 120, 2, fc1, BLACK, 1);


    show_string("Back", CENTER, 225, 2, RED, BLACK, 1);

    display_state = 0;
  }
}
void keyboard_display() //键盘显示
{
  show_string("1", keyboard_x, keyboard_y, 3, fc3 , WHITE, 1);
  show_string("2", keyboard_x + 50, keyboard_y, 3, fc3, WHITE, 1);
  show_string("3", keyboard_x + 100, keyboard_y, 3, fc3, WHITE, 1);
  show_string("<", keyboard_x + 150, keyboard_y , 3, fc3, WHITE, 1);

  show_string("4", keyboard_x , keyboard_y - 50, 3, fc3, WHITE, 1);
  show_string("5", keyboard_x + 50, keyboard_y - 50, 3, fc3, WHITE, 1);
  show_string("6", keyboard_x + 100, keyboard_y - 50, 3, fc3, WHITE, 1);
  show_string("0", keyboard_x + 150, keyboard_y - 50, 3, fc3, WHITE, 1);

  show_string("7", keyboard_x , keyboard_y - 100, 3, fc3, WHITE, 1);
  show_string("8", keyboard_x + 50, keyboard_y - 100, 3, fc3, WHITE, 1);
  show_string("9", keyboard_x + 100, keyboard_y - 100, 3, fc3, WHITE, 1);
  if (dotFlag == 0) show_string(".", keyboard_x + 150, keyboard_y - 100, 3, fc3, BLACK, 0);
  else if (dotFlag == 1) show_string(".", keyboard_x + 150, keyboard_y - 100, 3, YELLOW, BLACK , 0);
  show_string("Ok", keyboard_x + 135, keyboard_y - 129, 3, fc3, BLACK, 1);
}
