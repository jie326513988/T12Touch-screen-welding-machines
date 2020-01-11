//主界面的显示
void mainDisplay()
{
  if (main_display_state == 1)
  {
    uint8_t y = 16;
    show_string("T12_AD:", 0, y * 0, 2, RED, BLACK, 1);
    show_string("T12_temp:", 0, y * 1, 2, RED, BLACK, 1);
    show_string("NTC_temp:", 0,  y * 2, 2, RED, BLACK, 1);
    show_string("SetTemp:", 0,  y * 3, 2, RED, BLACK, 1);
    show_string("Volage:", 0,  y * 4, 2, RED, BLACK, 1);
    show_string("Ec:", 0,  y * 5, 2, RED, BLACK, 1);
    show_string("Pid_out:", 0,  y * 6, 2, RED, BLACK, 1);
    
    if (t12_switch == 0)
    {
      show_string("ON", 250,  144, 3, WHITE, WHITE, 1);
      show_string("OFF", 250,  188, 3, RED, WHITE, 1);
    }
    else if (t12_switch == 1)
    {
      show_string("ON", 250,  144, 3, RED, WHITE, 1);
      show_string("OFF", 250,  188, 3, WHITE, WHITE, 1);
    }

    show_string("Fps", 280, 0, 1, RED, BLACK, 1);

    mylcd.Set_Draw_color(GREEN);
    mylcd.Draw_Triangle(275, 20, 250, 60, 300, 60);
    mylcd.Draw_Triangle(275, 120, 250, 80, 300, 80);

    main_display_state = 0;
  }
  if (main_display_touch == 1)
  {
    uint8_t y = 16;
    show_number_int(t12_ad, 130, y * 0, 2, BLUE, BLACK  , 0);
    show_number_int(t12_temp, 130, y * 1, 2, BLUE, BLACK  , 0);
    show_number_float(1, ntc_temp, 130, y * 2, 2, BLUE, BLACK  , 0);
    show_number_int(set_temp, 130, y * 3, 2, BLUE, BLACK  , 0);
    show_number_float(1, volage, 130, y * 4, 2, BLUE, BLACK  , 0);
    show_number_float(1, ec, 130, y * 5, 2, BLUE, BLACK  , 0);
    show_number_int(pid_out, 130, y * 6, 2, BLUE, BLACK  , 0);
    
    show_number_int(fps_1, 280, 10, 1, BLUE, BLACK  , 0);
  }
}
