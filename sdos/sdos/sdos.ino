#include <byte_code.h>
#include <nvm.h>

void setup(){
  NVMCPU::Init();
  unsigned char code[]={
    PSH,0,PSH,13,
    WD,SHTD
  };
  NVMCPU::InsertCode(code,sizeof(code));
}

void loop(){
  NVMCPU::Execute();
}
