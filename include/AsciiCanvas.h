#ifndef ASCIICANVAS_H
#define ASCIICANVAS_H

#include "FrameReader.h"
#include "Renderable.h"

class AsciiCanvas : public Renderable{
public:
  AsciiCanvas(FrameReader& f) : fr(f), w(f.FrameWidth()), h(f.FrameHeight()), frame(NULL) { }

  AsciiCanvas(const AsciiCanvas& copy);
  AsciiCanvas& operator=(const AsciiCanvas& copy);
  ~AsciiCanvas();

  void Draw(Canvas& canvas);
  void Update();

private:
  int w;
  int h;
  char * frame;
  FrameReader fr;
};

#endif
