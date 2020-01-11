//增量式PID


void t12_pid()
{
  if (millis() - t12_pid_time < 100) return;
  t12_pid_time = millis();
  if (set_temp >= 10 && t12_switch == 1)
  {
    //ek0 = set_temp - t12_ad;
    ek0 = set_temp - t12_temp;
    if (ek0 > 0)
    {
      pid_out = float((p * ek0) - (i * ek1) + (d * ek2));
      if (pid_out > 255) pid_out = 255;
      ek2 = ek1;
      ek1 = ek0;
    }
    else pid_out = 0;
    analogWrite(t12_pwm_pin, pid_out);
  }
  else pid_out = 0;
}
