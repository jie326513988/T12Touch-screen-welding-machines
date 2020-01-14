//增量式PID
void t12_pid()
{
  //uint16_t time0 = micros();
  if (millis() - t12_pid_time < 100) return;
  t12_pid_time = millis();
  if (set_temp >= 10 && t12_switch == 1)
  {
    //ek0 = set_temp - t12_ad;
    ek0 = set_temp - t12_temp;
    if (ek0 <= 0) pid_out = 0;
    else if (ek0 > 10)
    {
      t12_temp_read_time = 800;
      pid_out = 255;
    }
    else if (ek0 <= 10)
    {
      t12_temp_read_time = 200;
      pid_out = float((p * ek0) - (i * ek1) + (d * ek2));
      if (pid_out > 255) pid_out = 255;
      ek2 = ek1;
      ek1 = ek0;
    }
    analogWrite(t12_pwm_pin, pid_out);
  }
  else pid_out = 0;
  //uint16_t time1 = micros();
  //Serial.println(time1 - time0);
}
