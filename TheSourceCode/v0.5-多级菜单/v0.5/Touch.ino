//触摸时的操作
int px, py;
void touch()
{
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
  {
    py = map(p.x, 910, 125, 0, 240);
    px = map(p.y, 85, 895, 0, 320);
    uint8_t x = 0;
    uint8_t y = 216;
    show_string("p.x:", 0, y, 1, fc1, BLACK, 1);
    show_number_int(p.x, x + 24, y, 1, fc2, BLACK  , 0);

    show_string("p.y:", 0, y + 8, 1, fc1, BLACK, 1);
    show_number_int(p.y, x + 24, y + 8, 1, fc2, BLACK  , 0);

    show_string("p.z:", 0, y + 16, 1, fc1, BLACK, 1);
    show_number_int(p.z, x + 24, y + 16, 1, fc2, BLACK  , 0);

    show_string("px:", x + 50, y, 1, fc1, BLACK, 1);
    show_number_int(px, x + 66, y, 1, fc2, BLACK  , 0);

    show_string("py:", x + 50, y + 8, 1, fc1, BLACK, 1);
    show_number_int(py, x + 66, y + 8, 1, fc2, BLACK  , 0);

    //在主屏幕时的触屏操作
    if (main_display_touch == 1) main_touch();
    else if (set_display_touch == 1) set_touch();
  }
}

void main_touch()
{
  //加减温度
  if (px < 300 && px > 250 && py < 40 && py > 0)
  {
    set_temp += 10;
    set_temp_limit();
    buzzer1();
    show_number_int(set_temp, 130, 48, 2, WHITE, BLACK  , 0); //更新设置温度的显示
  }
  else if (px < 300 && px > 250 && py < 100 && py > 60)
  {
    set_temp -= 10;
    set_temp_limit();
    buzzer1();
    show_number_int(set_temp, 130, 48, 2, WHITE, BLACK  , 0); //更新设置温度的显示
  }
  //加热总开关
  else if (px < 320 && px > 250 && py < 166 && py > 144) //开启加热
  {
    t12_switch = 1;
    main_display_state = 1;
    buzzer1();
  }
  else if (px < 320 && px > 250 && py < 211 && py > 187) //关闭加热
  {
    t12_switch = 0;
    main_display_state = 1;
    t12_temp_read_time = 800;
    buzzer1();
  }
  //进入设置界面
  else if (px < 204 && px > 147 && py < 240 && py > 216)
  {
    buzzer1();
    main_display_touch = 0;
    set_display_touch = 1;
    set_display_state = 1;
    mylcd.Fill_Screen(BLACK);
  }
}

void set_touch()
{
  //返回
  if (px < 320 && px > 280 && py < 240 && py > 220)
  {
    buzzer1();
    main_display_touch = 1;
    set_display_touch = 0;
    main_display_state = 1;
    keyboard_state = 0;
    keyboard_cache = 0;
    keyboard_touch_state = 0;
    dotFlag = 0;
    mylcd.Fill_Screen(BLACK);
    p_change = 0; i_change = 0; d_change = 0;
  }
  else if (px < 80 && px > 0 && py < 50 && py > 0) //改P数值
  {
    buzzer1();
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    p_change = 1; //可以更改P数值
    i_change = 0;
    d_change = 0;
  }
  else if (px < 205 && px > 115 && py < 50 && py > 0) //改I数值
  {
    buzzer1();
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    p_change = 0; //可以更改i数值
    i_change = 1;
    d_change = 0;
  }
  else if (px < 320 && px > 230 && py < 50 && py > 0) //改D数值
  {
    buzzer1();
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    p_change = 0; //可以更改d数值
    i_change = 0;
    d_change = 1;
  }
  else if (keyboard_touch_state == 1) keyboard_touch();
}

void set_temp_limit()
{
  if (set_temp < 0) set_temp = 0;
  else if (set_temp > 1000) set_temp = 1000;
}

void buzzer1()
{
  digitalWrite(buzzer_pin, 1);
  delay(1);
  digitalWrite(buzzer_pin, 0);
}

void keyboard_touch() //键盘算法
{
  //按下1
  if (px < keyboard_x + 24 && px > keyboard_x && py < keyboard_y + 24 && py > keyboard_y)
  {
    if (keyboard_cache <= 99)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 1;
      else if (dotFlag == 1) keyboard_cache = keyboard_cache  + 0.1;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    delay(100);
  }
  //按下2
  else if (px < keyboard_x + 24 + 50 && px > keyboard_x + 50 && py < keyboard_y + 24 && py > keyboard_y)
  {
    if (keyboard_cache <= 99)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 2;
      else if (dotFlag == 1) keyboard_cache = keyboard_cache  + 0.2;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    delay(100);
  }
  //按下3
  else if (px < keyboard_x + 24 + 100 && px > keyboard_x + 100 && py < keyboard_y + 24 && py > keyboard_y)
  {
    if (keyboard_cache <= 99)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 3;
      else if (dotFlag == 1) keyboard_cache = keyboard_cache  + 0.3;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    delay(100);
  }
  //按下<
  else if (px < keyboard_x + 24 + 150 && px > keyboard_x + 150 && py < keyboard_y + 24 && py > keyboard_y)
  {
    if (dotFlag == 0) keyboard_cache = int(keyboard_cache / 10);
    else if (dotFlag == 1) {
      keyboard_cache = int(keyboard_cache);
      dotFlag = 0;
    }
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    keyboard_state = 1;
    delay(100);
  }
  //按下4
  else if (px < keyboard_x + 24 && px > keyboard_x && py < keyboard_y + 24 - 50 && py > keyboard_y - 50)
  {
    if (keyboard_cache <= 99)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 4;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.4;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    delay(100);
  }
  //按下5
  else if (px < keyboard_x + 24 + 50 && px > keyboard_x + 50 && py < keyboard_y + 24 - 50 && py > keyboard_y - 50)
  {
    if (keyboard_cache <= 99)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 5;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.5;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    delay(100);
  }
  //按下6
  else if (px < keyboard_x + 24 + 100 && px > keyboard_x + 100 && py < keyboard_y + 24 - 50 && py > keyboard_y - 50)
  {
    if (keyboard_cache <= 99)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 6;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.6;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    delay(100);
  }
  //按下0
  else if (px < keyboard_x + 24 + 150 && px > keyboard_x + 150 && py < keyboard_y + 24 - 50 && py > keyboard_y - 50)
  {
    if (keyboard_cache <= 99)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    delay(100);
  }
  //按下7
  else if (px < keyboard_x + 24 && px > keyboard_x && py < keyboard_y + 24 - 100 && py > keyboard_y - 100)
  {
    if (keyboard_cache <= 99)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 7;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.7;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    delay(100);
  }
  //按下8
  else if (px < keyboard_x + 24 + 50 && px > keyboard_x + 50 && py < keyboard_y + 24 - 100 && py > keyboard_y - 100)
  {
    if (keyboard_cache <= 99)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 8;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.8;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    delay(100);
  }
  //按下9
  else if (px < keyboard_x + 24 + 100 && px > keyboard_x + 100 && py < keyboard_y + 24 - 100 && py > keyboard_y - 100)
  {
    if (keyboard_cache <= 99)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 9;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.9;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    delay(100);
  }
  //按下.
  else if (px < keyboard_x + 24 + 150 && px > keyboard_x + 150 && py < keyboard_y + 24 - 100 && py > keyboard_y - 100)
  {
    dotFlag = 1;
    show_number_float(1, keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
    buzzer1();
    keyboard_state = 1;
    delay(100);
  }
  //按下OK
  else if (px < keyboard_x + 135 + 34 && px > keyboard_x + 135  && py < keyboard_y - 129 + 24  && py > keyboard_y - 129 )
  {
    if (p_change == 1) {
      p = keyboard_cache;
      EEPROM.put(p_eeprom, p);
    }
    else if (i_change == 1) {
      i = keyboard_cache;
      EEPROM.put(i_eeprom, i);
    }
    else if (d_change == 1) {
      d = keyboard_cache;
      EEPROM.put(d_eeprom, d);
    }
    buzzer1();
    p_change = 0; i_change = 0; d_change = 0;
    keyboard_cache = 0;
    dotFlag = 0;
    //keyboard_state = 0; //关闭显示键盘
    //keyboard_touch_state = 0; //关闭键盘触摸
    //set_display_state = 1; //更新设置显示
    keyboard_state = 1; //更新键盘显示
    mylcd.Set_Draw_color(BLACK);//刷新pid的背景
    mylcd.Fill_Rectangle(0, 30, 320, 30 + 24);
    mylcd.Set_Draw_color(BLACK);//刷新keyboard_cache的背景
    mylcd.Fill_Rectangle(keyboard_x, keyboard_y - 129, keyboard_x + 100, keyboard_y - 129 + 24);
    delay(50);
  }
}
