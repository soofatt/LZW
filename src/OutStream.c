#include <stdio.h>
#include "OutStream.h"
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
  outStream->currentbyte = 0;
  outStream->bitIndex = 0;
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
  int i, bit = 0, carryOver, temp = 0;
  
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

void streamFlush(OutStream *out){
  fputc(out->currentbyte, out->file);
}

void closeOutStream(OutStream *out){
  fclose(out->file);
  free(out);
}



