
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>//include library code to communicate with SPI devices
#include <SD.h>//include library code for SD card

const int chipSelect = 10;

Servo myservo;  // create servo object to control a servo

TinyGPSPlus gps;// The TinyGPS++ object

SoftwareSerial ss(4, 3);// The serial connection to the GPS device (RX=4 e TX=3)

double readAngle = 0;
int setpointD = -30; //angulo desejado de descida
double error = 0;

//Controle de tempo
unsigned long previousMillis = 0;
const long interval = 1000; //intervalo de tempo para Descida
unsigned long currentMillis = 0;

//Variaveis de Controle
double P = 0,
       I = 0,
       D = 0;

double kP = 1,
       kI = 0,
       kD = 0;
int controleMotor = 0;

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  myservo.attach(9);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  ss.begin(9600);
  //inicialização do SD Cards
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present!");
    return;
  }
  File dataFile = SD.open("gps.csv", FILE_WRITE); //opens file
  if (dataFile) { //if the file opened ok, writes to it
    dataFile.println("Date, Time , Lat , Long , Sats , HDOP , Alt, Speed");//prints the headings for our data
  }
  dataFile.close();//file closed
}

void loop() {

  mpu6050.update();//atualiza leitura da IMU
  //monitorSerial_Angles();//exibição dos agulos lidos através do Monitor Serial
  currentMillis = millis();
  //armzena o valor do angulo em X na variavel readAngle
  readAngle = mpu6050.getAngleX();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Serial.print("readAngle: ");
    Serial.println(readAngle);

    //converte para controle
    controleMotor = 90 + PID() ;

    if (controleMotor > 180) { //Limita velocidade maxima no sentido horário
      controleMotor = 180;
    }
    if (controleMotor < 0) { //Limita velcidade máxima no sentido anti-horário
      controleMotor = 0;
    }
    //Saída do Controle
    myservo.write(controleMotor);
  }

  while(ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      Serial.println("GPS Ativado");
      monitorSerial_GPS();
      File dataFile = SD.open("gpsdata.csv", FILE_WRITE);//The routine for writing data to SD card:
      if (dataFile) {// if the file is available, write to it:
        gps.encode(ss.read());
        Serial.println("Printing In SD ");
        dataFile.print(gps.date.value());
        dataFile.print("/");
        dataFile.print(gps.time.value());
        dataFile.print("/");
        dataFile.print(gps.location.lat(), 6);
        dataFile.print("/");
        dataFile.print(gps.location.lng(), 6);
        dataFile.print("/");
        dataFile.print(gps.satellites.value());
        dataFile.print("/");
        dataFile.print(gps.hdop.value());
        dataFile.print("/");
        dataFile.print(gps.altitude.meters());
        dataFile.print("/");
        dataFile.print(gps.speed.mps());
        dataFile.print("\n");
        dataFile.close();
      }
    }
  }//Fim while GPS
}
