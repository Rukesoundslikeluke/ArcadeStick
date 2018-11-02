#ifndef IR_H
#define IR_H
#include <IRremote.h>

#define POWER 0xFFA25D
#define VOLUP 0xFF629D
#define FUNC 0xFFE21D
#define SKIPBACK 0xFF22DD
#define PLAY 0xFF02FD
#define SKIPFORWARD 0xFFC23D
#define DOWN 0xFFE01F
#define VOLDOWN 0xFFA857
#define UP 0xFF906F
#define N0 0xFF6897
#define EQ 0xFF9867
#define N1 0xFF30CF
#define N2 0xFF18E7
#define N3 0xFF7A85
#define N4 0xFF10EF
#define N5 0xFF38C7
#define N6 0xFF5AA5
#define N7 0xFF42BD
#define N8 0xFF4AB5
#define N9 0xFF52AD

#define RECV_PIN 8

void startIR(IRrecv irrecv){
  irrecv.enableIRIn();
  irrecv.blink13(true);
}



#endif