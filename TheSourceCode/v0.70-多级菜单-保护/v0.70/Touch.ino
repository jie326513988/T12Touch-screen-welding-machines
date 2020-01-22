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
    if (display_touch == MainDisplay) main_touch();
    else if (display_touch == SetDisplay1) set_touch();
    else if (display_touch == PidDisplay) pid_touch();
    else if (display_touch == SleepDisplay) sleep_touch();
  }
}

void main_touch()
{
  //加减温度
  if (px < 320 && px > 250 && py < 45 && py > 0)
  {
    set_temp += 10;
    sleep_count = 0;
    set_temp_limit();
    buzzer1();
    show_number_int_0(set_temp, 45, 150, 3, WHITE, BLACK  , 0); //刷新数值
  }
  else if (px < 320 && px > 250 && py < 110 && py > 70)
  {
    set_temp -= 10;
    sleep_count = 0;
    set_temp_limit();
    buzzer1();
    show_number_int_0(set_temp, 45, 150, 3, WHITE, BLACK  , 0); //刷新数值
  }
  //加热总开关
  else if (px < 320 && px > 248 && py < 166 && py > 144) //开启加热
  {
    t12_switch = 1; //开启总开关
    display_state = 1; //刷新一下
    buzzer1();
  }
  else if (px < 320 && px > 248 && py < 211 && py > 187) //关闭加热
  {
    t12_switch = 0; //关闭总开关
    display_state = 1; //刷新一下
    t12_temp_read_time = 800; //延长测量时间
    sleep_count = 0;
    buzzer1();
  }
  else if (px < 95 && px > 60 && py < 240 && py > 200)  //一键设置400度
  {
    buzzer1();
    set_temp = 400;
    sleep_count = 0;
  }
  else if (px < 155 && px > 120 && py < 240 && py > 200) //一键设置320度
  {
    buzzer1();
    set_temp = 320;
    sleep_count = 0;
  }
  else if (px < 215 && px > 180 && py < 240 && py > 200) //一键设置240度
  {
    buzzer1();
    set_temp = 240;
    sleep_count = 0;
  }
  //进入设置界面第一页
  else if (px < 40 && px > 0 && py < 240 && py > 200)
  {
    buzzer1();
    display_state = SetDisplay1;
    display_touch = SetDisplay1;
    mylcd.Fill_Screen(BLACK);
  }
}
void set_touch()
{
  //返回
  if (px < 320 && px > 280 && py < 240 && py > 210)
  {
    buzzer1();
    display_state = MainDisplay; //开启主界面
    display_touch = MainDisplay; //开启主界面触摸
    mylcd.Fill_Screen(BLACK); //画黑色清屏
  }
  //进入PID界面
  else if (px < 320 && px > 0 && py < 40 && py > 0)
  {
    buzzer1();
    display_state = PidDisplay; //开启pid界面
    display_touch = PidDisplay; //开启pid触摸
    mylcd.Fill_Screen(BLACK); //画黑色清屏
  }
  //进入Sleep界面
  else if (px < 320 && px > 0 && py < 40 * 2 && py > 0)
  {
    buzzer1();
    display_state = SleepDisplay; //开启pid界面
    display_touch = SleepDisplay; //开启pid触摸
    mylcd.Fill_Screen(BLACK); //画黑色清屏
  }
}
void pid_touch()
{
  //开启键盘触摸
  if (keyboard_touch_state == 1) keyboard_touch();
  //返回
  if (px < 320 && px > 280 && py < 240 && py > 210)
  {
    buzzer1();
    display_state = SetDisplay1; //显示设置界面第一页
    display_touch = SetDisplay1; //开启设置触摸第一页
    keyboard_state = 0; //关闭键盘显示
    keyboard_touch_state = 0;  //关闭键盘触摸
    keyboard_cache = 0; //键盘输入数值缓存清零
    dotFlag = 0; //键盘小数点归零
    change_num = 0; //pid触摸归零
    mylcd.Fill_Screen(BLACK); //画黑色清屏
  }
  else if (px < 80 && px > 0 && py < 50 && py > 0) //改P数值
  {
    buzzer1();
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    change_num = p_change_num; //可以更改P数值
    display_state = PidDisplay;  //刷新显示
  }
  else if (px < 205 && px > 115 && py < 50 && py > 0) //改I数值
  {
    buzzer1();
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    change_num = i_change_num; //可以更改i数值
    display_state = PidDisplay; //刷新显示
  }
  else if (px < 320 && px > 230 && py < 50 && py > 0) //改D数值
  {
    buzzer1();
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    change_num = d_change_num; //可以更改d数值
    display_state = PidDisplay; //刷新显示
  }
}
void sleep_touch()
{
  if (keyboard_touch_state == 1) keyboard_touch(); //开启键盘触摸
  if (px < 320 && px > 280 && py < 240 && py > 210) //返回
  {
    buzzer1();
    display_state = SetDisplay1; //显示设置界面第一页
    display_touch = SetDisplay1; //开启设置触摸第一页
    keyboard_state = 0; //关闭键盘显示
    keyboard_touch_state = 0;  //关闭键盘触摸
    keyboard_cache = 0; //键盘输入数值缓存清零
    dotFlag = 0; //键盘小数点归零
    change_num = 0; //pid触摸归零
    mylcd.Fill_Screen(BLACK); //画黑色清屏
  }
  else if (px < 120 && px > 0 && py < 50 && py > 20) //改sleep_temp数值
  {
    buzzer1();
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    change_num = sleep_temp_change_num; //可以更改sleep_temp
    display_state = SleepDisplay; //刷新显示
  }
  else if (px < 320 && px > 220 && py < 50 && py > 20) //改sleep_count_set数值
  {
    buzzer1();
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    change_num = sleep_count_set_change_num; //可以更改sleep_count_set
    display_state = SleepDisplay; //刷新显示
  }
}
void set_temp_limit() //设置温度限制
{
  if (set_temp < 0) set_temp = 0;
  else if (set_temp > 400) set_temp = 400;
}

void keyboard_touch() //键盘算法
{
  //按下1
  if (px < keyboard_x + 24 && px > keyboard_x && py < keyboard_y + 24 && py > keyboard_y)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (keyboard_cache <= 99 || dotFlag == 1)
        if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 1;
        else if (dotFlag == 1) keyboard_cache = keyboard_cache  + 0.1;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      delay_time = millis();
    }
  }
  //按下2
  else if (px < keyboard_x + 24 + 50 && px > keyboard_x + 50 && py < keyboard_y + 24 && py > keyboard_y)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (keyboard_cache <= 99 || dotFlag == 1)
        if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 2;
        else if (dotFlag == 1) keyboard_cache = keyboard_cache  + 0.2;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      delay_time = millis();
    }
  }
  //按下3
  else if (px < keyboard_x + 24 + 100 && px > keyboard_x + 100 && py < keyboard_y + 24 && py > keyboard_y)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (keyboard_cache <= 99 || dotFlag == 1)
        if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 3;
        else if (dotFlag == 1) keyboard_cache = keyboard_cache  + 0.3;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      delay_time = millis();
    }
  }
  //按下<
  else if (px < keyboard_x + 24 + 150 && px > keyboard_x + 150 && py < keyboard_y + 24 && py > keyboard_y)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (dotFlag == 0) keyboard_cache = int(keyboard_cache / 10);
      else if (dotFlag == 1) {
        keyboard_cache = int(keyboard_cache);
        dotFlag = 0;
      }
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      keyboard_state = 1; //刷新键盘
      delay_time = millis();
    }
  }
  //按下4
  else if (px < keyboard_x + 24 && px > keyboard_x && py < keyboard_y + 24 - 50 && py > keyboard_y - 50)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (keyboard_cache <= 99 || dotFlag == 1)
        if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 4;
        else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.4;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      delay_time = millis();
    }
  }
  //按下5
  else if (px < keyboard_x + 24 + 50 && px > keyboard_x + 50 && py < keyboard_y + 24 - 50 && py > keyboard_y - 50)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (keyboard_cache <= 99 || dotFlag == 1)
        if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 5;
        else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.5;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      delay_time = millis();
    }
  }
  //按下6
  else if (px < keyboard_x + 24 + 100 && px > keyboard_x + 100 && py < keyboard_y + 24 - 50 && py > keyboard_y - 50)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (keyboard_cache <= 99 || dotFlag == 1)
        if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 6;
        else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.6;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      delay_time = millis();
    }
  }
  //按下0
  else if (px < keyboard_x + 24 + 150 && px > keyboard_x + 150 && py < keyboard_y + 24 - 50 && py > keyboard_y - 50)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (keyboard_cache <= 99 || dotFlag == 1)
        if (dotFlag == 0) keyboard_cache = keyboard_cache * 10;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      delay_time = millis();
    }
  }
  //按下7
  else if (px < keyboard_x + 24 && px > keyboard_x && py < keyboard_y + 24 - 100 && py > keyboard_y - 100)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (keyboard_cache <= 99 || dotFlag == 1)
        if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 7;
        else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.7;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      delay_time = millis();
    }
  }
  //按下8
  else if (px < keyboard_x + 24 + 50 && px > keyboard_x + 50 && py < keyboard_y + 24 - 100 && py > keyboard_y - 100)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (keyboard_cache <= 99 || dotFlag == 1)
        if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 8;
        else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.8;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      delay_time = millis();
    }
  }
  //按下9
  else if (px < keyboard_x + 24 + 100 && px > keyboard_x + 100 && py < keyboard_y + 24 - 100 && py > keyboard_y - 100)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      if (keyboard_cache <= 99 || dotFlag == 1)
        if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 9;
        else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.9;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      delay_time = millis();
    }
  }
  //按下.
  else if (px < keyboard_x + 24 + 150 && px > keyboard_x + 150 && py < keyboard_y + 24 - 100 && py > keyboard_y - 100)
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      dotFlag = 1;
      show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
      buzzer1();
      keyboard_state = 1;
      delay_time = millis();
    }
  }
  //按下OK
  else if (px < keyboard_x + 135 + 34 && px > keyboard_x + 135  && py < keyboard_y - 129 + 24  && py > keyboard_y - 129 )
  {
    if (millis() - delay_time > 200) //不浪费CPU的消抖
    {
      switch (change_num)
      {
        case p_change_num:
          p = keyboard_cache;
          EEPROM.put(p_eeprom, p);
          break;
        case i_change_num:
          i = keyboard_cache;
          EEPROM.put(i_eeprom, i);
          break;
        case d_change_num:
          d = keyboard_cache;
          EEPROM.put(d_eeprom, d);
          break;
        case sleep_temp_change_num:
          sleep_temp = int(keyboard_cache);
          EEPROM.update(sleep_temp_eeprom, sleep_temp);
          break;
        case sleep_count_set_change_num:
          sleep_count_set = int(keyboard_cache);
          EEPROM.put(sleep_count_set_eeprom, sleep_count_set);
          break;
      }

      if (display_touch == PidDisplay) display_state = PidDisplay; //更新PID显示
      else if (display_touch == SleepDisplay) display_state = SleepDisplay; //更新PID显示
      mylcd.Fill_Rect(keyboard_x, keyboard_y - 129, 100, 24, BLACK); //用黑色刷新keyboard_cache

      buzzer1();
      change_num = 0; //数值标志位归零
      keyboard_cache = 0; //键盘数值缓存归零
      dotFlag = 0; //小数点归零
      keyboard_state = 1; //更新键盘显示
      delay_time = millis();
    }
  }
}
void buzzer1() //蜂鸣器
{
  digitalWrite(buzzer_pin, 1);
  delay(1);
  digitalWrite(buzzer_pin, 0);
}
