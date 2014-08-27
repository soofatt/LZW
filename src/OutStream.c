#include <stdio.h>
#include "OutStream.h"
#include "InStream.h"
#include "CException.h"
#include "ErrorCode.h"
#include <malloc.h>

/*
* open file for writing
*
* input: -openMethod: to write, w
*        -  fileName: name of file
*/
OutStream *openOutStream(char *fileName, char *openMethod){
  OutStream *outStream = calloc(1, sizeof(OutStream));

  outStream->file = fopen(fileName, openMethod);

  outStream->filename = fileName;
  outStream->currentByte = 0;
  outStream->bitIndex = 0;
  outStream->size = 0;
  return outStream;
}

/*
* to write bits into file
*
* streamWriteBits will always write 8 bits into file
* if bitsToWrite is more than 8 bits, it will be shifted >> to 8 bits, bit(s) that are shifted out will be saved
* these saved bits will be the starting bit(s) for the next byte
*
* input: -       *out: pointer to OutStream struct
*        -    bitSize: number of bits to be written
*        -bitsToWrite: bits to be written
*/
void streamWriteBits(OutStream *out, int bitsToWrite, int bitSize){
  int i, bit = 0, temp = 0;
  
  if(bitSize == 8){
    out->currentByte = bitsToWrite;
    fputc(out->currentByte, out->file);
  }
  else{
  if(out->size == 0){
    temp = bitsToWrite >> 4;
    temp = out->currentByte | temp;
  }
  else{
    temp = bitsToWrite >> 8;
    temp = out->currentByte | temp;
  }
  // printf("temp: %x\n", temp);
  // printf("bits: %x\n", bitsToWrite);
  // printf("out: %x\n", out->size);
  // printf("current before: %x\n", out->currentByte);

  for(i = 0 ; i < 8 ; i++){

    out->currentByte = out->currentByte << 1;
    bit = (temp >> 7-i)&0x01;
    streamWriteBit(out, bit);

  }
  fputc(out->currentByte, out->file);
  // printf("write: %x\n", out->currentByte);
  
  if(out->size == 0){
    out->currentByte = bitsToWrite << 4;
    out->size = 1;
  }
  else{
    out->currentByte = bitsToWrite;
    streamFlush(out);
    out->currentByte = bitsToWrite << 8;
      // printf("flush\n");
    out->size = 0;
  }
  // printf("current: %x\n", out->currentByte);
  }
}

void streamFlush(OutStream *out){
  fputc(out->currentByte, out->file);
  out->currentByte = 0;
}

void closeOutStream(OutStream *out){
  fclose(out->file);
  free(out);
}

void streamWriteBit(OutStream *out, int bit){
  out->currentByte = out->currentByte | bit;
  out->bitIndex++;
  if(out->bitIndex == 7)
    out->bitIndex = 0;
}


