
#include <MPU6050_tockn.h> //biblioteca para uso da IMU
#include <Wire.h> //permite a conexão com dispositivos I2C como a IMU
#include <Servo.h> //biblioteca que permite o uso de funções do servo

Servo myservo;//cria um objeto servo para controlar o servo

double readAngle = 0;//variavel de leitura do angulo
double setpoint = 30; //angulo desejado de descida
double error = 0; //variavel de erro de controle
double lastAngle = 0; //ultimo Angulo em x lido

//Controle de tempo
unsigned long previousMillis = 0;//variavel de tempo anterior
const long interval = 52000; //intervalo de tempo para Descida
unsigned long currentMillis = 0;//variavel de tempo atual

//Variaveis de Controle
float P = 0,//proporcional
      I = 0, //integral
      D = 0; //derivativo

float kP = 1, 
      kI = 0.5,
      kD = 3;

int controleMotor = 0;//variavel de potência do motor

MPU6050 mpu6050(Wire); //define a conexão I2C com a IMU

void setup() {
  Serial.begin(9600);
  Wire.begin(); //inicia comunicação I2C
  myservo.attach(9);// aloca o servo na porta digital 9 do arduino
  mpu6050.begin(); //inicia a MPU 6050
  mpu6050.calcGyroOffsets(true);// Calibra os angulos com base na sitação atual do robô
}

void loop() {
  //define o tempo atual como a função millis() que conta o tempo decorrido do programa em milissegundos
  currentMillis = millis();
  
  mpu6050.update();//atualiza leitura da IMU
  monitorSerial_Angles();//exibição dos agulos lidos através do Monitor Serial

//se o tempo atual menos tempo anterior for maior que o intervalo, entra no if
  if (currentMillis - previousMillis >= interval) {
     previousMillis = currentMillis; //tempo anterior = tempo atual
    setpoint=setpoint*(-1);//inverte o angulo de inclinação do robô
  }
  //armzena o valor do angulo em X na variavel readAngle
  readAngle = mpu6050.getAngleZ();
  //Serial.print("readAngle: ");
  //Serial.println(readAngle);

  /*converte para controle:
  0 - Velocidade máxima sentido antihorário
  90 - servo parado
  180 - Velocidade máxima sentido horário
  */
  controleMotor = 90 + PID() ;

//se o valor for maior que 180, limita a velocidade horaria do servo
  if (controleMotor > 180) {
    controleMotor = 180;
  }
 //se o valor for menor que 0, limita a velocidade antihoraria do servo
  if (controleMotor < 0) {
    controleMotor = 0;
  }

  //saida do controle
  myservo.write(controleMotor);//valor do PID aplicado a potencia do motor

}
