/*

   gon_data_logger.h
   Autor: Cristiano Gonzaga
   Abril de 2022


*/

#ifndef DataLogger_h
#define DataLogger_h

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

class DataLogger
{
   private:
	   File _currentFile;
      String _nameCurrentFile;
      void _printDirectory(File dir, int numTabs);
      int _pin;
      String _basePathFiles;
      String _lastFileFolder;
      unsigned long _lastFileSize;


   public:
       void config(int pin);
       void ler();
       void gravar();
       unsigned long size();
       unsigned long maxSizePer;
       void listFiles();
       
};

#endif