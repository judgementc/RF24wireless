/*
DS3231
SCL=SCK--> SCL 时钟线
SDA --> SDA 数据线
VCC --> 3.3v供电
GND --> GND
时钟模块在板上有专门接口 SCL 与 SDA
*/


#include <DS3231.h>
DS3231 Clock;
bool Century=false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;
int second,minute,hour,date,month,year;


second=Clock.getSecond();
minute=Clock.getMinute();
hour=Clock.getHour(h12, PM);
date=Clock.getDate();
month=Clock.getMonth(Century);
year=Clock.getYear();