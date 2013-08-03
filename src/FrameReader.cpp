#include "FrameReader.h"

#include "AsciiConverter.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef>

using namespace std;

FrameReader::FrameReader(const char * path){
  ifstream inFile;

  inFile.open(path, ios::in|ios::binary|ios::ate);      
  inFile.seekg(0, ios::end);
  length = inFile.tellg();
  inFile.seekg(0, ios::beg);

  data = new char[length];
  inFile.read(data, length);

  delay = CharArrToInt(data, 0);
  width = CharArrToInt(data, 4);
  height = CharArrToInt(data, 8);
  frameCount = CharArrToInt(data, 12);
  count = 0;
}

FrameReader::FrameReader(const FrameReader& copy){
  length = copy.length;
  delay = copy.delay;
  width = copy.width;
  height = copy.height;
  frameCount = copy.frameCount;
  count = copy.count;
  data = new char[length];
  for(int i = 0; i < length; i ++){
    data[i] = copy.data[i];
  }
}

FrameReader& FrameReader::operator=(const FrameReader& copy){
  if(this != &copy){
    length = copy.length;
    delay = copy.delay;
    width = copy.width;
    height = copy.height;
    frameCount = copy.frameCount;
    count = copy.count;
    char * newData = new char[length];
    for(int i = 0; i < length; i ++){
      newData[i] = copy.data[i];
    }
    
    delete[] data;
    data = newData;
  }

  return *this;
}

FrameReader::~FrameReader(){
  delete[] data;
}

int FrameReader::Delay(){
  return delay;
}

int FrameReader::FrameWidth(){
  return width;
}

int FrameReader::FrameHeight(){
  return height;
}

char * FrameReader::NextFrame(){
  if(count >= frameCount){
    return NULL;
  }

  int offset = 16 + (count * width * height);
  char * frame = new char[width * height];

  for(int i = 0; i < width * height; i ++){
    frame[i] = data[offset + i];
  }

  count ++;

  return Convert(frame, width * height);
}

int FrameReader::CharArrToInt(char * data, int offset){
  int c = data[offset];
  c = (c << 8) | data[offset + 1];
  c = (c << 8) | data[offset + 2];
  c = (c << 8) | data[offset + 3];

  return c;
}
