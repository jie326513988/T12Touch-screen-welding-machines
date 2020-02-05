# T12触屏焊台-ArduinoProMini-Atmega328p-au核心
## 使用了LCDWIKI_KBV、LCDWIKI_GUI、TouchScreen、库，感谢
## 基本功能已经完善，Nano/Mini和Uno平台都有屏幕校准功能了！<br>1.触摸调节温度、2.虚拟键盘、3.调节pid参数、4.烙铁的休眠设置、5.断电保存数据、6.软件过压过流机内高温保护、7.内置看门狗 、8.屏幕校准
### Arduino核心板，触摸屏，降压电路为模块拔插式，其他部分电路为贴片焊接，方便新手，方便调试。<br>从30℃加热到260℃需12秒，400℃需25秒，稳定跳动温度1-3℃，与实际误差1-10℃（跟环境温度有关）。观看视频https://www.bilibili.com/video/av83184959
#### 2020-01-28 v0.81版本，修复了一个休眠的BUG，优化了温度测量，上传了3D打印件和成本清单。
2020-01-24 v0.80版本，经过了8个小时的努力以及十几根头发的代价，又又又再一次压缩了Flash，还剩0.38%的空间，终于在nano/mini平台上加入屏幕校准功能。Uno平台还有5%，还可以美化一下UI。<br>
2020-01-22 v0.71版 新增坐标显示的开关，优化了flash，Mini还剩2%,Uno还剩7%,优化触摸读取速度，下一版本加入屏幕校准功能。<br>
2020-01-22 v0.7版，主界面新增一键到达设定温度的功能400/320/240。<br>
2020-01-20 v0.7版，增加软件过压过流过温保护，修正烙铁休眠唤醒不会回温的BUG，主界面美化一下，电路去掉了一个100欧的电阻，加热效率提升30%。<br>
2020-01-19 v0.6版上线，优化一些些内存，修改一下下菜单，增加了烙铁进入休眠的时间阈值和休眠的温度的菜单项，同样支持虚拟键盘修改数值和EEPROM。<br>
2020-01-16 优化了加热效率和控温稳定性。与设定值差10℃以上时，采样周期长，10℃以内，采样周期短。从30℃加热到260℃需15秒，稳定跳动温度3℃以内，通常为1℃。<br>
2020-01-14 终于实现了模拟键盘输入并可更改pid数值并储存在Eeprom中，有点小BUG但不影响使用。<br>
2020-01-13 初步实现稳定控温，从30℃加热到260℃需45秒，太久了。<br>
##### 引脚定义
D0  D1  D2  D3  D4  D5  D6  D7<br>
8   9   2   3   4   5   6   7<br>
LCDWIKI_KBV mylcd(ILI9341, A2, A1, 13, A0, 12); //model,cs,cd,wr,rd,resett<br>
#define YP A2  // must be an analog pin, use "An" notation!<br>
#define XM A1  // must be an analog pin, use "An" notation!<br>
#define YM 9   // can be a digital pin<br>
#define XP 8   // can be a digital pin<br>
#define t12_temp_pin A5      //T12温度读取引脚<br>
#define sleep_pin A3         //休眠状态读取引脚<br>
#define ec_pin A4            //电流读取引脚<br>
#define volage_pin A6        //电源电压读取引脚<br>
#define ntc_pin A7           //ntc读取引脚<br>
#define t12_pwm_pin 10       //T12加热控制引脚<br>
#define buzzer_pin 11        //蜂鸣器控制引脚<br><br>
##### 电路简介 PCB文件待完善
1.热电偶信号放大电路<br>
    使用AD8628轨到轨运算放大器，放大510倍，输入和输出均加有低通滤波器。<br>
2.功率输出电路<br>
    使用光耦和AOD4184场效应管组成的简单功率输出控制电路。<br>
3.检测电流电压电路<br>
    电流检测使用ACS712量程为±5A的霍尔感应电流传感器，输出并未加低通滤波电路，测量值比较飘，只能降低精度至0.1A。<br>
    电压检测使用简单的分压电路测量，量程为0-42V，精度0.1V，输入检测电压前反向并联26V的瞬态抑制二极管，防止脉冲电涌损坏单片机。<br>
4.5V供电电路<br>
    使用固定输出4.98V的降压模块，拔插式。为单片机、LCD、运算放大器、电流传感器供电。同样为了防止脉冲电涌，输出反向并联5.1V的稳压二极管。<br>
5.显示电路<br>
    使用2.4寸带触摸功能LCD屏幕模块，拔插式。提供显示功能和触摸功能。<br>
6.控制核心<br>
    使用ArduinoProMini平台，核心为Atmel328p-AU,拔插式。<br>
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/01.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/02.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/03.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/04.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/05.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/06.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/07.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/08.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/09.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/10.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/11.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/12.jpg)
![](https://github.com/jie326513988/T12Touch-screen-welding-machines/blob/master/compressed%20image/13.jpg)
