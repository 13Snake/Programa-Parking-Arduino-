//PROGRAMA DE LA MOVIDA DEL HUMO Y DEL DETECTOR DE FLAMA

//Variables de los sensores
int sensorh1=0;
int sensorh2=0;
//Variables de boton apagar/encende circuito
int apagado=0;
int apagadoA=0;
int apagadoE=0;
//Variable de boton encender piezos sin detectar nada
int piezo=0; 
int piezoA=0;
int piezoE=0;
//Variables de los seguidores de linea (FLAMA)
int poste1;
int poste1A;
int poste2;
int poste2A;

void setup() {
  //pines para los timbres
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  //pines para los botones
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  //Pin de los sensores de linea
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  //Inicializando sensores
  Serial.begin(9600);
  Serial.println("INICIANDO SENSORES");
  delay(3000); //delay para que caliente las bobinas
  //pin que dice que estan listos los sensores
  pinMode(6,OUTPUT); //pin de led verde
  pinMode(7,OUTPUT); //pin de led naranja
  pinMode(8,OUTPUT); //pin de led rojo
  
  digitalWrite(6,HIGH);
  
  Serial.println("LISTO");
}

void loop() {
  //variables de los sensores de llama
  poste1=digitalRead(9);
  poste2=digitalRead(10);
  //INICIO PROGRAMA DE LOS HUMOS
  apagado=digitalRead(4);
  digitalWrite(6,HIGH);
  if(apagado==HIGH && apagadoA==LOW)
  {
    apagadoE=1-apagadoE;
    delay(80);
  }
  apagadoA=apagado;
  if(apagadoE==1)
  {
    digitalWrite(8,HIGH);
    piezo=digitalRead(5);
    if(piezo==HIGH && piezoA==LOW)
    {
      piezoE = 1-piezoE;
      delay(20);
    }
    if(piezoE==1) //sino detecta nada pero queremos que se activen
    {
      digitalWrite(7,HIGH);
      tone(2,3000,200);
      delay(100);
      tone(3,3000,200);
      delay(800);
    }else{
      if(poste1!=HIGH || poste2!=HIGH) //si hay alguna FLAMA
      {
        tone(2,4000,200);
        delay(100);
        tone(3,4000,200);
        delay(800);
        Serial.println("LLAMA");
      }
       //Leo los valores de cada sensor
      sensorh1=analogRead(A0);
      sensorh2=analogRead(A1);
      Serial.print("SENSOR1=");
      Serial.println(sensorh1);
      Serial.print("SENSOR2=");
      Serial.println(sensorh2);
      if(sensorh1 > 80 || sensorh2 > 80) //si detecta humo o gas enciende piezos
      {
        tone(2,5000,200);
        delay(100);
        tone(3,5000,200);
        delay(800);
      }else{
        noTone(2);
        noTone(3);
      } 
    }
    digitalWrite(6,LOW);
  }else{
    piezoE=0;
    digitalWrite(8,LOW);
  }
  digitalWrite(7,LOW); 
  
}
