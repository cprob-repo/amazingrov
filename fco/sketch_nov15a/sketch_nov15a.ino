#include <DallasTemperature.h>
#include <OneWire.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <SoftwareSerial.h>

#define MA_IN1 6
#define MA_IN2 7
#define MA_EN1 3

#define MB_IN3 8
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
const long interval = 1000;

Adafruit_BME280 bme;
SoftwareSerial apc220T(2,4);

//int contador = 0;

String data = "";

void setup()
{
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
  //apc220R.begin(9600);
  apc220T.begin(9600);
  bme.begin();
  sensors.begin();
}

void loop() {
  while(Serial.available())
  {
    char c = Serial.read();
    if(c != '\n')
    {
      data = data + c;
    }
    else
    { 
      char v = data.charAt(0);
      //Serial.println(v);
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
  sensors.requestTemperatures(); 
  tempH2O = sensors.getTempCByIndex(0);
  tempAr = bme.readTemperature();
  pressAr = bme.readPressure() / 100.0F;
  humidAr = bme.readHumidity();
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    if(tempH2O != DEVICE_DISCONNECTED_C) {
      String data = (String)tempH2O + ";" + (String)tempAr + ";" + (String)pressAr + ";" + (String)humidAr;
      apc220T.println(data);
      Serial.println(data);
    } 
    else{
      apc220T.println("Erro sensor");
    }
  }
}
