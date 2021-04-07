#include <Ultrasonic.h> 

// Configuração dos sensores
#define TRIGGER_PIN1 4               
#define ECHO_PIN1    5 

#define TRIGGER_PIN2 12             
#define ECHO_PIN2    13

#define TRIGGER_PIN3 14              
#define ECHO_PIN3    15
              
//configuração dos motores
#define IN1 6                       
#define IN2 7                       
#define IN3 8                       
#define IN4 9                       

#define ENA 10                      
#define ENB 11

// configuração do LED
#define LED 16


Ultrasonic ultrasonic_frente(TRIGGER_PIN1, ECHO_PIN1);
Ultrasonic ultrasonic_esquerda(TRIGGER_PIN2, ECHO_PIN2);
Ultrasonic ultrasonic_direita(TRIGGER_PIN3, ECHO_PIN3);

unsigned long int tempoAnterior = 0;

float distancia_frente();
float distancia_direita();                 
float distancia_esquerda();

void robo_frente();
void robo_esquerda();
void robo_direita();
void robo_parado(); 

void decisao_esquerda();
void decisao_direita();

void ligar_uvc();

void setup() 
{
  pinMode(IN1,OUTPUT);              
  pinMode(IN2,OUTPUT);              
  pinMode(IN3,OUTPUT);             
  pinMode(IN4,OUTPUT);              
  pinMode(ENA,OUTPUT);              
  pinMode(ENB,OUTPUT);              
  analogWrite(ENA,120);             
  analogWrite(ENB,120); 
  pinMode(16, OUTPUT); // led
  delay(1000); 
} //end setup


void loop()                         
{
  while(1)
  {
    if(millis() - tempoAnterior >= 3000)
    {
       tempoAnterior = millis();
       robo_parado();
       ligar_uvc();
    }
    
    else
    {
      robo_frente();                    
      float dist_cm_frente = distancia_frente();
      float dist_cm_direita = distancia_direita();    
      float dist_cm_esquerda = distancia_esquerda();         
    
      if(dist_cm_frente <= 70) // caso a distancia medida na frente for menor que 70cm                
      {
         if(dist_cm_direita > dist_cm_esquerda) { decisao_direita(); } // caso a distancia medida na direita for maior que a esquerda o robo irá para a direita
         if(dist_cm_direita < dist_cm_esquerda) { decisao_esquerda();} // caso a distancia medida na direita for menor que a esquerda o robo irá para a a esquerda
         if(dist_cm_direita == dist_cm_esquerda){ decisao_esquerda();} // caso as duas medidas forem iguais o robo irá para a esquerda. ESSA DECISÃO É SÓ PARA EVITAR QUE O ROBO FIQUE CONFUSO
      } 
    }
    delay(100);
  }                          
} 


float distancia_frente()                   
{
  float cmMsec;
  long microsec = ultrasonic_frente.timing();
  cmMsec = ultrasonic_frente.convert(microsec, Ultrasonic::CM);
  return(cmMsec);                   
  delay(10);
} 


float distancia_direita()                   
{
  float cmMsec;
  long microsec = ultrasonic_direita.timing();
  cmMsec = ultrasonic_direita.convert(microsec, Ultrasonic::CM);
  return(cmMsec);                   
  delay(10);
}


float distancia_esquerda()                   
{
  float cmMsec;
  long microsec = ultrasonic_esquerda.timing();
  cmMsec = ultrasonic_esquerda.convert(microsec, Ultrasonic::CM);
  return(cmMsec);                   
  delay(10);
}

void robo_frente()                  
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
} 

void robo_esquerda()             
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH); 
} 

void robo_direita()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void robo_parado()                  
{

  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);   
} 

void decisao_esquerda()                      
{
  robo_parado();
  delay(500);
  robo_esquerda();
  delay(400);                       
  robo_parado();
  delay(500);
}

void decisao_direita()                      
{
  robo_parado();
  delay(500);
  robo_direita();
  delay(400);                       
  robo_parado();
  delay(500);
}

void ligar_uvc()
{
  digitalWrite(16, HIGH);
  delay(3000);
  digitalWrite(16, LOW);  
}

