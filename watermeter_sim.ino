#include <user_interface.h>;//Biblioteca necessaria para acessar os Timers
#include <time.h>
#include <stdlib.h>
#define output D3 //LED_BUILTIN

int timerCount=0,r=0,state=0,outPin=0,trashCount=0,timerFlag=0,setpoint=50;

os_timer_t tmr0;//Cria o Timer. Maximo de 7 Timers.

void setup() {
  Serial.begin(115500);
  //srand(time(NULL));   // Initialization, should only be called once.
  pinMode(output,OUTPUT);
  os_timer_setfn(&tmr0, timer, NULL); //timer, subrotina, null
  os_timer_arm(&tmr0, 10, true); //timer, tempo em ms (entre 1ms e 2s), loop=true 

}

void loop() {
  if(timerFlag==1){
    if (timerCount==1){
      r = 400 + rand() % 200;   //between 4s and 6s
      state=!state;
      outPin=state;
      digitalWrite(output,outPin);
      Serial.println(timerCount);
    }
    if (timerCount>1 && timerCount<=r){
      digitalWrite(output,outPin);
      Serial.println(timerCount);
    }
    if(timerCount==r)
      setpoint=rand()%75+25;
    if(timerCount>r){
      Serial.println(timerCount);
      if (trashCount<setpoint){
        outPin=rand()%2;
        digitalWrite(output,outPin);
        Serial.println(outPin);
        trashCount++;
      }
      if(trashCount>=setpoint){
        timerCount=0;
        trashCount=0;
        setpoint=50;
      }
    }
    timerFlag=0;
  }
}

void timer(void*z){ //software timer de 1ms - Conta o relógio internalo
  timerCount++;
  timerFlag=1;
}
