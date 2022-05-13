//ORIGINAL CODE
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial apc220T(6,7); //apc220 transmit
SoftwareSerial apc220R(8,9); //apc220 receive
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int i,j, col;
char aguarde[]="Aguarde...";
char amazingrov[]="AmazingROV";
char recebendo[]="Recebendo";
char sem_dados[]="Sem dados";

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long interval = 100;
String temp = "";

void setup() 
{
  Serial.begin(9600);
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);
  apc220T.begin(9600);
  apc220R.begin(9600);
  lcd.begin(16,2);

  //faz o texto amazingrov
    col=3;
    for(j=0;j<=9;j++){
      lcd.setCursor(col,0);
      lcd.print(amazingrov[j]);
      delay(200);
      col++;
    }
   //faz o texto aguarde por favor.
   col=4;
   for(j=0;j<=9;j++) {
    lcd.setCursor(col, 1);
    lcd.print(aguarde[j]);
    delay(100);
    col++;
   }

   delay(5000);
   limpaLinha(1);
}
void limpaLinha(int linha){
  for(j=0;j<=15;j++){
    lcd.setCursor(j,linha);
    lcd.print(" ");
  }
}

void loop() 
{
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    if (previousMillis = currentMillis)
    {
      int pv = analogRead(A0);
      int sv = analogRead(A1);
      int tv = analogRead(A2);
      int Swt = digitalRead(4);
    
      String data = (String)pv + ";" + (String)sv + ";" + (String)tv + ";" + (String)Swt;
      String blinker_stop = "";
      apc220T.println(blinker_stop);
      

      //Cima
      if((pv>=510 && pv<=700) && (sv>=400 && sv<=600) && (tv>=800 && tv<=1023))
      {
        apc220T.println("C");
        Serial.println("C");
      }

      //Baixo
      else if((pv>=510 && pv<=700) && (sv>=400 && sv<=600) && (tv>=0 && tv<=200)){   
        apc220T.println("B");
        Serial.println("B");
      }

      //Esquerda    
      else if((pv>=700 && pv<=1024) && (sv>=400 && sv<=600) && (tv>=400 && tv<=600))
      {
        apc220T.println("E");
        Serial.println("E");
      }

      //Direita
      else if((pv>=0 && pv<=300) && (sv>=400 && sv<=600) && (tv>=400 && tv<=600)){
        apc220T.println("D");
        Serial.println("D");
      }

      //Frente
      else if((pv>=510 && pv<=700) && (sv>=0 && sv<=300) && (tv>=400 && tv<=600))
      {
        apc220T.println("F");     
        Serial.println("F");
      }

      //Trás
      else if((pv>=80 && pv<=700) && (sv>=800 && sv<=1023) && (tv>=400 && tv<=600)){
        apc220T.println("T");
        Serial.println("T");
      }
      
      //Cima + Frente
      else if((pv>=510 && pv<=700) && (sv>=0 && sv<=300) && (tv>=800 && tv<=1023)){
        //apc220T.println("1");
        Serial.println("1");
      }

      //Cima + Trás
      else if((pv>=80 && pv<=700) && (sv>=800 && sv<=1023) && (tv>=800 && tv<=1023)){
        //apc220T.println("2");
        Serial.println("2");
      }

      //Cima + Esquerda
      else if((pv>=700 && pv<=1024) && (sv>=400 && sv<=600) && (tv>=800 && tv<=1023)){
        apc220T.println("3");
        Serial.println("3");
      }

      //Cima + Direita
      else if((pv>=0 && pv<=300) && (sv>=400 && sv<=600) && (tv>=800 && tv<=1023)){
        //apc220T.println("4");
        Serial.println("4");
      }

      //Baixo + Frente
      else if((pv>=510 && pv<=700) && (sv>=0 && sv<=300) && (tv>=0 && tv<=200)){
        //apc220T.println("5");
        Serial.println("5");
      }

      //Baixo + Trás
      else if((pv>=80 && pv<=700) && (sv>=800 && sv<=1023) && (tv>=0 && tv<=200)){
        //apc220T.println("6");
        Serial.println("6");
      }

      //Baixo + Esquerda
      else if((pv>=700 && pv<=1024) && (sv>=400 && sv<=600) && (tv>=0 && tv<=200))
      {
        //apc220T.println("7");
        Serial.println("7");
      }

      //Baixo + Direita
      else if((pv>=0 && pv<=300) && (sv>=400 && sv<=600) && (tv>=0 && tv<=200)){
        apc220T.println("8");
        Serial.println("8");
   }
  }
 }

  //ler dados recebidos
  while(apc220R.available()){
    char c = apc220R.read();
    if(c!='\n'){
      temp = temp + c;
      lcd.setCursor(1,1);
      lcd.print("Recebendo dados");
    }
    else {
      Serial.println("Recebido: " + temp);
      limpaLinha(1);
      lcd.setCursor(4,1);
      lcd.print("Sem dados");
      }
      
    }
    temp="";
  }
