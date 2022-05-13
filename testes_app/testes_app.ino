void setup() {
  Serial.begin(9600);

}
int cont=0;
void loop() {
  //ordem: contador;temp;temp;pressão;humidade;PH;salinidade;latitude;longitude;
  Serial.println((String)cont + ";24.5;23.6;1013.25;75.00;10.00;25.00;37.123456;-25.654123");
  cont++;
  delay(1000);
}
