#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7,3,NEGATIVE);

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int i,j, col;
char cprob[]="ENTA#CPROB";
char aguarde[]="Aguarde...";
char amazingrov[]="AmazingROV";
char TEXTO[]="TEXTO";
char bom[]="BOM";
char ano[]="ANO";
char novo[]="NOVO";
char votos[]="Sao os votos do";
  
void setup() {
  Serial.begin(9600);
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


void loop() {
    /*
    //faz o texto aguarde. 
    col=3;
    for(j=0;j<=10;j++){
      lcd.setCursor(col,0);
      lcd.print(amaizingrov[j]);
      delay(50);
      col++;

    }
    col++;
    for(j=0;j<=4;j++){
      lcd.setCursor(col,0);
      lcd.print(TEXTO[j]);
      delay(50);
      col++;
    }
    lcd.print("!");


    //faz bom ano novo
    col=13;
    for(j=3;j>=0;j--){
      lcd.setCursor(col,1);
      lcd.print(novo[j]);
      delay(50);
      col--;
    }
    col--;
    for(j=2;j>=0;j--){
      lcd.setCursor(col,1);
      lcd.print(ano[j]);
      delay(50);
      col--;
    }
    col--;
    for(j=2;j>=0;j--){
      lcd.setCursor(col,1);
      lcd.print(bom[j]);
      delay(50);
      col--;
    }
    delay(3000);
    delay(500);

    //faz entacprob
    col=3;
    for(j=0;j<=9;j++){
      lcd.setCursor(col,0);
      lcd.print(cprob[j]);
      delay(50);
      col++;
    }
    delay(1000);

    //faz *
    for(j=0;j<=2;j++){
      lcd.setCursor(j,0);
      lcd.print("*");
      delay(200);
    }
    for(j=13;j<=15;j++){
      lcd.setCursor(j,0);
      lcd.print("*");
      delay(200);
    }
    for(j=0;j<=15;j++){
      lcd.setCursor(j,1);
      lcd.print("*");
      delay(100);
    }
    delay(3000);
    delay(500);
    */
}

void limpaLinha(int linha){
  for(j=0;j<=15;j++){
    lcd.setCursor(j,linha);
    lcd.print(" ");
  }
}
