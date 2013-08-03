#include "AsciiConverter.h"

char * Convert(char * data, int len){
  char * chArr = new char[len];

  for(int i = 0; i < len; i ++){
    chArr[i] = ToAscii(data[i]);
  }
  return chArr;
}

char ToAscii(char v){
  int n = v;
  if(n < 0){
    n += 256;
  }

  //const char * chars = " ,.-:/+osyhdm#NM";
  //const char * chars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
  //const char * chars = "tfjrxnuvcwqkah%@$8BXYUJCL";

  const char * chars = " '`,.-:;_~\"^i!l1\\/|I?([{+<o*syhdmtjrxnuvcwqkah%@$8BXYUJLCOQ0#NMW";

  return chars[n / 8];
}
