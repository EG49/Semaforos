#include <NewPing.h>
#include <toneAC.h>
int rojo9O = 7;  //9   2   /7 pq 9 lo ocupa la libreria tone ac
int amarillo9O = 13;  //10   3  tone ac le da corriente a 10 y 9 continuamente
int verde9O = 8;  //8   4
int echo = 6;  // echo
int trig = 5;  // positivo trig gnd
int echo1 = 12;  // gnd echo
int trig1 = 11;  // positivo trig
int buzzer = 9; //Buzzer
int indice0, indice1;
int rojoAO = 2;  //2    9
int verdeAO = 4;  //4    8
int amarilloAO = 3; //3    10            //CAMBIAMOS LOS VALORES DE LOS SENSORES DE 15 Y 25 MAS CORTOS PARA PRACTICAR MEJOR
int frecuencia1 = 500;
int maxDistance = 15 , maxDistance1 = 25;   //El más largo es para la 9 de oct, ya que el paso cebra es más grande 
int valoresSensores[2];
NewPing sensorAO(trig, echo, maxDistance);
NewPing sensor9O(trig1, echo1, maxDistance1);
void setup() {
  Serial.begin(9600);
  pinMode(rojo9O, OUTPUT);
  pinMode(amarillo9O, OUTPUT);
  pinMode(verde9O, OUTPUT);
  pinMode(rojoAO, OUTPUT);
  pinMode(verdeAO, OUTPUT);
  pinMode(amarilloAO, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig1, OUTPUT);
  pinMode(buzzer, OUTPUT);
}
void loop() {
  tnormal();
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(100);
  digitalWrite(trig, HIGH);
  delayMicroseconds(100);
  digitalWrite(trig, LOW);
  digitalWrite(trig1, LOW);
  digitalWrite(echo1, LOW);
  delayMicroseconds(100);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(100);
  digitalWrite(trig1, LOW);
} 
void tnormal(){
    toneAC();  //Apagamos los sensores
    Serial.println("Entrando en tráfico normal");
    prender(rojo9O, "rojo9O"); //usamos esta función para mostrar por serial un print al prender
    prender(verdeAO, "verdeAO");
    medirComprobar();   //Medimos que existe en los sensores y en caso de existir algo se comprueba que tienen más cerca
    digitalWrite(verdeAO, LOW);
    prender(amarilloAO, "amarilloAO");
    delay(1000);
    digitalWrite(amarilloAO, LOW);
    digitalWrite(rojo9O, LOW);
    prender(rojoAO, "rojoAO");
    prender(verde9O, "verde9O");
    toneAC(frecuencia1);  //Prendemos el parlante
    medirComprobar();
    toneAC();
    digitalWrite(verde9O, LOW);
    digitalWrite(amarillo9O, HIGH);
    prender(amarillo9O, "amarillo9O");
    delay(1000);
    digitalWrite(amarillo9O, LOW);
    digitalWrite(rojoAO, LOW);
    prender(rojo9O, "rojo9O");
    prender(verdeAO, "verdeAO");
}
  void mediciones(){
    valoresSensores[0] = sensorAO.ping_cm();
    valoresSensores[1] = sensor9O.ping_cm();
    Serial.print(" Matriz indice 0: ");
    Serial.print(valoresSensores[0]);
    indice0 = valoresSensores[0];
    Serial.print(", La variable indice0 es: ");
     if (indice0 == 0) {
      indice0 = maxDistance1;  //El maxDistance más largo para no tener problemas con la comparación
    }
    Serial.println(indice0);
    Serial.print(" Matriz indice 1: ");
    Serial.print(valoresSensores[1]);
    indice1 = valoresSensores[1];
    Serial.print(", La variable indice1 es: ");
    if (indice1 == 0) {
      indice1 = maxDistance1;
    }
    Serial.println(indice1);
    return;
  }
  void comprobaciones(){
  
    if(indice0 < indice1){
      trafico();
    }
    if(indice0 > indice1){
      trafico1();
    }
  }
  void trafico(){
    toneAC();
    Serial.println("====================== ACTIVANDO PROTOCOLO DE TRÁFICO ======================");
    digitalWrite(rojoAO, LOW);
    digitalWrite(verde9O, LOW);
    while(indice0 != maxDistance1){   //Mientras que el sensor tenga un objeto no cambiará el semáforo
      prender(rojo9O, "rojo9O");
      prender(verdeAO, "verdeAO");
      mediciones();
    } 
    delay(1500);
    digitalWrite(verdeAO, LOW);
    prender(amarilloAO, "amarilloAO");
    delay(1000);
    digitalWrite(amarilloAO, LOW);
    digitalWrite(rojo9O, LOW);
    prender(rojoAO, "rojoAO");
    prender(verde9O, "verde9O");
    toneAC(frecuencia1);
    medirComprobar();
    toneAC();
    digitalWrite(verde9O, LOW);
    prender(amarillo9O, "amarillo9O");
    delay(1000);
    digitalWrite(amarillo9O, LOW);
    indice0, indice1 = maxDistance1;
    digitalWrite (rojoAO, LOW);
    digitalWrite (verde9O, LOW);
    digitalWrite (amarilloAO, LOW);
    tnormal();
  }
  void trafico1(){
    toneAC();
    Serial.println("====================== ACTIVANDO PROTOCOLO DE TRÁFICO1 ======================");
    digitalWrite(verdeAO, LOW);
    digitalWrite(rojo9O, LOW);
    while(indice1 != maxDistance1){
      toneAC(frecuencia1);
      prender(verde9O, "verde9O");
      prender(rojoAO, "rojoAO");
      mediciones();
    }
    delay(1500);
    toneAC();
    digitalWrite(verde9O, LOW);
    prender(amarillo9O, "amarillo9O");
    delay(1000);
    digitalWrite(amarillo9O, LOW);
    digitalWrite(rojoAO, LOW);
    prender(rojo9O, "rojo9O");
    prender(verdeAO, "verdeAO");
    medirComprobar(); 
    indice0, indice1 = maxDistance1;
    // Volver a tráfico normal
    digitalWrite (rojoAO, LOW);
    digitalWrite (verde9O, LOW);
    digitalWrite (amarillo9O, LOW);
    digitalWrite (amarilloAO, LOW);
    tnormal();
  }
  void prender(int color, String led){
    digitalWrite(color, HIGH);
    Serial.print(led);      //Muetro por serial cual es el led que se prende
    Serial.println("ON");
    
  }
  void medirComprobar(){
    mediciones();
    if((indice0 || indice1) != (maxDistance1)){  //El maxdistance màs largo
      comprobaciones();
    }
    delay(1000);
    mediciones();
    if((indice0 || indice1) != (maxDistance1)){
      comprobaciones();
    }
    delay(1000); 
    mediciones();
    if((indice0 || indice1) != (maxDistance1)){
      comprobaciones();
    }
    delay(1000);
    mediciones();
    if((indice0 || indice1) != (maxDistance1)){
      comprobaciones();
    } 
  }
