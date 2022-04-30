#include <gon_data_logger.h>


DataLogger logger;


void setup() {
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  logger.config(4);
//  logger.gravar();
//  logger.ler();
//  logger.listFiles();

}

void loop() {

  // put your main code here, to run repeatedly:

}