#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "Canvas.h"
#include "Renderable.h"

using namespace std;

class Animation{

public:
  Animation(int sleep_time) : sleep_time(sleep_time){ }

  void RunAnimate(Canvas& canvas);

  void RegisterRenderable(Renderable * renderable);
  void UnregisterRenderable(Renderable * renderable);

private:
  vector<Renderable *> renderables;
  int sleep_time;
};


#endif
