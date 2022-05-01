/*

   gon_data_logger.cpp
   Autor: Cristiano Gonzaga
   Abril de 2022


*/

#include "Arduino.h"
#include "gon_data_logger.h"
#include <SPI.h>
#include <SD.h>

void DataLogger::config(int pin, unsigned long maxSizePer){
  _maxSizePer = maxSizePer;
  _pin = pin;
  _basePathFiles = "/LOGS/";
  if (!SD.begin(_pin)) {
      Serial.println("Inicializaçåo falhou!");
      while (1);
   }
  listFiles();
  _nameCurrentFile = _lastFileFolder;
  
}

void DataLogger::gravar(String texto){
  _getNameFileCurrent();
  _currentFile = SD.open(_basePathFiles+_nameCurrentFile, FILE_WRITE);
    // if the file opened okay, write to it:
  if (_currentFile) {
    _currentFile.println(texto);
    // close the file:
    _currentFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("Ocorreu um erro ao abrir o arquivo");
  }
}

void DataLogger::ler(){
      // re-open the file for reading:
  _currentFile = SD.open(_basePathFiles+_nameCurrentFile);
  if (_currentFile) {
    Serial.println(_basePathFiles+_nameCurrentFile);

    // read from the file until there's nothing else in it:
    while (_currentFile.available()) {
      Serial.write(_currentFile.read());
    }
    // close the file:
    _currentFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening arquivo");
  }
}

unsigned long DataLogger::size(){
  unsigned long size = 0;
  _currentFile = SD.open(_nameCurrentFile);
  size = _currentFile.size();
  _currentFile.close();
 return size;
}

void DataLogger::listFiles(){
  _currentFile = SD.open(_basePathFiles);
  _printDirectory(_currentFile, 0);
}

void DataLogger::_printDirectory(File dir, int numTabs) {
  _lastFileFolder = "";
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    _lastFileFolder = entry.name();
    _lastFileSize = entry.size();
    Serial.print(entry.name());

    if (entry.isDirectory()) {
      Serial.println("/");
      _printDirectory(entry, numTabs + 1);
    } else {

      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }

    entry.close();

  }
}

String DataLogger::_getNameFileCurrent(){
  if(_lastFileFolder == ""){
    _nameCurrentFile = "1.txt";
  }
  if (_maxSizePer < _lastFileSize){
    int piceName = _lastFileFolder.substring(0, _lastFileFolder.indexOf(".")).toInt();
     piceName ++;
    _nameCurrentFile = String(piceName)+".txt";
  }
  return _nameCurrentFile;
}