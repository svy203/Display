#include "main.h"


int main() {
      Serial.begin(9600);
      count truck;
      truck.initalization(3,0);
      truck.Massa(5090,7430,7680,0,0,0);
      truck.Massa2(5615,6910,8370,0,0,0);
      truck.Voltage(1.23,1.42,1.59,0,0,0);
      while(true) truck.test();
}    