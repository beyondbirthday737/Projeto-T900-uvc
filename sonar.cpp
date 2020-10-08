#include <Arduino.h>


// --- Mapeamento de Hardware ---
//TODOS ESSES PINOS SÃO TEMPORÁRIOS
// SERÁ NECESSÁRIO MUDAR.
#define trig 9  // definir o Pino do Arduino que será a saída de trigger
#define echo 8  // definir o Pino do Arduino que será a entrada de echo


void trigPuls();  
void sonarBegin();


float pulse;     
float dist_cm;   


void setup() 
{
    pinMode(trig, OUTPUT);   
    pinMode(echo, INPUT);    

    digitalWrite(trig, LOW);
    Serial.begin(9600);      

}


void loop() 
{
    sonarBegin();
}


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










