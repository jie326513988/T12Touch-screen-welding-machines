//温度 电压 电流 读取
/*
  串联电阻的中点电压计算公式
  Eout 中点电压
  Vcc 输入电压（两端施加电压）
  R1、R2 两个串联的分压电阻
  Eout = Vcc * R2/(R1+R2) R1靠近电源 R2靠近地
*/
void timing_volage_ntc() //定时读取电源电压和ntc温度
{
  if (millis() - volage_time > 3000)
  {
    volage_read(); //读取电源电压
    ntc_temp_read(); //读取ntc温度
    if (volage >= 25 || ntc_temp >= 80) t12_switch = 0;//过压高温保护
    volage_time = millis();
  }
}

void read_t12_temp() //定时读取T12的温度
{
  if (millis() - t12_temp_time < t12_temp_read_time) return;
  t12_temp_time = millis();
  analogWrite(t12_pwm_pin, 0);
  //int time0 = millis();
  //总显示函数相当于延时大概110ms,
  //因为运放输出部分加有低通滤波，需要等待一段时间等滤波电容放完电再测量，不然测量到的值不准
  t12_display(); //总显示函数
  //int time1 = millis();
  //Serial.println(time1 - time0);
  for (uint8_t a = 0; a < 10; a++) //稍微滤一下波
  {
    t12_ad += analogRead(t12_temp_pin);
  }
  t12_ad = t12_ad / 10.0;

  //计算温度，自己测量自己拟合的曲线，没有测量设备请不要改动这里
  //analogWrite(t12_pwm_pin, pid_out);
  float temp = float(-0.000184 * t12_ad * t12_ad + 0.5532 * t12_ad + 34.978);
  t12_temp += (temp - t12_temp) * 0.85; //温度补偿
  t12_pid(); //运行pid

  //Serial.print(t12_temp);
  //Serial.print(",");
  //Serial.println(set_temp);
}

void volage_read() //读取电源电压
{
  float volage_ad = 0.0;
  for (uint8_t a = 0; a < 10; a++) //稍微滤一下波
  {
    volage_ad += analogRead(volage_pin);
  }
  volage_ad = volage_ad / 10.0; //读取原始AD
  volage = (volage_ad / 0.1181) * vcc_refer_1024; //计算电源电压 7.5/56+7.5=0.1181
  //Serial.print("电源电压：");Serial.println(volage);
}
void ntc_temp_read() //读取ntc温度
{
  float ntc_ad = 0.0;
  float ntc_volage = 0.0;
  float ntc_rt = 0.0;
  float ad = 0.0;
  float T1 = 273.15 + 25.0; //常温
  float R1 = 10.0; //常温对应的阻值，注意单位是千欧
  float B = 3590.0;
  for (uint8_t a = 0; a < 10; a++) //稍微滤一下波
  {
    ntc_ad += analogRead(ntc_pin);
  }
  ntc_ad = ntc_ad / 10.0;
  ntc_volage = ntc_ad * vcc_refer_1024; //ntc处的电压
  ntc_rt = (50.0 - 10.0 * ntc_volage) / ntc_volage; //计算ntc的电阻
  ntc_temp = (((T1 * B) / (B + T1 * log(ntc_rt / R1))) - 273.15); //计算ntc的温度
  /*Serial.print("ntc_ad:"); Serial.print(ntc_ad); Serial.print(" || ");
    Serial.print("ntc_volage:"); Serial.print(ntc_volage); Serial.print(" || ");
    Serial.print("ntc_rt:"); Serial.print(ntc_rt); Serial.print(" || ");
    Serial.print("ntc_temp:"); Serial.println(ntc_temp);*/
}

void ec_read() //读取电流
{
  float ec_ad = 0.0;
  for (uint8_t a = 0; a < 30; a++) //稍微滤一下波
  {
    ec_ad += analogRead(ec_pin);
  }
  ec = (ec_ad / 30.0) * vcc_refer_1024;
  //Serial.print("ec:"); Serial.println(ec, 2);
  ec = abs((ec - vcc_refer_ec)) / 0.185;
  if (ec >= 3.0) t12_switch = 0; //过流保护
}
