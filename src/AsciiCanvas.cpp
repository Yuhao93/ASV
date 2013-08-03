#include "AsciiCanvas.h"

AsciiCanvas::AsciiCanvas(const AsciiCanvas& copy) : w(copy.w), h(copy.h), fr(copy.fr){
  frame = new char[w * h];
  for(int i = 0; i < w * h; i ++){
    frame[i] = copy.frame[i];
  } 
}

AsciiCanvas& AsciiCanvas::operator=(const AsciiCanvas& copy){
  if(this != &copy){
    w = copy.w;
    h = copy.h;
    fr = copy.fr;
    char * newFrame = new char[w * h];
    for(int i = 0; i < w * h; i ++){
      newFrame[i] = copy.frame[i];
    }
    delete[] frame;
    frame = newFrame;
  }

  return *this;
}

AsciiCanvas::~AsciiCanvas(){
  delete[] frame;
}

void AsciiCanvas::Draw(Canvas& canvas){
/*  for(int x = 0; x < w; x ++){
    for(int y = 0; y < h; y ++){
      if(frame != NULL){
        canvas.Draw(frame[y * w + x], x, y);
      }
    }
  }

  */if(frame != NULL){
    canvas.DrawAndUpdate(frame);
  }
}

void AsciiCanvas::Update(){
  delete[] frame;
  frame = fr.NextFrame();
}
