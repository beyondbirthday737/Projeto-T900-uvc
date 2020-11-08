#include <Arduino.h>
#include <SoftwareSerial.h>


// --- Mapeamento de Hardware ---
//TODOS ESSES PINOS SÃO TEMPORÁRIOS
// SERÁ NECESSÁRIO MUDAR.

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

#define trig 2 // definir o Pino do Arduino que será a saída de trigger
#define echo 3  // definir o Pino do Arduino que será a entrada de echo


char entrada;
int rotacao = 0 ;

float pulse;     
float dist_cm;   


char appData;  
String inData = "";


// IMPLEMENTAÇÃO DAS FUNÇÕES
void trigPulse()
{
    digitalWrite(trig, HIGH);  
    delayMicroseconds(10);     
    digitalWrite(trig, LOW);   
}


void sonarBegin()
{
    trigPulse();                 
    pulse = pulseIn(echo, HIGH, 200000); 
    dist_cm = pulse/58.82;      

    Serial.println(dist_cm);     
    delay(200);
    
}


void liga(int pino)
{
    digitalWrite(pino,HIGH); 
}

 
void desliga(int pino)
{
    digitalWrite(pino,LOW); 
}


void motor_direita(int pwm)
{
    analogWrite(PWM_MOTOR_2, pwm);
}


void motor_esquerda(int pwm)
{
    analogWrite(PWM_MOTOR_1, pwm);
}


void frente()
{
    liga(MOTOR_ESQ_PIN);
    liga(MOTOR_DIR_PIN);
}


void stopped()
{
    desliga(MOTOR_ESQ_PIN);
    desliga(MOTOR_DIR_PIN);
    desliga(MOTOR_ESQFD_PIN);
    desliga(MOTOR_DIRFD_PIN);
}


void re()
{
    liga(MOTOR_ESQFD_PIN);
    liga(MOTOR_DIRFD_PIN);
}


void execucao(String entrada, void saida())
{
    if (inData == entrada)
    {
      saida();
    }
}


void maximo()
{
    rotacao = 255;
}


void rotation(String entrada,String referencia)
{
    if (entrada == referencia)
    {
          rotacao = entrada.toInt() * 25 ;
    }
}

void esquerda_ft()
{
    desliga(MOTOR_ESQ_PIN);
    liga(MOTOR_DIR_PIN);
}


void esquerda_fd()
{
    liga(MOTOR_ESQFD_PIN);
    desliga(MOTOR_DIRFD_PIN);
}


void decision()
{
    stopped();
    delay(500);
    esquerda_ft();
    delay(500);
    stopped();
    delay(500);

}

void setup() 
{
    pinMode(trig, OUTPUT);   
    pinMode(echo, INPUT);    

    digitalWrite(trig, LOW); 
  
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
    Serial.begin(9600);      

}



void loop() 
{ 
    while (1)
    {
        sonarBegin();
        frente();
        if (dist_cm < 70)
        {
            decision();
        }
    }
      
}

