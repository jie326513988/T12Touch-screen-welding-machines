//温度读取
/*
  串联电阻的中点电压计算公式
  Eout 中点电压
  Vcc 输入电压（两端施加电压）
  R1、R2 两个串联的分压电阻
  Eout = Vcc * R2/(R1+R2) R1靠近电源 R2靠近地
*/
void timing_volage_ntc() //定时读取电源电压和ntc温度
{
  if (millis() - volage_time < 3000) return;
  volage_time = millis();
  volage_read(); //读取电源电压
  ntc_temp_read(); //读取ntc温度
  ec_read(); //读取电流
}

void read_t12_temp1() //定时读取T12的温度（暂时）
{
  if (millis() - t12_temp_time < 300) return;
  t12_temp_time = millis();
  analogWrite(t12_pwm_pin, 0);
  delay(70);
  for (uint8_t a = 0; a < 10; a++) //稍微滤一下波
  {
    t12_ad += analogRead(t12_temp_pin);
  }
  t12_ad = t12_ad / 10;
  //t12_ad = analogRead(t12_temp_pin);
  t12_temp = double(-0.000149 * t12_ad * t12_ad + 0.415 * t12_ad + 28.78);
  analogWrite(t12_pwm_pin, pid_out);
}

void read_t12_temp2() //读取T12的温度（暂时）
{
  analogWrite(t12_pwm_pin, 0);
  delay(70);
  for (uint8_t a = 0; a < 5; a++) //稍微滤一下波
  {
    t12_ad += analogRead(t12_temp_pin);
  }
  t12_ad = t12_ad / 5;
  //t12_ad = analogRead(t12_temp_pin);
  t12_temp = double(-0.000149 * t12_ad * t12_ad + 0.415 * t12_ad + 28.78);
}

void volage_read() //读取电源电压
{
  float volage_ad = 0.0;
  volage_ad = analogRead(volage_pin); //读取原始AD
  volage = (volage_ad / 0.1181) * vcc_refer_1024; //计算电源电压 7.5/39+7.5=0.1613
  //Serial.print("电源电压：");Serial.println(volage);
}

void ntc_temp_read() //读取ntc温度
{
  float ntc_ad = 0.0;
  float ntc_volage = 0.0;
  float ntc_rt = 0.0;
  float ad = 0.0;
  float T1 = 273.15 + 25; //常温
  float R1 = 10.0; //常温对应的阻值，注意单位是千欧
  float B = 3590.0;
  ntc_ad = analogRead(ntc_pin);
  ntc_volage = ntc_ad * vcc_refer_1024; //ntc处的电压
  ntc_rt = (50 - 10 * ntc_volage) / ntc_volage; //计算ntc的电阻
  ntc_temp = (((T1 * B) / (B + T1 * log(ntc_rt / R1))) - 273.15); //计算ntc的温度
  /*Serial.print("ntc_ad:"); Serial.print(ntc_ad); Serial.print(" || ");
    Serial.print("ntc_volage:"); Serial.print(ntc_volage); Serial.print(" || ");
    Serial.print("ntc_rt:"); Serial.print(ntc_rt); Serial.print(" || ");
    Serial.print("ntc_temp:"); Serial.println(ntc_temp);*/
}

void ec_read()
{
  float ec_ad = 0.0;
  for (uint8_t a = 0; a < 20; a++) //稍微滤一下波
  {
    ec_ad += analogRead(ec_pin);
  }
  ec = (ec_ad / 20) * vcc_refer_1024;
  //Serial.print("ec:"); Serial.println(ec, 2);
  ec = abs((ec - vcc_refer_ec)) / 0.185;

}
void buzzer()
{
  digitalWrite(buzzer_pin, 1);
  delay(1);
  digitalWrite(buzzer_pin, 0);
}
