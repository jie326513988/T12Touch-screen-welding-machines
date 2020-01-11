void read_wen_du()
{
  if (millis() - wen_du_time < 500) return;
  wen_du_time = millis();
  wen_du = thermocouple->readCelsius();
}
