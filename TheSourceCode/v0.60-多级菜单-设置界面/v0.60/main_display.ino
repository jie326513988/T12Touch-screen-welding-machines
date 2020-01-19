//主界面的显示
void mainDisplay()
{
  uint8_t y = 16;
  if (display_state == MainDisplay)
  {
    show_string("T12_AD:", 0, y * 0, 2, fc1, BLACK, 1);
    show_string("T12_temp:", 0, y * 1, 2, fc1, BLACK, 1);
    show_string("NTC_temp:", 0,  y * 2, 2, fc1, BLACK, 1);
    show_string("SetTemp:", 0,  y * 3, 2, fc1, BLACK, 1);
    show_string("Volage:", 0,  y * 4, 2, fc1, BLACK, 1);
    show_string("Ec:", 0,  y * 5, 2, fc1, BLACK, 1);
    show_string("Pid_out:", 0,  y * 6, 2, fc1, BLACK, 1);
    show_string("Sleep:", 0,  y * 7, 2, fc1, BLACK, 1);
    show_string("SET", CENTER,  219, 3, YELLOW, BLACK, 1);
    if (t12_switch == 0)
    {
      show_string("ON", 250,  144, 3, DGRAY, BLACK, 1);
      mylcd.Set_Text_colour(  255, 0, 0); //  纯红
      show_string_no_fc("OFF", 250,  188, 3, BLACK, 1);
    }
    else if (t12_switch == 1)
    {
      mylcd.Set_Text_colour(  255, 0, 0); //  纯红
      show_string_no_fc("ON", 250,  144, 3, BLACK, 1);
      show_string("OFF", 250,  188, 3, DGRAY, BLACK, 1);
    }

    //show_string("Fps", 280, 0, 1, RED, BLACK, 1);

    mylcd.Set_Draw_color(0, 191, 255);
    mylcd.Draw_Triangle(275, 0, 250, 40, 300, 40);//上三角
    mylcd.Draw_Triangle(275, 100, 250, 60, 300, 60);//下三角

    display_state = 0;
  }
  show_number_int(t12_ad, 130, y * 0, 2, fc2, BLACK  , 0);
  show_number_int(t12_temp, 130, y * 1, 2, fc2, BLACK  , 0);
  show_number_float(ntc_temp, 130, y * 2, 2, fc2, BLACK  , 0);
  show_number_int(set_temp, 130, y * 3, 2, fc2, BLACK  , 0);
  show_number_float(volage, 130, y * 4, 2, fc2, BLACK  , 0);
  show_number_float(ec, 130, y * 5, 2, fc2, BLACK  , 0);
  show_number_int(pid_out, 130, y * 6, 2, fc2, BLACK  , 0);
  show_number_int(sleep_count, 130, y * 7, 2, fc2, BLACK  , 0);
  //show_number_int(t12_temp_read_time, 130, y * 8, 2, fc2, BLACK  , 0);
  //show_number_int(fps_1, 280, 10, 1, fc2, BLACK  , 0);
}
