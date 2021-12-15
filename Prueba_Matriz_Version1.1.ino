#include "LedControl.h" 

LedControl lc=LedControl(11,13,10,1); //11=DIN 13=CLK 10=CS 1=numero de dispositivos
LedControl lc2=LedControl(9,12,8,1); //DIN=9 CLK=12 CS=8 1=numero de dispositivos

int contador1=0;
int contador2=0;
int col_inicio;
int col_fin;

//VARIABLES PARA EL PRIMER TABLERO
//variables posicion arreglos derecho y izquierdo para primer tablero
int pos1=0;
//variables boton sumar restar primer tablero
int sumar1=0; //pin 7
int sumar1A=0;
int restar1=0; //pin 6
int restar1A=0;
int estado_sumar1=0;
int estado_restar1=0;

//VARIABLES PARA EL SEGUNDO TABLERO
//variables posicion arreglos derecho y izquierdo para segundo tablero
int pos2=0;
//variables boton sumar restar segundo tablero
int sumar2=0; //pin5
int sumar2A=0;
int restar2=0; //pin4
int restar2A=0;
int estado_sumar2=0;
int estado_restar2=0;

int cero[32] {
  0,1,1,0,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  0,1,1,0
};

int uno[32] {
  0,0,1,0,
  0,1,1,0,
  1,0,1,0,
  0,0,1,0,
  0,0,1,0,
  0,0,1,0,
  0,0,1,0,
  0,1,1,1
};

int dos[32]{
  0,1,1,0,
  1,0,0,1,
  0,0,0,1,
  0,0,0,1,
  0,0,1,0,
  0,1,0,0,
  1,0,0,0,
  1,1,1,0

};

int tres[32]{
  1,1,1,1,
  0,0,0,1,
  0,0,0,1,
  0,0,0,1,
  0,1,1,0,
  0,0,0,1,
  0,0,0,1,
  1,1,1,1

};

int cuatro[32]{
  0,0,0,1,
  0,0,1,1,
  0,1,0,1,
  1,0,0,1,
  1,1,1,1,
  0,0,0,1,
  0,0,0,1,
  0,0,0,1

};

int cinco[32]{
  1,1,1,1,
  1,0,0,0,
  1,0,0,0,
  1,1,1,1,
  0,0,0,1,
  0,0,0,1,
  0,0,0,1,
  1,1,1,1
};

int seis[32]={
  1,1,1,1,
  1,0,0,1,
  1,0,0,0,
  1,0,0,0,
  1,1,1,1,
  1,0,0,1,
  1,0,0,1,
  1,1,1,1
};

int siete[32]={
  1,1,1,1,
  0,0,0,1,
  0,0,0,1,
  0,0,1,0,
  0,1,0,0,
  1,0,0,0,
  1,0,0,0,
  1,0,0,0
};

int ocho[32]={
  0,1,1,0,
  1,0,0,1,
  1,0,0,1,
  0,1,1,0,
  1,0,0,1,
  1,0,0,1,
  1,0,0,1,
  0,1,1,0
};

int nueve[32]={
  1,1,1,1,
  1,0,0,1,
  1,0,0,1,
  1,1,1,1,
  0,0,0,1,
  0,0,0,1,
  0,0,0,1,
  1,1,1,1
};

void setup() {
  Serial.begin(9600);
  for(int x=4; x<=7; x++)
  {
    pinMode(x,INPUT);
  }
  
  //CONFIGURACION TABLERO 1
  lc.shutdown(0,false);
  lc.setIntensity(0,4); 
  lc.clearDisplay(0);
  //prende al tablero 1 en ceros
  for(int fila = 0; fila < 8; fila++) //unidad
  {
    for(int columna = 4; columna < 8; columna++) 
    {
      lc.setLed(0,fila,columna,cero[pos1]);
      delay(80);
      pos1=1+pos1;
    }
  }
  pos1=0;
  for(int fila = 0; fila < 8; fila++) //decena
  {
    for(int columna = 0; columna < 4; columna++) 
    {
      lc.setLed(0,fila,columna,cero[pos1]);
      delay(80);
      pos1=1+pos1;
    }
  }
  pos1=0;
  
  //CONFIGURACION TABLERO 2
  lc2.shutdown(0,false);
  lc2.setIntensity(0,4); 
  lc2.clearDisplay(0);
  //prende al tablero 2 en ceros
  pos2=0;
  for(int fila = 0; fila < 8; fila++) //unidad
  {
    for(int columna = 4; columna < 8; columna++) 
    {
      lc2.setLed(0,fila,columna,cero[pos2]);
      delay(80);
      pos2=1+pos2;
    }
  }
  pos2=0;
  for(int fila = 0; fila < 8; fila++) //unidad
  {
    for(int columna = 0; columna < 4; columna++) 
    {
      lc2.setLed(0,fila,columna,cero[pos2]);
      delay(80);
      pos2=1+pos2;
    }
  }
}

void loop()
{
  sumar1=digitalRead(7);
  restar1=digitalRead(6);
  sumar2=digitalRead(5);
  restar2=digitalRead(4);

  //INICIA PROGRAMA PRIMER TABLERO SUMAR  
  if(sumar1==HIGH && sumar1A==LOW)
  {
    estado_sumar1 = 1 - estado_sumar1;
    delay(80);
  }
  sumar1A=sumar1;
  if(estado_sumar1==1)
  {
    Serial.println("ENTRA A SUMAR AL PRIMER TABLERO");
    estado_sumar1=0;
    contador1=contador1+1;
    if(contador1>99)
    {
      contador1=0;
    }
    imprimir_tablero1();
  }

  //INICIA PROGRAMA PRIMER TABLERO RESTAR
  if(restar1==HIGH && restar1A==LOW)
  {
    estado_restar1 = 1 - estado_restar1;
    delay(80);
  }
  restar1A=restar1;
  if(estado_restar1==1)
  {
    Serial.println("ENTRA A RESTAR AL PRIMER TABLERO");
    estado_restar1=0;
    contador1=contador1-1;
    if(contador1<=0)
    {
      contador1=0;
    }
    imprimir_tablero1();
    //AQUI VAN LOS CASOS DONDE SE RESTA AL TABLERO UNO
  }

  //INICIA PROGRAMA SEGUNDO TABLERO SUMAR
  if(sumar2==HIGH && sumar2A==LOW)
  {
    estado_sumar2 = 1 - estado_sumar2;
    delay(80);
  }
  sumar2A=sumar2;
  if(estado_sumar2==1)
  {
    Serial.println("ENTRA A SUMAR AL SEGUNDO TABLERO");
    estado_sumar2=0;
    contador2=contador2+1;
    if(contador2>99)
    {
      contador2=0;
    }
    imprimir_tablero2();
  }

  //INICIA PROGRAMA SEGUNDO TABLERO RESTAR
  if(restar2==HIGH && restar2A==LOW)
  {
    estado_restar2 = 1 - estado_restar2;
    delay(80);
  }
  restar2A=restar2;
  if(estado_restar2==1)
  {
    Serial.println("ENTRA A RESTAR AL SEGUNDO TABLERO");
    estado_restar2=0;
    contador2=contador2-1;
    if(contador2<0)
    {
      contador2=0;
    }
    imprimir_tablero2();
    //AQUI VAN LOS CASOS DONDE SE RESTA AL TABLERO DOS
  }
}

void imprimir_tablero1()
{
  int decena=contador1/10;
  int unidad=contador1-(decena*10);
  col_inicio=4;
  col_fin=8;
  imprimir_casos(unidad);
  col_inicio=0;
  col_fin=4;
  imprimir_casos(decena);
}

void imprimir_tablero2()
{
  int decena=contador2/10;
  int unidad=contador2-(decena*10);
  col_inicio=4;
  col_fin=8;
  imprimir_casos2(unidad); //AQUIII2
  col_inicio=0;
  col_fin=4;
  imprimir_casos2(decena);
}

void imprimir_casos(int num)
{
  pos1=0;
  switch(num)
  {
    case 0:
      imprimir0_lc();
    break;
    case 1:
      imprimir1_lc();
    break;
    case 2:
      imprimir2_lc();
    break;
    case 3:
      imprimir3_lc();
    break;
    case 4:
      imprimir4_lc();
    break;
    case 5:
      imprimir5_lc();
    break;
    case 6:
      imprimir6_lc();
    break;
    case 7:
      imprimir7_lc();
    break;
    case 8:
      imprimir8_lc();
    break;
    case 9:
      imprimir9_lc();
    break;
  }
}

void imprimir_casos2(int num)
{
  pos2=0;
  switch(num)
  {
    case 0:
      imprimir0_lc2();
    break;
    case 1:
      imprimir1_lc2();
    break;
    case 2:
      imprimir2_lc2();
    break;
    case 3:
      imprimir3_lc2();
    break;
    case 4:
      imprimir4_lc2();
    break;
    case 5:
      imprimir5_lc2();
    break;
    case 6:
      imprimir6_lc2();
    break;
    case 7:
      imprimir7_lc2();
    break;
    case 8:
      imprimir8_lc2();
    break;
    case 9:
      imprimir9_lc2();
    break;
  }
}

void imprimir0_lc()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc.setLed(0,fila,columna,cero[pos1]);
          delay(10);
          pos1=1+pos1;
        }
      }
  pos1=0;
}

void imprimir1_lc()
{
  for(int fila = 0; fila < 8; fila++) 
  {
    for(int columna = col_inicio; columna < col_fin; columna++) 
    {
      lc.setLed(0,fila,columna,uno[pos1]);
      delay(10);
      pos1=1+pos1;
    }
  }
  pos1=0;
}

void imprimir2_lc()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc.setLed(0,fila,columna,dos[pos1]);
          delay(10);
          pos1=1+pos1;
        }
      }
  pos1=0;
}

void imprimir3_lc()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc.setLed(0,fila,columna,tres[pos1]);
          delay(10);
          pos1=1+pos1;
        }
      }
  pos1=0;
}

void imprimir4_lc()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc.setLed(0,fila,columna,cuatro[pos1]);
          delay(10);
          pos1=1+pos1;
        }
      }
  pos1=0;
}

void imprimir5_lc()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc.setLed(0,fila,columna,cinco[pos1]);
          delay(10);
          pos1=1+pos1;
        }
      }
  pos1=0;
}

void imprimir6_lc()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc.setLed(0,fila,columna,seis[pos1]);
          delay(10);
          pos1=1+pos1;
        }
      }
  pos1=0;
}

void imprimir7_lc()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc.setLed(0,fila,columna,siete[pos1]);
          delay(10);
          pos1=1+pos1;
        }
      }
  pos1=0;
}

void imprimir8_lc()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc.setLed(0,fila,columna,ocho[pos1]);
          delay(10);
          pos1=1+pos1;
        }
      }
  pos1=0;
}

void imprimir9_lc()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc.setLed(0,fila,columna,nueve[pos1]);
          delay(10);
          pos1=1+pos1;
        }
      }
  pos1=0;
}

//METODOS PARA EL SEGUNDO TABLERO
void imprimir0_lc2()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc2.setLed(0,fila,columna,cero[pos2]);
          delay(10);
          pos2=1+pos2;
        }
      }
  pos2=0;
}

void imprimir1_lc2()
{
  for(int fila = 0; fila < 8; fila++) 
  {
    for(int columna = col_inicio; columna < col_fin; columna++) 
    {
      lc2.setLed(0,fila,columna,uno[pos2]);
      delay(10);
      pos2=1+pos2;
    }
  }
  pos2=0;
}

void imprimir2_lc2()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc2.setLed(0,fila,columna,dos[pos2]);
          delay(10);
          pos2=1+pos2;
        }
      }
  pos2=0;
}

void imprimir3_lc2()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc2.setLed(0,fila,columna,tres[pos2]);
          delay(10);
          pos2=1+pos2;
        }
      }
  pos2=0;
}

void imprimir4_lc2()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc2.setLed(0,fila,columna,cuatro[pos2]);
          delay(10);
          pos2=1+pos2;
        }
      }
  pos2=0;
}

void imprimir5_lc2()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc2.setLed(0,fila,columna,cinco[pos2]);
          delay(10);
          pos2=1+pos2;
        }
      }
  pos2=0;
}

void imprimir6_lc2()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc2.setLed(0,fila,columna,seis[pos2]);
          delay(10);
          pos2=1+pos2;
        }
      }
  pos2=0;
}

void imprimir7_lc2()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc2.setLed(0,fila,columna,siete[pos2]);
          delay(10);
          pos2=1+pos2;
        }
      }
  pos2=0;
}

void imprimir8_lc2()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc2.setLed(0,fila,columna,ocho[pos2]);
          delay(10);
          pos2=1+pos2;
        }
      }
  pos2=0;
}

void imprimir9_lc2()
{
  for(int fila = 0; fila < 8; fila++) 
      {
        for(int columna = col_inicio; columna < col_fin; columna++) 
        {
          lc2.setLed(0,fila,columna,nueve[pos2]);
          delay(10);
          pos2=1+pos2;
        }
      }
  pos2=0;
}
