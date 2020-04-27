#include "Ultrasonic.h"

const int trigPin = 2;
const int echoPin = 3;

const int ledRGBVermelho = 5;
const int ledRGBVerde = 6;
const int ledRGBAzul = 9;

const int ledPausa = 12;

bool numeroUm = false;
bool numeroDois = false;

Ultrasonic ultrasonic(trigPin, echoPin);

void setup() {

  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ledRGBVermelho, OUTPUT);
  analogWrite(ledRGBVermelho, 0);

  pinMode(ledRGBVerde, OUTPUT);
  analogWrite(ledRGBVerde, 0);

  pinMode(ledRGBAzul, OUTPUT);
  analogWrite(ledRGBAzul, 0);

  pinMode(ledPausa, OUTPUT);
  digitalWrite(ledPausa, HIGH);
  delay(500);
  digitalWrite(ledPausa, LOW);
}

void loop() {

  rgbDesligado();

  long distance;
  distance = getDistancia();

  int contadorDescarga = 0;

  while (distance < 10) {

    contadorDescarga++;
    distance = getDistancia();

    if ( contadorDescarga > 10 ) {

      rgbVerde();
      numeroUm = true;
    }

    if ( contadorDescarga > 20 ) {

      rgbVermelho();
      numeroUm = false;
      numeroDois = true;
    }

    if ( contadorDescarga > 55 ) {

      rgbDesligado();
      numeroUm = false;
      numeroDois = false;
    }

    delay(100);
  }

  rgbDesligado();

  if ( numeroUm || numeroDois ) {

    if ( numeroUm ) {

      numeroUm = false;
      rgbAzul();
      delay(6000);
    }

    if ( numeroDois ) {

      numeroDois = false;
      rgbAzul();
      delay(10000);
    }

    rgbDesligado();
    esperaDescarga();
  }
}

long getDistancia() {

  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  return distance;
}

void esperaDescarga() {

  int espera = 0;

  while (espera < 20) {
    digitalWrite(ledPausa, HIGH);
    delay(1000);
    digitalWrite(ledPausa, LOW);
    delay(1000);
    espera++;
  }

  espera = 0;
  while (espera < 3) {
    digitalWrite(ledPausa, HIGH);
    delay(50);
    digitalWrite(ledPausa, LOW);
    delay(50);
    espera++;
  }

}

void rgbVermelho() {

  analogWrite(ledRGBVermelho, 255);
  analogWrite(ledRGBVerde, 0);
  analogWrite(ledRGBAzul, 0);
}

void rgbVerde() {

  analogWrite(ledRGBVermelho, 0);
  analogWrite(ledRGBVerde, 255);
  analogWrite(ledRGBAzul, 0);
}

void rgbAzul() {

  analogWrite(ledRGBVermelho, 0);
  analogWrite(ledRGBVerde, 0);
  analogWrite(ledRGBAzul, 255);
}

void rgbDesligado() {

  digitalWrite(ledRGBVermelho, LOW);
  digitalWrite(ledRGBVerde, LOW);
  digitalWrite(ledRGBAzul, LOW);
}
