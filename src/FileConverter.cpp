#include "FileConverter.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;

void ConvertFile(const char * src, const char * dest, const char * defW, const char * defH){
  vector<unsigned char> frameBuffer;
  VideoCapture cap(src);

  if(!cap.isOpened()){
    return;
  }

  int scrWidth;
  int scrHeight;

  int w = 0;
  int h = 0;
  int frameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);

  initscr();
  getmaxyx(stdscr, scrHeight, scrWidth);
  endwin();

  for(int i = 0; i < frameCount; i ++){
    Mat frame;
    Mat newFrame;

    if(!cap.grab()){
      break;
    }

    if(!cap.retrieve(frame, 0)){
      break;
    }

    // Convert frame to grayscale
    cvtColor(frame, newFrame, CV_BGR2GRAY);

    if(!w || !h){
      // Scale down to terminal size
      if(defW != NULL && defH != NULL){
        string strW(defW);
        string strH(defH);
        scrWidth = stoi(strW);
        scrHeight = stoi(strH);
      }

      Size size = newFrame.size();
      double wRatio = (double)scrWidth / size.width;
      double hRatio = (double)scrHeight / size.height;
      double ratio = wRatio > hRatio ? hRatio : wRatio;

      w = (ratio == wRatio) ? scrWidth : ratio * size.width;
      h = (ratio == hRatio) ? scrHeight : ratio * size.height;
    }

    Mat dst(h, w, newFrame.type());
    resize(newFrame, dst, dst.size(), 0, 0, INTER_LINEAR);
    
    for(int y = 0; y < h; y ++){
      for(int x = 0; x < w; x ++){
        frameBuffer.push_back(dst.at<unsigned char>(y, x));
        frameBuffer.push_back(dst.at<unsigned char>(y, x));
      }
      for(int i = 0; i < scrWidth - (2 * w); i ++){
        frameBuffer.push_back(0);
      }
    }

    int numStar = 50 * i / frameCount;

    cout << '\r' << "[";
    for(int i = 0; i < 50; i ++){
      if(i < numStar){
        cout << '*';
      }else{
        cout << ' ';
      }
    }
    cout << "] " << 100 * i / frameCount << "%";
  }

  char * fileContents = new char[frameBuffer.size() + 16];
  char * delay = ToArr((int)(1000000 / cap.get(CV_CAP_PROP_FPS)));
  char * width = ToArr(scrWidth);
  char * height = ToArr(h);
  char * num = ToArr(frameBuffer.size() / (scrWidth * h));

  Copy(fileContents, delay, 0);
  Copy(fileContents, width, 4);
  Copy(fileContents, height, 8);
  Copy(fileContents, num, 12);

  delete[] delay;
  delete[] width;
  delete[] height;
  delete[] num;

  for(int i = 0; i < frameBuffer.size(); i ++){
    fileContents[16 + i] = (char)frameBuffer[i];
  }

  ofstream outBuff(dest, std::ios::binary|std::ios::out);
  outBuff.write(fileContents, frameBuffer.size() + 16);
  outBuff.close();
  cout << "\ndone." << endl;
}

char * ToArr(int in){
  char * arr = new char[4];
  arr[0] = in >> (8 * 3);
  arr[1] = in >> (8 * 2);
  arr[2] = in >> (8 * 1);
  arr[3] = in;
  return arr;
}

void Copy(char * to, char * from, int offset){
  to[offset] = from[0];
  to[offset + 1] = from[1];
  to[offset + 2] = from[2];
  to[offset + 3] = from[3];
}
