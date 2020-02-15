//增量式PID
void t12_pid()
{
  if (set_temp >= 40 && t12_switch == 1) //设置温度大于40度&&总开关开启
  {
    //ek0 = set_temp - t12_ad;
    ek0 = set_temp - t12_temp;  //计算现在的差值
    if (ek0 < 0) //差值0度以下
    {
      pid_out = 0;
      digitalWrite(t12_pwm_pin, 0);
    }
    else if (ek0 > 10)  //差值大于10度
    {
      pid_out = 511;
      digitalWrite(t12_pwm_pin, 1);
      t12_temp_read_time = 900;
    }
    else if (ek0 <= 10  && ek0 >= 0)   //差值0-10度内
    {
      t12_temp_read_time = 200;  //缩短采样时间
      pid_out = float((p * ek0) - (i * ek1) + (d * ek2) + ((0.0012 * t12_temp + 0.042) * t12_temp)); //最后为0差值补偿
      //pid_out = float((p * ek0) - (i * ek1) + (d * ek2));
      //pid_out = float((p * (ek0 - ek1)) + (i * ek0) + (d * (ek0 - 2 * ek1 + ek2)));
      if (pid_out > 511) pid_out = 511;
      else if (pid_out < 0)pid_out = 0;
      ek2 = ek1;
      ek1 = ek0;
      pwm1(pid_out); //使用相位和频率校正模式，61HZ，滴滴声大幅下降
      //analogWrite(t12_pwm_pin, pid_out); //使用自带的PWM，490HZ，有滴滴声
    }
  }
  else 
  {
    pid_out = 0;
    digitalWrite(t12_pwm_pin, 0);
  }
  ec_read(); //读取电流
}
