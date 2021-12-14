#include <Servo.h>

//variables de los servos
Servo out;
Servo in;
//programa de luces del parking
int val;
int x;
int x2;
int boton_in=0;
int boton_out=0;
int encendido=0;
int estado = 0;
int contador=0;
int boton_inA=0;
int boton_outA=0;
int boton_inEstado=0;
int boton_outEstado=0;
int grado_entrada=0;
int grado_salida=0;

void setup() {
  //inicializamos los servos
  in.attach(3);
  out.attach(5);
  in.write(0);
  out.write(0);
  //botones
  pinMode(6, INPUT);
  pinMode(9, INPUT);
  //leds para la parte izquierda del parking
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(8, OUTPUT);
  //leds para la parte derecha del parking
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //===========INICIA PROGRAMA DE LAS LUCES============
  val = analogRead(A0);
  x = map(val, 0, 1025, 0, 255);
  Serial.print("VALOR X: ");
  Serial.println(x);
  delay(200);
  if (x >= 195 && x <= 255)
  {
    digitalWrite(13, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(2, HIGH);
    Serial.println("LUCES ENCENDIDAS");
  } else {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    Serial.println("LUCES APAGADAS");
  }
  //=========INICIA PROGRAMA DE LOS SERVOS============
  boton_in = digitalRead(6);
  boton_out = digitalRead(9);
  //INICIA PROGRAMA BOTON ENTRADA
  if(boton_in==HIGH && boton_inA==LOW)
  {
    boton_inEstado = 1 - boton_inEstado;
    delay(80);
  }
  boton_inA=boton_in;
  if (boton_inEstado == 1)
  {
    if(grado_entrada==0)
    {
      in.write(95);
      grado_entrada=95;
      Serial.println("SERVO1 ABRIR");
      boton_inEstado=0;
    }else{
      if(grado_entrada=95)
      {
        in.write(0); 
        grado_entrada=0;
        Serial.println("SERVO1 CERRAR");
        boton_inEstado=0;
      }
    }
  }
  //INICIA PROGRAMA BOTON SALIDA
  if(boton_out==HIGH && boton_outA==LOW)
  {
    boton_outEstado = 1 - boton_outEstado;
    delay(80);
  }
  boton_outA=boton_out;
  if (boton_outEstado == 1)
  {
    if(grado_salida==0)
    {
      out.write(95);
      grado_salida=95;
      Serial.println("SERVO2 ABRIR");
      boton_outEstado=0;
    }else{
      if(grado_salida=95)
      {
        out.write(0); 
        grado_salida=0;
        Serial.println("SERVO2 CERRAR");
        boton_outEstado=0;
      }
    }
  }
  delay(500);
}
