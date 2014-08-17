#include <stdio.h>
#include "OutStream.h"
#include "CException.h"
#include "ErrorCode.h"
#include <malloc.h>

int temp = 0;

OutStream *openOutStream(char *fileName, char *openMethod){
  OutStream *outStream = calloc(1, sizeof(OutStream));

  outStream->file = fopen(fileName, openMethod);
  
  outStream->filename = fileName;
  outStream->currentbyte = 0;
  outStream->bitIndex = 0;
  return outStream;
}

void streamWriteBits(OutStream *out, int bitsToWrite, int bitSize){
  int i, loop, bit =0, carryOver;
  
  temp = bitsToWrite;
  carryOver = bitSize - 8;
  temp = bitsToWrite >> carryOver;
  
  out->currentbyte = out->currentbyte | temp;
  
  for(i = 0 ; i < 8 ; i++){
    out->bitIndex++;
    bit = bit << 1;
    bit = bit | ((out->currentbyte >> 7-i)&0x01);
    
    if(out->bitIndex == 7)
      out->bitIndex = 0;
  }
  
  out->currentbyte = bitsToWrite << (8-carryOver);
 
  fputc(bit, out->file);

}

void closeOutStream(OutStream *out){
  fclose(out->file);

}



