//使用MEGA2560 or UNO
#include <SoftwareSerial.h>
SoftwareSerial Gsmserial(10,11);
String TEMPdata="";
#define apikey "oQQ*****************gKEA"  //替换成你自己的ApiKey
unsigned long deviceid=7****1;    //替换成你自己的deviceid
String sensorid="T***P";     //替换成你自己的sensorid
String sensor1id="P***5";      //替换成你自己的sensorid
#define Yapikey "8673******************23807"   //替换成你自己的ApiKey
unsigned long Ydeviceid=2***6;    //替换成你自己的deviceid
unsigned long Ysensorid=3***2;     //替换成你自己的sensorid
unsigned long Ysensorid1=3***7;     //替换成你自己的sensorid
#define LINEBREAK "\r\n"
char server[]="api.heclouds.com";
 
 
void setup()
{
  randomSeed(analogRead(A0));
   Serial.begin(9600);
   Gsmserial.begin(9600);
Gsmserial.listen();
  Serial.println("**********************************************************************");
  Serial.println("debug========================AT");
  String cmd="\"AT\"";
  Gsmserial.println("AT");
  delay(1000);
 returnmsg_ok();
cmd="\"AT+CPIN?\"";
 Gsmserial.println("AT+CPIN?"); 
    TEMPdata=""; returnmsg_ok();
   Gsmserial.println("AT+CGCLASS=\"B\""); 
    TEMPdata=""; returnmsg_ok();
   Gsmserial.println("AT+CGDCONT=1,\"IP\",\"CMNET\""); 
    TEMPdata=""; returnmsg_ok(); 
    Gsmserial.println("AT+CGATT=1"); 
   TEMPdata="";   returnmsg_ok();    
  Serial.println("debug=========AT+CIPCLOSE");
Gsmserial.println("AT+CIPCLOSE"); 
    TEMPdata=""; returnmsg_ok_err();   
 
 
}
  
void loop()
{
 
////////////////////////////////////////////////////////////////////读取各种数值
  
int v1 = analogRead(A3)*random(3)/3;
int v2 = analogRead(A3)*random(3)/2;
int sensorReading = analogRead(A3)*random(3)/3;
int sensorReading1 = analogRead(A3)*random(3)/2;
Serial.print("VAL:");
Serial.println(v1);
postdate(v1,Yapikey,Ydeviceid,Ysensorid);
delay (5000);
postdate(v1,Yapikey,Ydeviceid,Ysensorid1);
delay (5000);
TEMPdata="";
sendData(sensorReading,deviceid,sensorid);
TEMPdata="";
delay(5000);
sendData(sensorReading1,deviceid,sensor1id);
delay(5000); 
    
 }
 

/////////////////////////////////////////////////////////////////
//=================postdate传数据=====================yeelink用
void postdate(int SensorData , String APIKEY , unsigned long DEVICEID ,unsigned long SENSORID)
{
 Gsmserial.println("AT+CIPSTART=\"TCP\",\"api.yeelink.net\",80"); 
returnmsg_ok_con();   TEMPdata="";
int l=getLength(SensorData);
int D=getLength(DEVICEID);
int S=getLength(SENSORID);
//该数据是我摸索出来的，3天就是调这个，大家可以自己调调看，估计还和设备ID和传感器ID长度也有关系
int lens=232+D+S+l;
Gsmserial.print("AT+CIPSEND=");
returnmsg();  TEMPdata="";
Gsmserial.println(lens);
returnmsg();  TEMPdata="";
delay(300);
Gsmserial.print("POST /v1.0/device/");
returnmsg();  TEMPdata="";
Gsmserial.print(DEVICEID);
returnmsg();  TEMPdata="";
Gsmserial.print("/sensor/");
returnmsg();  TEMPdata="";
Gsmserial.print(SENSORID);
returnmsg();  TEMPdata="";
Gsmserial.print("/datapoints HTTP/1.1\r\nHost: api.yeelink.net\r\nAccept: */*\r\nU-ApiKey:");
//Serial.print("/datapoints HTTP/1.1\r\nHost: api.yeelink.net\r\nAccept: */*\r\nU-ApiKey:");
returnmsg();  TEMPdata="";
Gsmserial.print(APIKEY);
returnmsg();  TEMPdata="";
Gsmserial.print("\r\nContent-Length: ");
returnmsg();  TEMPdata="";
//浮点数据还要+3
Gsmserial.print(10+l);
returnmsg();  TEMPdata="";
Gsmserial.print("\r\nContent-Type: application/x-www-form-urlencoded\r\nConnection: close\r\n\r\n{\"value\":");
returnmsg();  TEMPdata="";
Gsmserial.print(SensorData);
returnmsg();  TEMPdata="";
Gsmserial.print("}\r\n\r\n");
returnmsg_ok_finish();  TEMPdata="";
}

void sendData(int thisData,unsigned long deviceid,String sensorid )
//移动onenet用
{
int l=getLength(thisData);
int D=getLength(deviceid);
int S=sensorid.length(); 
 Serial.print("SSSSSSSSSSSSSSSSSSSSSSSSSSS==========");Serial.println(S);
int lens=216+D+S+l;  //该数据是我摸索出来的，3天就是调这个，大家可以自己调调看，估计还和设备ID和传感器ID长度也有关系
int lenss=53+S+l;
  Serial.println("debug======AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r");
  Gsmserial.println("AT+CIPSTART=\"TCP\",\"183.230.40.33\",80");
      Serial.println("connecting...");
returnmsg_ok_con();  TEMPdata="";
 
    Gsmserial.print("AT+CIPSEND=");
  Serial.println("debug============================AT+CIPSEND=");
returnmsg();  TEMPdata="";
Gsmserial.println(lens);    
Serial.println(lens); 
returnmsg();  TEMPdata="";
    Serial.println("debug============POST [url=http://api.heclouds.com/devices/]http://api.heclouds.com/devices/[/url]");
    Gsmserial.print("POST [url=http://api.heclouds.com/devices/]http://api.heclouds.com/devices/[/url]");
returnmsg();  TEMPdata="";
    Gsmserial.print(deviceid);
returnmsg();  TEMPdata="";
    Gsmserial.print("/datapoints HTTP/1.1");
returnmsg();  TEMPdata="";
    Gsmserial.print(LINEBREAK);
returnmsg();  TEMPdata="";
    Gsmserial.print("Host: ");
returnmsg();  TEMPdata="";
    Gsmserial.print(server);
returnmsg();  TEMPdata="";
    Gsmserial.print(LINEBREAK);
returnmsg();  TEMPdata="";
    Gsmserial.print("api-key: ");
returnmsg();  TEMPdata="";
    Gsmserial.print(apikey);
returnmsg();  TEMPdata="";
    Gsmserial.print(LINEBREAK);
returnmsg();  TEMPdata="";
    Gsmserial.println("Connection: close");
returnmsg();  TEMPdata="";
    Gsmserial.print("Content-Length: ");
returnmsg();  TEMPdata="";
    Gsmserial.print(lenss);
returnmsg();  TEMPdata="";
    Gsmserial.print(LINEBREAK);
returnmsg();  TEMPdata="";
   Gsmserial.print(LINEBREAK);
returnmsg();  TEMPdata="";
    Gsmserial.print("{\"datastreams\":[{\"id\":\"");
returnmsg();  TEMPdata="";
    Gsmserial.print(sensorid);
returnmsg();  TEMPdata="";
    Gsmserial.print("\",\"datapoints\":[{\"value\":");
returnmsg();  TEMPdata="";
    Gsmserial.print(thisData);
returnmsg();  TEMPdata="";
   Gsmserial.print("}]}]}");
returnmsg();  TEMPdata="";
    Gsmserial.print(LINEBREAK);
    Gsmserial.print(LINEBREAK);
    Gsmserial.print(LINEBREAK);  
    Gsmserial.print(LINEBREAK);
returnmsg_ok_finish();  TEMPdata="";
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
 
int getLength(int someValue) {
  int digits = 1;
  int dividend = someValue /10;
  while (dividend > 0) {
    dividend = dividend /10;
    digits++;
  }
  return digits;
}
///////////////////////////////////////////////////////////////////////////////////////////
void returnmsg_ok_con()
{
  while(1)
 {
 while(Gsmserial.available())
  {
     TEMPdata+=char(Gsmserial.read());
     delay(1);
                                                              
  }
   
    if ((TEMPdata.indexOf("OK") > 3)&&(TEMPdata.indexOf("CONNECT") > 0))
     {
     Serial.println(TEMPdata); 
       Serial.println("");  
       break;
     }
 
}
 return;
}
////////////////////////////////////////////////////////////////////////////////////////////////
void returnmsg_ok_finish()
{
  while(1)
 {
 while(Gsmserial.available())
  {
     TEMPdata+=char(Gsmserial.read());
 // Serial.println(TEMPdata); 
    delayMicroseconds(700); 
                                                              
  }
    if ((TEMPdata.indexOf("CLOSED") > 3)&&(TEMPdata.indexOf("OK") > 0))
     {
     Serial.println(TEMPdata); 
       Serial.println("");  
       break;
     }
     else
     {;}
}
 return;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
 void returnmsg_ok()
{
 
  while(1)
 {
     while( Gsmserial.available())
         {
            TEMPdata+=char( Gsmserial.read());
            //Serial.println(TEMPdata);
             delay(2);
          }
           if (TEMPdata.indexOf("OK") > 1)
                  {
                       Serial.println(TEMPdata); 
                        Serial.println("");  
                        break ;
     }
}
   return ; 
 
}
 
//////////////////////////////////////////////////////////////////////
 
void returnmsg()
{
  while(!Gsmserial.available())
 {}
 while( Gsmserial.available())
  {
     TEMPdata+=char( Gsmserial.read());
   // Serial.println(TEMPdata);
     delay(2);
   }
   Serial.println(TEMPdata);
 return;
}
//////////////////////////////////////////////////////////////////////////////////////
 
 
 void returnmsg_ok_err()
{
 
  while(1)
 {
     while( Gsmserial.available())
         {
            TEMPdata+=char( Gsmserial.read());
            //Serial.println(TEMPdata);
             delay(2);
          }
           if ((TEMPdata.indexOf("OK") > 1)||(TEMPdata.indexOf("ERROR") > 1))
                  {
                       Serial.println(TEMPdata); 
                        Serial.println("");  
                        break ;
     }
}
   return ; 
 
}
 
//////////////////////////////////////////////////////////////////////////////////////