#include <NewPing.h>
#include <toneAC.h>

int echo = 6;  // echo
int trig = 5;  // positivo trig gnd
int echo1 = 12;  // gnd echo
int trig1 = 11;  // positivo trig
float indice0, indice1; //CAMBIAMOS LOS VALORES DE LOS SENSORES DE 15 Y 25 MAS CORTOS PARA PRACTICAR MEJOR
int maxDistance = 100 , maxDistance1 = 100;   //El más largo es para la 9 de oct, ya que el paso cebra es más grande 
int valoresSensores[2];
NewPing sensorAO(trig, echo, maxDistance);
NewPing sensor9O(trig1, echo1, maxDistance1);
float angulo1, angulo2;
float AlturaSensor = 2.3; //7.3 cm es lo que yo medí de altura en la maqueta
void setup() {
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig1, OUTPUT);
}
void loop() {
  mediciones();
  delay(1000);
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
    Serial.print(indice0);
    Serial.print(", El ángulo de inclinación es: ");
    angulo1 = asin(AlturaSensor / indice0);
    angulo1 = angulo1 * (180/PI);
    Serial.println(angulo1);
    Serial.print(" Matriz indice 1: ");
    Serial.print(valoresSensores[1]);
    indice1 = valoresSensores[1];
    Serial.print(", La variable indice1 es: ");
    if (indice1 == 0) {
      indice1 = maxDistance1;
    }
    Serial.print(indice1);
    Serial.print(", El ángulo de inclinación es: ");
    angulo2 = asin(AlturaSensor / indice1);
    angulo2 = angulo2 * (180/PI);
    Serial.println(angulo2);
    return;
  }
 