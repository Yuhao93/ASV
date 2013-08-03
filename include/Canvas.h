#ifndef CANVAS_H
#define CANVAS_H

#include <string>

class Canvas{
public:
  Canvas();
  
  // Big Three
  Canvas(const Canvas& copy);
  Canvas& operator=(const Canvas& copy);
  ~Canvas();

  // Clear Screen
  void Clear();

  // Draw the screen
  void Draw(char c, int x, int y);

  // Draw the screen
  void DrawAndUpdate(const char * str);

  // Update
  void Update();

  // Get Width
  int Width();

  // Get Height
  int Height();

private:
  char * canvas;
  int width;
  int height;
};

#endif
