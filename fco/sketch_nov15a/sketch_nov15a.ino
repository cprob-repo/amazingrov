#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#define GPSECHO  false

#define MA_IN1 6
#define MA_IN2 7
#define MA_EN1 3

#define MB_IN3 14
#define MB_IN4 13
#define MB_EN2 9

#define MC_IN1 11
#define MC_IN2 12
#define MC_EN3 10

#define MD_IN3 24
#define MD_IN4 26
#define MD_EN4 5

#define ONE_WIRE_BUS 22

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float tempH2O = 0;
float tempAr = 0;
float pressAr = 0;
float humidAr = 0;

unsigned long previousMillis = 0;
const long interval = 2000;

Adafruit_BME280 bme;
SoftwareSerial apc220T(2,4);
SoftwareSerial mySerial(51,52);
Adafruit_GPS GPS(&mySerial);

boolean usingInterrupt = false;
float lat, lon, sec_lat, sec_lon, dec_lat, dec_lon;
String s_dec_lat, s_dec_lon;
int rate, deg_lat, deg_lon, minu_lat, minu_lon;
uint32_t timer = millis();
String data = "";

void setup()
{
  Serial.begin(9600); 
  rate=2000;
  GPS.begin(9600);
  GPS.sendCommand("$PMTK251,19200*22");
  GPS.sendCommand("$PMTK220,100*2F");
  mySerial.end();
  GPS.begin(19200);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_NOANTENNA);
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
  //Motor A e B = Frente / Trás e Mudança de Direção 
  pinMode(MA_IN1,OUTPUT);
  pinMode(MA_IN2,OUTPUT);
  pinMode(MA_EN1,OUTPUT);
  
  pinMode(MB_IN3,OUTPUT);
  pinMode(MB_IN4,OUTPUT);
  pinMode(MB_EN2,OUTPUT);

  //Motor C e D = Cima / Baixo
  pinMode(MC_IN1,OUTPUT);
  pinMode(MC_IN2,OUTPUT);
  pinMode(MC_EN3,OUTPUT);

  pinMode(MD_IN3,OUTPUT);
  pinMode(MD_IN4,OUTPUT);
  pinMode(MD_EN4,OUTPUT);  
  
  Serial.begin(9600);
  Serial1.begin(9600);
  apc220T.begin(9600);
  bme.begin();
  sensors.begin();
  delay(500);
  
}

void loop() {
  /*verifica se chegaram comandos*/
  while(Serial1.available())
  {
    char c = Serial1.read();
    if(c != '\n')
    {
      data = data + c;
    }
    else
    { 
      char v = data.charAt(0);
      Serial.println(v);
        switch (v) {
          case 'F' : {
            digitalWrite(MA_IN1,HIGH);
            digitalWrite(MA_IN2,LOW);
            analogWrite(MA_EN1,50);
            digitalWrite(MB_IN3,LOW);
            digitalWrite(MB_IN4,HIGH);
            analogWrite(MB_EN2,50);
            break; 
       }
         case 'T' : {
            digitalWrite(MA_IN1,LOW);
            digitalWrite(MA_IN2,HIGH);
            analogWrite(MA_EN1,50);
            digitalWrite(MB_IN3,HIGH);
            digitalWrite(MB_IN4,LOW);
            analogWrite(MB_EN2,50);
            break; 
       } 
         case 'E' : {
            digitalWrite(MA_IN1,HIGH);
            digitalWrite(MA_IN2,LOW);
            analogWrite(MA_EN1,50);
            digitalWrite(MB_IN3,LOW);
            digitalWrite(MB_IN4,LOW);
            analogWrite(MB_EN2,50);
            break; 
       }
         case 'D' : {
            digitalWrite(MA_IN1,LOW);
            digitalWrite(MA_IN2,LOW);
            analogWrite(MA_EN1,50);
            digitalWrite(MB_IN3,LOW);
            digitalWrite(MB_IN4,HIGH);
            analogWrite(MB_EN2,50);
            break; 
        }
         case 'C' : {
            digitalWrite(MC_IN1,HIGH);
            digitalWrite(MC_IN2,LOW);
            analogWrite(MC_EN3,50);
            digitalWrite(MD_IN3,HIGH);
            digitalWrite(MD_IN4,LOW);
            analogWrite(MD_EN4,50);
            break; 
         }
         case 'B' : {
            digitalWrite(MC_IN1,LOW);
            digitalWrite(MC_IN2,HIGH);
            analogWrite(MC_EN3,50);
            digitalWrite(MD_IN3,LOW);
            digitalWrite(MD_IN4,HIGH);
            analogWrite(MD_EN4,50);
            break; 
         }
         case '1' : {
            break; 
         }
         case '2' : {
            break; 
         }
         case '3' : {
            break; 
         }
         case '4' : {
            break;
         }
         case '5' : {
            break;
         }
         case '6' : {
            break;
         }
         case '7' : {
            break;
         }
         case '8' : {
            break;
         }
         default : {
            digitalWrite(MA_IN1,LOW);
            digitalWrite(MA_IN2,LOW);
            digitalWrite(MB_IN3,LOW);
            digitalWrite(MB_IN4,LOW);
            digitalWrite(MC_IN1,LOW);
            digitalWrite(MC_IN2,LOW);
            digitalWrite(MD_IN3,LOW);
            digitalWrite(MD_IN4,LOW);
            break;   
        }
      }
      data="";
    }
  }

  /*recolhe leituras dos sensors*/
  
  sensors.requestTemperatures(); 
  tempH2O = sensors.getTempCByIndex(0);
  tempAr = bme.readTemperature();
  pressAr = bme.readPressure() / 100.0F;
  humidAr = bme.readHumidity();
  getGPS();

  
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    String data = 
    "ART;"+(String)tempH2O+";"+(String)tempAr+";"+(String)pressAr+";"+(String)humidAr+";";
    apc220T.print(data);
    apc220T.print(dec_lat,8);
    apc220T.print(";");
    apc220T.println(dec_lon,8);
    Serial.println(data);
    /*if(tempH2O != DEVICE_DISCONNECTED_C) {
      String data = (String)tempH2O + ";" + (String)tempAr + ";" + (String)pressAr + ";" + (String)humidAr;
      apc220T.println(data);
      Serial.println(data);
    } 
    else{
      apc220T.println("Erro sensor");
      Serial.println("Erro sensor");
    }*/
  }
}
//end loop

void getGPS (){
  if (!usingInterrupt)
  {
   while (mySerial.available())
    {
      char c = GPS.read();
    }
  }
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }
  if (timer > millis())  
    timer = millis();
  if (millis() - timer > rate) 
  {
    timer = millis();
    if (GPS.fix)
    {
      lat = GPS.latitude;
      deg_lat = int (lat / 100);
      minu_lat = int (lat - (deg_lat * 100));
      sec_lat = ((float) (lat - int(lat))) * 60;
      dec_lat = (float) deg_lat + (float) minu_lat / 60 + (float) sec_lat / 3600;
      if (GPS.lat == 'S')
      {
        dec_lat = dec_lat * -1;
      }
      lon = GPS.longitude;
      deg_lon = int (lon / 100);
      minu_lon = int (lon - (deg_lon * 100));
      sec_lon = ((float) (lon - int(lon))) * 60;
      dec_lon = (float) deg_lon + (float) minu_lon / 60 + (float) sec_lon / 3600;
      if (GPS.lon == 'W')
      {
        dec_lon = dec_lon * -1;
      }
    }
    else
    {
      dec_lat = 0;
      dec_lon = 0;
    }
  }
}
