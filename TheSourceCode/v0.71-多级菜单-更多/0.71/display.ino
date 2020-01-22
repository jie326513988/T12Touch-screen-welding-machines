//怎么显示
void t12_display()
{
  if (display_touch == MainDisplay) mainDisplay();
  else if (display_touch == SetDisplay1) setDisplay();
  else if (display_touch == PidDisplay) pid_display();
  else if (display_touch == SleepDisplay) sleep_display();
  else if (display_touch == ScreenSetDisplay) screen_set_display();
  if (keyboard_state == 1) //显示一遍键盘
  {
    keyboard_display();
    keyboard_state = 0;
  }
}
