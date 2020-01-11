void read_wen_du()
{
  if (millis() - t12_temp_time < 500) return;
  t12_temp_time = millis();
  t12_temp = analogRead(t12_temp_pin);
}
