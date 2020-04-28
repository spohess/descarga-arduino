#include <Servo.h>

const int pinoSensor = 2;
const int pinoServo = 3;

const int ledRGBVermelho = 4;
const int ledRGBVerde = 5;
const int ledRGBAzul = 6;

const int ledPausa = 12;

bool numeroUm = false;
bool numeroDois = false;

Servo objetoServo;

void setup() {

  Serial.begin (9600);

  objetoServo.attach(pinoServo);
  objetoServo.write(0);

  pinMode(pinoSensor, INPUT);

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

  int contadorDescarga = 0;

  while (digitalRead(pinoSensor) == LOW) {

    contadorDescarga++;

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
      descargaNumeroUm();
    }

    if ( numeroDois ) {

      numeroDois = false;
      rgbAzul();
      descargaNumeroDois();
    }

    rgbDesligado();
    esperaDescarga();
  }
}

void descargaNumeroUm() {

  int posicao = 0;

  for (posicao = 0; posicao < 180; posicao++) {
    objetoServo.write(posicao);
    delay(10);
  }
  delay(500);
  for (posicao = 180; posicao >= 0; posicao--) {
    objetoServo.write(posicao);
    delay(10);
  }
}

void descargaNumeroDois() {

  int posicao = 0;

  for (posicao = 0; posicao < 180; posicao++) {
    objetoServo.write(posicao);
    delay(10);
  }
  delay(1000);
  for (posicao = 180; posicao >= 0; posicao--) {
    objetoServo.write(posicao);
    delay(10);
  }
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
