#ifndef FILECONVERTER_H
#define FILECONVERTER_H

#include <cstring>

void ConvertFile(const char * src, const char * dest, const char * defW = NULL, const char * defH = NULL);
char * ToArr(int in);
void Copy(char * to, char * from, int offset);
#endif
