#ifndef FRAMEREADER_H
#define FRAMEREADER_H

#include <cstddef>

class FrameReader{
public:
  FrameReader(const char * path);
  FrameReader(const FrameReader& copy);
  FrameReader& operator=(const FrameReader& copy);
  ~FrameReader();

  int Delay();
  int FrameWidth();
  int FrameHeight();

  char * NextFrame();

private:
  char * data;
  int delay;
  int count;
  int frameCount;
  int width;
  int height;
  size_t length;

  int CharArrToInt(char * data, int offset);
};

#endif
