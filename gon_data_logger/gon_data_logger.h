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
      unsigned long _maxSizePer;
      String _getNameFileCurrent();



   public:
       void config(int pin, unsigned long maxSizePer);
       void ler();
       void gravar(String texto);
       unsigned long size();
       void listFiles();
};

#endif