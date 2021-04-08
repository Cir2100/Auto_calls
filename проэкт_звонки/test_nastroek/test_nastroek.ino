#include <EEPROM.h>
void setup() {
   EEPROM.write(14, 20); //hour
   EEPROM.write(15, 19); //hour

}

void loop() {
  // put your main code here, to run repeatedly:

}
