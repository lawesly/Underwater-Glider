#include <Servo.h>

Servo myservo;

//Controle de tempo
unsigned long previousMillis = 0;
const long interval = 51000; //intervalo de tempo para Descida
unsigned long currentMillis = 0;
int pin = 1;
int controleMotor = 0;

void setup () {
  Serial.begin(9600);
  myservo.attach(9);
}
void loop() {

  currentMillis = millis();
  //Serial.print("Millis: ");
  //Serial.println(currentMillis);
  //Serial.print("PreviousMillis: ");
  //Serial.println(previousMillis);

  if (currentMillis - previousMillis >= interval) {
    pin = pin * (-1);
    controleMotor = 90;
    myservo.write(controleMotor);
    delay(5000);
    previousMillis = millis();
  }
  if (pin > 0) {
    Serial.println("Descendo.... ");
    controleMotor = 0;
    myservo.write(controleMotor);
  } else {
    Serial.println("Subindo.... ");
    controleMotor = 180;
    myservo.write(controleMotor);
  }

}



