#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Canvas.h"

class Renderable{
public:
  virtual void Draw(Canvas& canvas) = 0;
  virtual void Update() = 0;
};

#endif
