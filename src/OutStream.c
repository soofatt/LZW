#include <stdio.h>
#include "OutStream.h"
#include "CException.h"
#include "ErrorCode.h"
#include <malloc.h>

OutStream *openOutStream(char *fileName, char *openMethod){
  OutStream *outStream = calloc(1, sizeof(OutStream));

  outStream->file = fopen(fileName, openMethod);
  
  outStream->filename = fileName;
  outStream->currentbyte = 0;
  outStream->bitIndex = 0;
  return outStream;
}

void streamWriteBits(OutStream *out, int bitsToWrite, int bitSize){
  int i,temp = 0, bit =0;
  
  
  temp = bitsToWrite;
  for(i = 7 ; i > -1 ; i--){
    bit = bit << 1;
    bit = bit | ((temp >> i)&0x01);
    
  }
  fputc(bit, out->file);

}

void closeOutStream(OutStream *out){
  fclose(out->file);

}