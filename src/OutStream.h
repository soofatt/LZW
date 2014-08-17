#ifndef OutStream_H
#define OutStream_H
#include <stdio.h>
#include "Utils.h"

typedef struct{
  FILE *file;
  char *filename;
  uint8 currentbyte;
  // uint8 length;
  // uint32 size;
  // uint32 byteIndex;
  uint32 bitIndex;
}OutStream;

void streamWriteBits(OutStream *out, int bitsToWrite, int bitSize);
OutStream *openOutStream(char *fileName, char *openMethod);
void streamFlush(OutStream *out);
#endif // OutStream_H

