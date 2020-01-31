//休眠
void sleep_read()
{
  if ((millis() - sleep_read_time < 900) || t12_switch == 0) return; //定时运行
  sleep_read_time = millis();
  if (sleep_state == digitalRead(sleep_pin)) sleep_count++; //烙铁没动，计数增加
  else //烙铁动了，计数清零
  {
    sleep_state = !sleep_state;
    sleep_count = 0;
    if (set_temp == sleep_temp && sleep_temp_cache > sleep_temp) //如果之前休眠了就将温度设置回工作温度
    {
      set_temp = sleep_temp_cache;
      sleep_temp_cache = 0;
      digitalWrite(buzzer_pin, 1);
      delay(20);
      digitalWrite(buzzer_pin, 0);
    }
  }
  if (sleep_count == sleep_count_set && set_temp > sleep_temp) //达到休眠的阈值，进入休眠温度
  {
    sleep_temp_cache = set_temp;  //休眠前将温度记录下来。
    set_temp = sleep_temp;        //将温度调至休眠温度
  }
  else if (sleep_count > 1800)  //半小时没操作，关闭加热
  {
    set_temp = sleep_temp_cache;
    sleep_temp_cache = 0;
    t12_switch = 0;
    sleep_count = 0;
    display_state = MainDisplay;
  }
}
