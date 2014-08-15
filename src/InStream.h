#ifndef InStream_H
#define InStream_H
#include <stdio.h>
#include "Utils.h"

typedef struct InStream{
  FILE *file;
  char *filename;
  char *buffer;
  // uint8 length;
  // uint32 size;
  // uint32 byteIndex;
  // uint32 bitIndex;
}InStream;

int streamReadBits(InStream *in, int bitSize);
InStream *openInStream(char *fileName, char *openMethod);
#endif // InStream_H
