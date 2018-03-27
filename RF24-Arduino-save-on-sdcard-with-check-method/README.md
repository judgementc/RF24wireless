# RF24-Arduino-save-on-sdcard-with-check-method
A coding and some thought on build a master with slave on sensor for hum and tem using RF24 and Arduino with Timetag and the data are able to saved on sd card, to double the data safe.
/*
 *2018年3月21日11:52:16
 *powered by arduino and mike ju
 *uno上RF24
 *miso -> 12 主机数据输入,从机信号输出 master in slave out
 *mosi -> 11 主机数据输出,从机信号输入 master out slave in
 *sck -> 13 时钟信号 serial clock
 *ss -> 10 (**RF24 not use**)随意定义 从机使能信号,由主机控制 slave select
 *ce -> 10 随意定义  SPI chip enable 使能端口,相当于ss
 *csn -> 9 随意定义 SPI chip select

 *mega上RF24 供电5v
 *miso -> 51
 *mosi -> 50 
 *sck -> 52
 *ce -> 48
 *csn -> 49

 *oled模块 无需供电(mega and uno)的ISP通信是库(SH1106.h)软件定义,****所有接口都可以修改****
 *#define OLED_MOSI   7
 *#define OLED_CLK   8
 *#define OLED_DC    5
 *#define OLED_CS    4
 *#define OLED_RESET 6

 *注意serial.begin

 *DS3231时钟模块 3.3v
 *SCL=SCK--> SCL 时钟线
 *SDA --> SDA 数据线
 *VCC --> 3.3v供电
 *GND --> GND
 *时钟模块在板上有专门接口 SCL 与 SDA
 *DHT11使用5v供电
 *1106oled使用3.3v供电
 *3231时钟使用3.3v供电
 *RF24(带AP与voltage regulator)使用5v供电
 *SD卡模块 5v 供电

 *SD卡片选cs
 *CS -> 46

 *注意serial与spi冲突,上传完成后需要关闭Serial串口重启
 *SDcard.begain(chipSelectPin)
 *注意为loop中个步骤设置检查check(if/else条件,并在oled输出)
 */
 /*/
 检查错误点:
 1.注意所有模块是否全部有效连接
 2.在添加模块前先使用有效代码做验证
 3.注意loop中是否有不能进行的顺序结构,导致循环失效
 4.注意端口变更,在编辑器上做的更改应该与IDE中一致.
 /*/
 