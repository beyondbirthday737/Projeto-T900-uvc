#include <SoftwareSerial.h>

SoftwareSerial HM10(2, 3); // RX = 2, TX = 3

char appData;  
String inData = "";

#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//MOTOR 1
#define MOTOR_ESQ_PIN 7
#define MOTOR_ESQFD_PIN 8

//MOTOR 2
#define MOTOR_DIR_PIN 4
#define MOTOR_DIRFD_PIN 9

#define PWM_MOTOR_1 5
#define PWM_MOTOR_2 6

#define CURRENT_SEN_1 A2
#define CURRENT_SEN_2 A3

#define EN_PIN_1 A0
#define EN_PIN_2 A1

#define MOTOR_1 0
#define MOTOR_2 1

char entrada = "";
int rotacao = 0 ;

void setup() {
  
  Serial.begin(9600); 
  HM10.begin(9600);
  
  pinMode(MOTOR_ESQ_PIN, OUTPUT);
  pinMode(MOTOR_ESQFD_PIN, OUTPUT);

  pinMode(MOTOR_DIR_PIN, OUTPUT);
  pinMode(MOTOR_DIRFD_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  pinMode(PWM_MOTOR_2, OUTPUT);

  pinMode(CURRENT_SEN_1, OUTPUT);
  pinMode(CURRENT_SEN_2, OUTPUT);

  pinMode(EN_PIN_1, OUTPUT);
  pinMode(EN_PIN_2, OUTPUT);

  digitalWrite(EN_PIN_1, LOW);
  digitalWrite(EN_PIN_2, LOW);
  
}

void liga(int pino){
  digitalWrite(pino,HIGH); 
}
 
void desliga(int pino){
  digitalWrite(pino,LOW); 
}

void motor_direita(int pwm){
    analogWrite(PWM_MOTOR_2, pwm);
}

void motor_esquerda(int pwm){
    analogWrite(PWM_MOTOR_1, pwm);
}

void frente(){
  liga(MOTOR_ESQ_PIN);
  liga(MOTOR_DIR_PIN);
}

void stopped(){
  desliga(MOTOR_ESQ_PIN);
  desliga(MOTOR_DIR_PIN);
  desliga(MOTOR_ESQFD_PIN);
  desliga(MOTOR_DIRFD_PIN);
}

void re(){
  liga(MOTOR_ESQFD_PIN);
  liga(MOTOR_DIRFD_PIN);
}

void execucao(String entrada, void saida()){
  if (inData == entrada){
    saida();
  }
 }

 void maximo(){
  rotacao = 255;
}

 void rotation(String entrada,String referencia){
   if (entrada == referencia){
        rotacao = entrada.toInt() * 25 ;
    }
 }

 void direita_ft(){
    liga(MOTOR_ESQ_PIN);
    desliga(MOTOR_DIR_PIN);
 }

 void esquerda_ft(){
    desliga(MOTOR_ESQ_PIN);
    liga(MOTOR_DIR_PIN);
 }

  void esquerda_fd(){
    liga(MOTOR_ESQFD_PIN);
    desliga(MOTOR_DIRFD_PIN);
 }

 void direita_fd(){
    desliga(MOTOR_ESQFD_PIN);
    liga(MOTOR_DIRFD_PIN);
 }

void loop() {
  
  HM10.listen(); 

  while (HM10.available() > 0) {   // if HM10 sends something then read
    appData = HM10.read();
    inData = String(appData);
    digitalWrite(EN_PIN_1, HIGH);
    digitalWrite(EN_PIN_2, HIGH);// save the data in string format
    Serial.print(appData);
    execucao("F",frente); 
    execucao("S",stopped);
    execucao("B",re); 
    execucao("q",maximo);
    execucao("I",direita_ft);
    execucao("G",esquerda_ft);
    execucao("H",direita_fd);
    execucao("J",esquerda_fd);

    for (int i = 0;i < 10;i++){
        String value = String(i);
        rotation(inData,value);
    }
    
    motor_direita(rotacao);
    motor_esquerda(rotacao);
  }

}
