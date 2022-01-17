#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2); //indica los pinde de D0 hasta D7

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2); //indica el tamaño del LCD
  lcd.setCursor(3,0);
  lcd.print("LOC vs VIS");
  lcd.setCursor(0,1);
  lcd.print("1'00:00 2'00:00");
  pinMode(8,INPUT);
  pinMode(9,INPUT);
}

int bt_inicio=0;
int bt_inicioA=0;
int bt_reinicio=0;
int bt_reinicioA=0;
int estado_inicio=0;
int estado_reinicio=0;
int minutos=0;
int segundos=0;
int minutos2=0;
int segundos2=0;
int bandera_tiempo=0;

void loop() {
  /*lcd.setCursor(2,0); //indica la posicion que queremos escribir (columna,fila);
  lcd.print("AME vs PUM"); //escribir en la pantalla LCD
  lcd.setCursor(0,1);
  lcd.print(millis() / 1000); //muestra los segundos
  //lcd.print("1'14:40_2'14:40");
  */
  if(Serial.available())
  {
    delay(1000);
    lcd.clear();
    lcd.setCursor(3,0);
    while(Serial.available()>0)
    {
      char c = Serial.read();
      lcd.write(c);
    }
    lcd.setCursor(0,1);
    lcd.print("1'00:00 2'00:00");
    estado_inicio=0;
    estado_reinicio=0;
    minutos=0;
    segundos=0;
    minutos2=0;
    segundos2=0;
    bandera_tiempo=0;
    estado_inicio=0;
  }

  bt_inicio = digitalRead(8);
  bt_reinicio = digitalRead(9);
  
  if(bt_inicio == HIGH && bt_inicioA==LOW)
  {
    estado_inicio=1-estado_inicio;
    delay(80);
  }
  bt_inicioA=bt_inicio;
  
  if(bt_reinicio == HIGH && bt_reinicioA==LOW)
  {
    estado_reinicio=1-estado_reinicio;
    delay(80);
  }
  bt_reinicioA=bt_reinicio;

  if(estado_reinicio==1)
  {
    estado_reinicio=0;
    lcd.setCursor(0,1);
    lcd.print("1'00:00 2'00:00");
    minutos=0;
    segundos=0;
    minutos2=0;
    segundos2=0;
    bandera_tiempo=0;
    estado_inicio=0;
  }
  
  if(estado_inicio==1)
  {
    //Serial.print("ENTRAMOS");
    if(bandera_tiempo==0)
    {
      segundos=1+segundos;
      delay(1000);
      if(segundos==60)
      {
        lcd.setCursor(5,1);
        lcd.print("0");
        segundos=0;
        minutos=minutos+1;
      }
      if(minutos/10!=0)
      {
        lcd.setCursor(2,1);
      }else{
        lcd.setCursor(3,1);
      }
      lcd.print(minutos);
      if(segundos/10!=0)
      {
        lcd.setCursor(5,1);
      }else{
        lcd.setCursor(6,1);
      }
      lcd.print(segundos);
    }
    if(bandera_tiempo==1)
    {
      segundos2=1+segundos2;
      delay(1000);
      if(segundos2==60)
      {
        lcd.setCursor(13,1);
        lcd.print("0");
        segundos2=0;
        minutos2=minutos2+1;
      }
      if(minutos2/10!=0)
      {
        lcd.setCursor(10,1);
      }else{
        lcd.setCursor(11,1);
      }
      lcd.print(minutos2);
      if(segundos2/10!=0)
      {
        lcd.setCursor(13,1);
      }else{
        lcd.setCursor(14,1);
      }
      lcd.print(segundos2);
    }
    if(bandera_tiempo==2)
    {
      lcd.setCursor(0,1);
      lcd.print("1'00:00 2'00:00");
      minutos=0;
      segundos=0;
      minutos2=0;
      segundos2=0;
      bandera_tiempo=0;
      estado_inicio=0;
    }
  }else{
    if(minutos>=45)
    {
      bandera_tiempo=1;
    }
    if(minutos2>=45)
    {
      bandera_tiempo=2;
    }
  }
  
}
