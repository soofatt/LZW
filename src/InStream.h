#ifndef InStream_H
#define InStream_H
#include <stdio.h>
#include "Utils.h"

typedef struct InStream{
  FILE *file;
  char *filename;
  uint8 currentbyte;
  // uint8 length;
  // uint32 size;
  // uint32 byteIndex;
  uint32 bitIndex;
}InStream;

int streamReadBits(InStream *in, int bitSize);
int streamReadBit(char byteToRead);
InStream *openInStream(char *fileName, char *openMethod);
void closeInStream(InStream *in);
#endif // InStream_H
