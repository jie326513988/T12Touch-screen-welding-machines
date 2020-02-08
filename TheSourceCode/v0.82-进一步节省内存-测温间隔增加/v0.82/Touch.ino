//触摸决策
/*
  打开TouchScreen.cpp修改成，看个人需要修改
  #define NUMSAMPLES 20  较快的触摸响应，精度适中可能会有误触，占用更多内存
  #define NUMSAMPLES 2   最慢的触摸响应，精度最高，占用更少内存
  #define NUMSAMPLES 1   最快的触摸响应，精度最低，占用最少内存

  因为是横屏,所以
  max_px --> py的0
  min_px --> py的240
  max_py --> px的320
  min_py --> px的0
   ------------------------------------------
   - max_px/min_py            max_px/max_py -
   -                                        -
   -                                        -
   -                                        -
   -                                        -
   -                                        -
   - min_px/min_py           min_px/ max_py -
   ------------------------------------------
*/

void touch()
{
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if (p.z < MAX_PZ && p.z > MIN_PZ && p.x < 1020 && p.x > 60 && p.y < 1020 && p.y > 60)
  {
    //py = map(p.x, 910, 125, 0, 240);
    //px = map(p.y, 85, 895, 0, 320);
    py = map(p.x, MAX_PX, MIN_PX, 0, 240);
    px = map(p.y, MIN_PY, MAX_PY, 0, 320);
    uint8_t x = 0;
    uint8_t y = 216;
    if (coordinates_state == 1) {
      show_string("p.x", x, y, 1, fc1, BLACK, 1);
      show_string_no_fc("p.y", x, y + 8, 1, BLACK, 1);
      show_string_no_fc("p.z", x, y + 16, 1, BLACK, 1);
      show_string_no_fc("px", x + 45, y, 1, BLACK, 1);
      show_string_no_fc("py", x + 45, y + 8, 1, BLACK, 1);
      show_number_int(p.x, x + 24, y, 1, fc2, BLACK  , 0);
      show_number_int(p.y, x + 24, y + 8, 1, fc2, BLACK  , 0);
      show_number_int(p.z, x + 24, y + 16, 1, fc2, BLACK  , 0);
      show_number_int(px, x + 62, y, 1, fc2, BLACK  , 0);
      show_number_int(py, x + 62, y + 8, 1, fc2, BLACK  , 0);
    }
    //屏幕校准计算
    switch (calibration_location) {
      case 1:
        max_px = p.x;
        min_py = p.y;
        break;
      case 2:
        max_px = (max_px + p.x) / 2;
        max_py = p.y;
        break;
      case 3:
        min_px = p.x;
        max_py = (max_py + p.y) / 2;
        break;
      case 4:
        min_px = (min_px + p.x) / 2;
        min_py = (min_py + p.y) / 2;
        break;
    }
    //各功能界面的触屏操作
    if (display_touch == MainDisplay) main_touch();
    else if (display_touch == SetDisplay1) set_touch();
    else if (display_touch == PidDisplay) pid_touch();
    else if (display_touch == SleepDisplay) sleep_touch();
    else if (display_touch == ScreenSetDisplay) screen_set_touch();

    //不让键盘按键运行的太快
    if (millis() - touch_time > 120) {
      if (keyboard_touch_state == 1) keyboard_touch();  //键盘
      touch_time = millis();
    }
  }
}

void main_touch() //主界面的触摸
{
  //加减温度
  if (millis() - touch_time > 60) //不让调温按键运行太快
  {
    if (px < 320 && px > 240 && py < 45 && py > 0) //加温
    {
      set_temp += 10;
      sleep_count = 0;
      set_temp_limit();
      buzzer(1);
      //刷新设置温度数值
      my_lcd.Set_Text_Size(3);
      my_lcd.Set_Text_colour(WHITE);
      my_lcd.Print_Number_Int(set_temp, 45, 150, 4, '0', 10);
    }
    else if (px < 320 && px > 240 && py < 110 && py > 70) //减温
    {
      set_temp -= 10;
      sleep_count = 0;
      set_temp_limit();
      buzzer(1);
      //刷新设置温度数值
      my_lcd.Set_Text_Size(3);
      my_lcd.Set_Text_colour(WHITE);
      my_lcd.Print_Number_Int(set_temp, 45, 150, 4, '0', 10);
    }
    touch_time = millis();
  }
  //加热总开关
  if (px < 320 && px > 248 && py < 166 && py > 144) //开启加热
  {
    t12_switch = 1; //开启总开关
    display_state = 1; //刷新一下
    buzzer(1);
  }
  else if (px < 320 && px > 248 && py < 211 && py > 187) //关闭加热
  {
    t12_switch = 0; //关闭总开关
    display_state = 1; //刷新一下
    t12_temp_read_time = 600; //延长测量时间
    sleep_count = 0;
    buzzer(1);
  }
  //一键设置400度
  else if (px < 100 && px > 55 && py < 240 && py > 200)
  {
    buzzer(1);
    set_temp = 400;
    sleep_count = 0;
  }
  //一键设置320度
  else if (px < 160 && px > 115 && py < 240 && py > 200)
  {
    buzzer(1);
    set_temp = 320;
    sleep_count = 0;
  }
  //一键设置240度
  else if (px < 220 && px > 175 && py < 240 && py > 200)
  {
    buzzer(1);
    set_temp = 240;
    sleep_count = 0;
  }
  //进入设置界面第一页
  else if (px < 40 && px > 0 && py < 240 && py > 200)
  {
    buzzer(1);
    display_state = SetDisplay1;
    display_touch = SetDisplay1;
    my_lcd.Fill_Screen(BLACK);
  }
}
void set_touch() //设置界面的触摸
{
  //返回
  if (px < 320 && px > 280 && py < 240 && py > 210)
  {
    buzzer(1);
    display_state = MainDisplay; //开启主界面
    display_touch = MainDisplay; //开启主界面触摸
    my_lcd.Fill_Screen(BLACK); //画黑色清屏
  }
  //进入PID界面
  else if (px < 320 && px > 0 && py < 30 && py > 0)
  {
    buzzer(1);
    display_state = PidDisplay; //开启pid界面
    display_touch = PidDisplay; //开启pid触摸
    my_lcd.Fill_Screen(BLACK); //画黑色清屏
  }
  //进入Sleep界面
  else if (px < 320 && px > 0 && py < 65  && py > 35)
  {
    buzzer(1);
    display_state = SleepDisplay; //开启pid界面
    display_touch = SleepDisplay; //开启pid触摸
    my_lcd.Fill_Screen(BLACK); //画黑色清屏
  }
  //进入屏幕设置界面
  else if (px < 320 && px > 0 && py < 110  && py > 75)
  {
    buzzer(1);
    display_state = ScreenSetDisplay; //开启pid界面
    display_touch = ScreenSetDisplay; //开启pid触摸
    my_lcd.Fill_Screen(BLACK); //画黑色清屏
  }
}
void pid_touch() //PID界面的触摸
{
  //返回
  if (px < 320 && px > 280 && py < 240 && py > 210)
  {
    buzzer(1);
    display_state = SetDisplay1; //显示设置界面第一页
    display_touch = SetDisplay1; //开启设置触摸第一页
    keyboard_state = 0; //关闭键盘显示
    keyboard_touch_state = 0;  //关闭键盘触摸
    keyboard_cache = 0; //键盘输入数值缓存清零
    dotFlag = 0; //键盘小数点归零
    change_num = 0; //数值标志位归零
    my_lcd.Fill_Screen(BLACK); //画黑色清屏
  }
  else if (px < 80 && px > 0 && py < 50 && py > 0) //改P数值
  {
    buzzer(1);
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    change_num = p_change_num; //可以更改P数值
    display_state = PidDisplay;  //刷新显示
  }
  else if (px < 205 && px > 115 && py < 50 && py > 0) //改I数值
  {
    buzzer(1);
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    change_num = i_change_num; //可以更改i数值
    display_state = PidDisplay; //刷新显示
  }
  else if (px < 320 && px > 230 && py < 50 && py > 0) //改D数值
  {
    buzzer(1);
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    change_num = d_change_num; //可以更改d数值
    display_state = PidDisplay; //刷新显示
  }
}
void sleep_touch() //休眠界面的触摸
{
  if (px < 320 && px > 280 && py < 240 && py > 210) //返回
  {
    buzzer(1);
    display_state = SetDisplay1; //显示设置界面第一页
    display_touch = SetDisplay1; //开启设置触摸第一页
    keyboard_state = 0; //关闭键盘显示
    keyboard_touch_state = 0;  //关闭键盘触摸
    keyboard_cache = 0; //键盘输入数值缓存清零
    dotFlag = 0; //键盘小数点归零
    change_num = 0; //数值标志位归零
    my_lcd.Fill_Screen(BLACK); //画黑色清屏
  }
  else if (px < 120 && px > 0 && py < 50 && py > 20) //改sleep_temp数值
  {
    buzzer(1);
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    change_num = sleep_temp_change_num; //可以更改sleep_temp
    display_state = SleepDisplay; //刷新显示
  }
  else if (px < 320 && px > 220 && py < 50 && py > 20) //改sleep_count_set数值
  {
    buzzer(1);
    keyboard_state = 1; //调出键盘显示
    keyboard_touch_state = 1; //开启键盘触摸
    change_num = sleep_count_set_change_num; //可以更改sleep_count_set
    display_state = SleepDisplay; //刷新显示
  }
}
void screen_set_touch() //屏幕设置界面的触摸
{
  if (px < 175 && px > 145 && py < 240 && py > 210) //返回
  {
    buzzer(1);
    display_state = SetDisplay1; //显示设置界面第一页
    display_touch = SetDisplay1; //开启设置触摸第一页
    calibration_state = 0; //屏幕校准状态归零
    calibration_location = 0; //屏幕校准位置归零
    calibration_count = 0; //校准计数清零
    my_lcd.Fill_Screen(BLACK); //画黑色清屏
  }
  else if (px < 270 && px > 50 && py < 160 && py > 130 && calibration_state == 0) //开关显示坐标
  {
    buzzer(1);
    coordinates_state = !coordinates_state;
    my_lcd.Fill_Screen(BLACK); //画黑色清屏
    display_state = ScreenSetDisplay;
  }
  else if (px < 270 && px > 50 && py < 70  && py > 45) //开关校准屏幕
  {
    buzzer(1);
    calibration_state = !calibration_state; //开启校准模式
    calibration_location = 1;//校准位置1，左上角开始
    min_px = MIN_PX, max_px = MAX_PX, min_py = MIN_PY, max_py = MAX_PY;
    calibration_count = 0; //校准计数清零
    my_lcd.Fill_Screen(BLACK); //画黑色清屏
    display_state = ScreenSetDisplay;
  }
  //校准屏幕的操作
  if ( calibration_location <= 4 && calibration_location > 0)
  {
    calibration_count ++;
    if (calibration_count > 400) {
      buzzer(20);
      calibration_location ++;
      calibration_count = 0;
      display_state = ScreenSetDisplay;
    }
  }
  //按下OK
  else if (px < 320 && px > 270 && py < 160 && py > 135 && calibration_location > 4)
  {
    if ((max_px - min_px) > 760 && (max_py - min_py) > 760)
    {
      MIN_PX = min_px;
      MAX_PX = max_px;
      MIN_PY = min_py;
      MAX_PY = max_py;
      EEPROM.put(MIN_PX_eeprom, MIN_PX);
      EEPROM.put(MAX_PX_eeprom, MAX_PX);
      EEPROM.put(MIN_PY_eeprom, MIN_PY);
      EEPROM.put(MAX_PY_eeprom, MAX_PY);
      calibration_location = 1; //校准位置1
      display_state = ScreenSetDisplay; //刷新显示
      my_lcd.Fill_Screen(BLACK); //画黑色清屏
      buzzer(20);
    }
    else {
      my_lcd.Fill_Screen(BLACK); //画黑色清屏
      calibration_location = 1; //校准位置1
      display_state = ScreenSetDisplay;
      for (uint8_t a = 0; a < 3; a++) {
        buzzer(20);
        delay(210);
        wdt_reset();
      }
    }
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
  if (px < keyboard_x1 + 25 && px > keyboard_x1 - 15 && py < keyboard_y1 + 32  && py > keyboard_y1 - 8 )
  {
    if (keyboard_cache <= 99 || dotFlag == 1)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 1;
      else if (dotFlag == 1) keyboard_cache = keyboard_cache  + 0.1;
    buzzer(1);
  }

  //按下2
  else if (px < keyboard_x2 + 25 && px > keyboard_x2 - 15  && py < keyboard_y1 + 32 && py > keyboard_y1 - 8)
  {

    if (keyboard_cache <= 99 || dotFlag == 1)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 2;
      else if (dotFlag == 1) keyboard_cache = keyboard_cache  + 0.2;
    buzzer(1);
  }
  //按下3
  else if (px < keyboard_x3 + 25 && px > keyboard_x3 - 15 && py < keyboard_y1 + 32 && py > keyboard_y1 - 8)
  {
    if (keyboard_cache <= 99 || dotFlag == 1)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 3;
      else if (dotFlag == 1) keyboard_cache = keyboard_cache  + 0.3;
    buzzer(1);
  }
  //按下<
  else if (px < keyboard_x4 + 25 && px > keyboard_x4 - 15 && py < keyboard_y1 + 32 && py > keyboard_y1 - 8)
  {
    if (dotFlag == 0) keyboard_cache = int(keyboard_cache / 10);
    else if (dotFlag == 1) {
      keyboard_cache = int(keyboard_cache);
      dotFlag = 0;
    }
    buzzer(1);
    keyboard_state = 1; //刷新键盘
  }
  //按下4
  else if (px < keyboard_x1 + 25 && px > keyboard_x1 - 15 && py < keyboard_y2 + 32 && py > keyboard_y2 - 8)
  {
    if (keyboard_cache <= 99 || dotFlag == 1)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 4;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.4;
    buzzer(1);
  }
  //按下5
  else if (px < keyboard_x2 + 25 && px > keyboard_x2 - 15 && py < keyboard_y2 + 32 && py > keyboard_y2 - 8)
  {
    if (keyboard_cache <= 99 || dotFlag == 1)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 5;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.5;
    buzzer(1);
  }
  //按下6
  else if (px < keyboard_x3 + 25 && px > keyboard_x3 - 15 && py < keyboard_y2 + 32 && py > keyboard_y2 - 8)
  {
    if (keyboard_cache <= 99 || dotFlag == 1)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 6;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.6;
    buzzer(1);
  }
  //按下0
  else if (px < keyboard_x4 + 25 && px > keyboard_x4 - 15 && py < keyboard_y2 + 32 && py > keyboard_y2 - 8)
  {
    if (keyboard_cache <= 99 || dotFlag == 1)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10;
    buzzer(1);
  }
  //按下7
  else if (px < keyboard_x1 + 25 && px > keyboard_x1 - 15 && py < keyboard_y3 + 32 && py > keyboard_y3 - 8)
  {
    if (keyboard_cache <= 99 || dotFlag == 1)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 7;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.7;
    buzzer(1);
  }
  //按下8
  else if (px < keyboard_x2 + 25 && px > keyboard_x2 - 15 && py < keyboard_y3 + 32 && py > keyboard_y3 - 8)
  {
    if (keyboard_cache <= 99 || dotFlag == 1)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 8;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.8;
    buzzer(1);
  }
  //按下9
  else if (px < keyboard_x3 + 25 && px > keyboard_x3 - 15 && py < keyboard_y3 + 32 && py > keyboard_y3 - 8)
  {
    if (keyboard_cache <= 99 || dotFlag == 1)
      if (dotFlag == 0) keyboard_cache = keyboard_cache * 10 + 9;
      else if (dotFlag == 1)keyboard_cache = keyboard_cache  + 0.9;
    buzzer(1);
  }
  //按下.
  else if (px < keyboard_x4 + 25 && px > keyboard_x4 - 15 && py < keyboard_y3 + 32 && py > keyboard_y3 - 8)
  {
    buzzer(1);
    dotFlag = 1;
    keyboard_state = 1;
  }
  //按下OK
  else if (px < keyboard_x + 135 + 34 && px > keyboard_x + 135  && py < keyboard_y - 129 + 24  && py > keyboard_y - 129 )
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
    else if (display_touch == SleepDisplay) display_state = SleepDisplay; //更新sleep显示
    my_lcd.Fill_Rect(keyboard_x, keyboard_y - 129, 100, 24, BLACK); //用黑色刷新keyboard_cache

    buzzer(1);
    change_num = 0; //数值标志位归零
    keyboard_cache = 0; //键盘数值缓存归零
    dotFlag = 0; //小数点归零
    keyboard_state = 1; //更新键盘显示
  }
  //即时显示数值
  if (px < keyboard_x + 175 && px > keyboard_x - 15 && py < keyboard_y + 22 && py > keyboard_y - 128) {
    show_number_float(keyboard_cache, keyboard_x + 5, keyboard_y - 129, 3, LGRAY, BLACK, 0);
  }
}
void buzzer(uint8_t time1) //蜂鸣器
{
  //直接操作寄存器节省内存
  //数据方向寄存器DDRX，端口数据寄存器PORTX，端口输入引脚地址PINX
  //11号引脚为PB3
  //只要向该寄存器中对应位写入1
  //就可以翻转对应端口的输出引脚状态
  /*digitalWrite(buzzer_pin, 1);
    delay(time1);
    digitalWrite(buzzer_pin, 0);*/
  bitWrite(PINB, 3, 1);
  delay(time1);
  bitWrite(PINB, 3, 1);
}
