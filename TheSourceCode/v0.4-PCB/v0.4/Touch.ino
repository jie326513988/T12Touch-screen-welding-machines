//触摸时的操作
void touch()
{
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

    show_string("p.x:", 0, 172, 2, RED, BLACK, 1);
    show_number_int(p.x, 60, 172, 2, BLUE, BLACK  , 0);

    show_string("p.y:", 0, 198, 2, RED, BLACK, 1);
    show_number_int(p.y, 60, 198, 2, BLUE, BLACK  , 0);

    show_string("p.z:", 0, 224, 2, RED, BLACK, 1);
    show_number_int(p.z, 60, 224, 2, BLUE, BLACK  , 0);

    if (main_display_touch == 1)//在主屏幕时的触屏操作
    {
      if (p.x < 220 && p.x > 180 && p.y < 306 && p.y > 256)
      {
        set_temp += 10;
        set_temp_limit();
        //analogWrite(t12_pwm_pin, set_temp);
      }
      else if (p.x < 160 && p.x > 120 && p.y < 306 && p.y > 256)
      {
        set_temp -= 10;
        set_temp_limit();
        //analogWrite(t12_pwm_pin, set_temp);
      }
      if (p.x < 95 && p.x > 65 && p.y < 320 && p.y > 250)
      {
        t12_switch = 1;
        main_display_state = 1;
      }
      else if (p.x < 50 && p.x > 20 && p.y < 320 && p.y > 250)
      {
        t12_switch = 0;
        main_display_state = 1;
      }
    }

    buzzer();
  }
}
void set_temp_limit()
{
  if (set_temp < 0) set_temp = 0;
  else if (set_temp > 1023) set_temp = 1020;
}
