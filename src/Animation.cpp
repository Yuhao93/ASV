#include "Animation.h"

#include <unistd.h>

using namespace std;

void Animation::RunAnimate(Canvas& canvas){
  canvas.Clear();
  for(auto it = renderables.begin(); it != renderables.end(); ++it){
    Renderable * r = *it;
    r->Draw(canvas);
    r->Update();
  }
  canvas.Update();

  usleep(sleep_time);
}

void Animation::RegisterRenderable(Renderable * renderable){
  renderables.push_back(renderable);
}

void Animation::UnregisterRenderable(Renderable * renderable){
  vector<Renderable*>::iterator pos = renderables.end();
  for(auto it = renderables.begin(); it != renderables.end(); ++it){
    if(*it == renderable){
      pos = it;
      break;
    }
  }

  if(pos != renderables.end()){
    renderables.erase(pos);
  }
}
