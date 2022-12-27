#include <SoftwareSerial.h>
#include "DFRobot_SerialScreen771.h"

SoftwareSerial mySerial(16, 17); //RX, TX
DFRobot_SerialScreen771 screen(mySerial);

void setup() {
  Serial.begin(115200);
  mySerial.begin(19200);
  screen.begin();
  /*Set screen color*/
  /*eColorMode_t: eColorRed = red
                  eColorYellow = yellow
                  eColorGreen = green
                  eColorCyan = cyan
                  eColorBlue = blue
                  eColorPurple = purple
                  eColorWhite = white
                  eColorBlack = black
  */
  screen.setFullScreenColor(screen.eColorBlack);
}

void loop() {  
  DFRobot_SerialScreen771::eColorMode_t buf[] = {screen.eColorRed, screen.eColorYellow, screen.eColorGreen, screen.eColorCyan, screen.eColorBlue, screen.eColorPurple, screen.eColorWhite, screen.eColorBlack};

  //Black
  screen.setFullScreenColor(screen.eColorBlack);
  delay(50);

  //Green
  screen.setFullScreenColor(screen.eColorGreen);
  delay(5000);

  //White
  for(int i=0; i<4; i++){
    screen.setFullScreenColor(screen.eColorWhite);
    delay(500);
  }

  //Red
  screen.setFullScreenColor(screen.eColorRed);
  delay(5000);
}
