#include "nvm.h"
#include "Arduino.h"
int NVMCPU::pc=128;
int NVMCPU::sp=-1;
unsigned char* NVMCPU::ram=new unsigned char[MAX_CODE+MAX_STACK];
void NVMCPU::Init(){
    
    Serial.begin(9500);
    pinMode(FAN_PIN,OUTPUT);
    pinMode(BUILTIN_LED,OUTPUT);
    pinMode(POWER_CONTROLLER_PIN,OUTPUT);
    digitalWrite(POWER_CONTROLLER_PIN,HIGH);//activate device
    Serial.println("Initializing memory of size 384 Byte");
    digitalWrite(BUILTIN_LED,HIGH);
    for (int i=0;i<MAX_STACK+MAX_CODE;i++){
        NVMCPU::ram[i]='\0';
    }
    delay(2000);
    digitalWrite(BUILTIN_LED,LOW);
    Serial.println("Initializing done! Starting Fan!...");

    for (int i=0;i<5;i++){
        digitalWrite(BUILTIN_LED,HIGH);
        delay(100);
        digitalWrite(BUILTIN_LED,LOW);
        delay(100);
    }
    digitalWrite(FAN_PIN,HIGH);
    digitalWrite(BUILTIN_LED,HIGH);
    delay(100);
    Serial.println("Fan Started!...");
    delay(100);
}

void NVMCPU::Push(unsigned char data){
    if (sp==MAX_STACK){
        Serial.println("Please reset hardware stack overflow!..........");
        Serial.println("Restarting nano virtual machine!....");
        Serial.println("Reseting SP to -1!");
        Serial.println("Restarting Program of VM....");
        Serial.println("Setting pc to 128!.. at starting....");
        int x=0;
        while (x<30){
            digitalWrite(BUILTIN_LED,HIGH);
            delay(50);
            digitalWrite(BUILTIN_LED,LOW);
            delay(50);
            x++;
        }
        sp=-1;
        pc=128;
    }
    sp++;
    ram[sp]=data;
}

unsigned char NVMCPU::Pop(){
    if (sp!=-1){
        unsigned char temp=ram[sp];
        sp--;
        return temp;
    }
    return '\0';
}

void NVMCPU::Error(){//In situation of critical error in this situation we need to start hardware totally
    while (true){
        digitalWrite(BUILTIN_LED,HIGH);
        delay(200);
        digitalWrite(BUILTIN_LED,LOW);
        delay(200);
    }
}


void NVMCPU::Shutdown(){
    digitalWrite(FAN_PIN,LOW);
    delay(1000);
    Serial.println("Fan off now shuting down hardwares");
    delay(1000);
    digitalWrite(POWER_CONTROLLER_PIN,LOW);
}

void NVMCPU::InsertCode(unsigned char* code,int size){
    if (size>MAX_CODE){
        Serial.println("Code is more than 256 Bytes");
        return;       
    }
    for (int i=0;i<size;i++){
        ram[pc+i]=code[i];       
    }
}


void NVMCPU::Execute(){
    pc=128;
    while (pc<MAX_CODE){
        switch(ram[pc++]){
            case OM:{
                pinMode(Pop(),OUTPUT);
                break;
            }
            case IM:{
                pinMode(Pop(),INPUT);
                break;
            }
            case WD:{
                digitalWrite(Pop(),Pop()==1?HIGH:LOW);
                break;
            }
            case RD:{
                Push(digitalRead(Pop()));
                break;
            }
            case PSH:{
                Push(ram[pc++]);
                break;
            }
            case POP:{
                Pop();
                break;
            }
            case JLT:{
                if (int(Pop())<0){
                    pc=ram[pc];
                }else{
                    pc++;
                }
                break;
            }
            case JGT:{
                if (int(Pop())>0){
                    pc=ram[pc];
                }else{
                    pc++;
                }
                break;
            }
            case JLE:{
                if (int(Pop())<=0){
                    pc=ram[pc];
                }else{
                    pc++;
                }
                break;
            }
            case JGE:{
                if (int(Pop())>=0){
                    pc=ram[pc];
                }else{
                    pc++;
                }
                break;
            }
            case JMP:{
                pc=ram[pc++];
                break;
            }
            case EQAL:{
                if (int(Pop())==0){
                    pc=ram[pc];
                }else{
                    pc++;
                }
                break;
            }

            case INC:{
                Push(Pop()+1);
                break;
            }
            case DEC:{
                Push(Pop()-1);
                break;
            }
            case CMP:{
                Push(Pop()-Pop());
                break;
            }
            case FON:{
                digitalWrite(FAN_PIN,HIGH);
                break;
            }
            case FOF:{
                digitalWrite(FAN_PIN,LOW);
                break;
            }
            case SHTD:{
                Shutdown();
                break;
            }
        }
    }
}