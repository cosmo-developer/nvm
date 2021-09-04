#ifndef BYTE_CODE_H
#define BYTE_CODE_H
#define OM  0
#define IM  1 
#define WD  2 
#define RD  3 
#define WA  4
#define RA  5
#define RST 6 //reset pc
#define PSH 7 // push on stack byte
#define POP 8 //pop
#define JLT 9 //jump if less than
#define JGT 10 
#define JGE 11
#define JLE 12
#define JMP 13
#define INC 14
#define DEC 15
#define FON 16 //Fan on 
#define FOF 17 // Fan off
#define CMP 28 // compare
#define SHTD 29 //shutdown system
#define EQAL 30
#endif