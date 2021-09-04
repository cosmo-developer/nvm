#ifndef NVM_H
#define NVM_H
#include "Arduino.h" //provide basic arduino hardware functionality
#include "byte_code.h"
#define MAX_STACK 128 //bytes
#define MAX_CODE  256 //bytes
#define FAN_PIN   12
#define BUILTIN_LED 13
#define POWER_CONTROLLER_PIN 8
class NVMCPU{
    public:
    static int pc;
    static int sp;
    static unsigned char* ram;
    public:
    static void Init();
    static void Push(unsigned char);
    static unsigned char Pop();
    static void InsertCode(unsigned char*,int size);
    static void Execute();
    static void Error(); //blinking led
    static void Shutdown();//shutdown hardware totally require external powersupply and controller at pin 8
};
#endif