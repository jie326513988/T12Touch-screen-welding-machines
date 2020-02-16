/*
  时钟输出 | Arduino输出Pin | 芯片Pin | Pin 名字
  OC0A       6                12       PD6
  OC0B       5                11       PD5
  OC1A       9                15       PB1
  OC1B       10               16       PB2
  OC2A       11               17       PB3
  OC2B       3                5        PD3

  脉冲生成模式控制位（WGM）：用来设置PWM的模式或CTC模式
  时钟选择位（CS）：设置时钟的预分频
  输出模式控制位（COMnA和COMnB）：使能/禁用/反相 输出A和输出B
  输出比较器（OCRnA和OCRnB）：当计数器等于这两个值时，输出值根据不同的模式进行变化

  快速PWM（0-255 0-255 数完归零）      
  相位修正PWM（0-255 255-0 数完倒数）  

  8位(定时器0/2)
  CSn0 001 = 1
  CSn1 010 = 8
  CSn2 011= 32
  CSn3 100= 64
  CSn4 101= 128
  CSn5 110= 256
  CSn6 111= 1024
  16位(定时器1)
  CSn0 001 = 1
  CSn1 010 = 8
  CSn2 011= 64
  CSn3 100= 256
  CSn4 101= 1024

  COMnA1 COMnB1 =  占空比AB都可控
  从0数到255 0时输出高电平
  OCRnA 当数到OCRnA，输出低电平，即A的占空比=OCRnA的值
  OCRnB 当数到OCRnB，输出低电平，即B的占空比=OCRnB的值

  COMnA0 COMnB1 =  A当数到头是反相 占空比A50% B可控
  OCRnA 从0数到OCRnA 0时输出高电平
  OCRnB 当OCRnA=OCRnB，输出低电平
*/
void pwm1(uint16_t val)
{
  //输出通道B 占空比: (OCR1B+1) / (OCR1A+1)
  //占空比不能大于OCR1A
  //pinMode(10, OUTPUT); //B
  bitWrite(DDRB, 2, 1); //设置pin10为输出
  //快速PWM,分频比64，频率: 16000000/64*(OCR1A+1) = 976HZ 
  //TCCR1A = B00100011;
  //TCCR1B = B00011011;
  //相位和频率校正PWM,分频比256，频率: 16000000/2*256*(OCR1A+1) = 61HZ 
  TCCR1A = B00100001;
  TCCR1B = B00010100;
  //相位校正PWM,分频比256，频率: 16000000/2*256*(OCR1A+1) = 122HZ 
  //TCCR1A = B00100011;
  //TCCR1B = B00010100;
  OCR1A = 511; //从0开始数到0CR1A，0-65535，设置周期和频率
  OCR1B = val; //用来设置比较器,占空比
}
