void t12_display()
{
  //if (millis() - display_time < 300) return;
  //display_time = millis();
  if (display_touch == MainDisplay) mainDisplay();
  else if (display_touch == SetDisplay1) setDisplay();
  else if (display_touch == PidDisplay) pid_display();
  else if (display_touch == SleepDisplay) sleep_display();
  if (keyboard_state == 1)
  {
    keyboard_display(); //显示一遍键盘
    keyboard_state = 0;
  }
}
