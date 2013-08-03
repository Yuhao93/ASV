#include "FileConverter.h"
#include "FrameReader.h"
#include "AsciiCanvas.h"
#include "Animation.h"
#include "Canvas.h"
#include <cstring>
#include <sys/time.h>

int main(int argc, char * argv[]){
  if(argc < 2){
    return 1;
  }

  if (strcmp(argv[1], "convert") == 0) {
    if (argc > 5) {
      ConvertFile(argv[2], argv[3], argv[4], argv[5]);    
    } else {
      ConvertFile(argv[2], argv[3]);
    }
  } else if (strcmp(argv[1], "play") == 0) {
    FrameReader fr(argv[2]);

    Animation animation(fr.Delay());
    Canvas canvas;
    int time = fr.Delay();

    AsciiCanvas * asCanvas = new AsciiCanvas(fr);
    animation.RegisterRenderable(asCanvas);

    while(true) {
      int start = clock() * 1000000 / CLOCKS_PER_SEC;
      asCanvas->Draw(canvas);
      asCanvas->Update();
      int end = clock() * 1000000 / CLOCKS_PER_SEC;
      int diff = end - start;
      if (time > diff) {
        usleep(time - diff);
      }
      animation.RunAnimate(canvas);
    }
    return 0;
  }
}
