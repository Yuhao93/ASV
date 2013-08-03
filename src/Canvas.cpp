#include "Canvas.h"

#include "ncurses.h"

Canvas::Canvas() {
  initscr();
  getmaxyx(stdscr, height, width);
  canvas = new char[width * height];
}
  
Canvas::Canvas(const Canvas& copy){
  width = copy.width;
  height = copy.height;
  canvas = new char[width * height];
  for(int i = 0; i < width * height; i ++){
    canvas[i] = copy.canvas[i];
  }
}

Canvas& Canvas::operator=(const Canvas& copy){
  if(this != &copy){
    width = copy.width;
    height = copy.height;
    char * newCanvas = new char[width * height];
    for(int i = 0; i < width * height; i ++){
      newCanvas[i] = copy.canvas[i];
    }

    delete[] canvas;
    canvas = newCanvas;
  }

  return *this;
}

Canvas::~Canvas(){
  endwin();
  delete[] canvas;
}

void Canvas::Clear(){
  for(int i = 0; i < width * height; i ++){
    canvas[i] = ' ';
  }
}

void Canvas::Draw(char c, int x, int y){
  if(x >= 0 && x < width && y >= 0 && y < height){
    canvas[y * width + x] = c;
  }
}

void Canvas::DrawAndUpdate(const char * str){
  move(0, 0);
  printw(str);
  refresh();
}

void Canvas::Update(){
  for(int y = 0; y < height; y ++){
    for(int x = 0; x < width; x ++){
      mvaddch(y, x, canvas[y * width + x]);
    }
  }
  refresh();
}

int Canvas::Width(){
  return width;
}

int Canvas::Height(){
  return height;
}
