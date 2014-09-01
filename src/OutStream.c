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
* streamWriteBits will always write 12 bits into file
*
* input: -       *out: pointer to OutStream struct
*        -    bitSize: number of bits to be written
*        -bitsToWrite: bits to be written
*/
void streamWriteBits(OutStream *out, int bitsToWrite, int bitSize){
  int i, bit = 0, temp = 0;
  
  //to remove 0xf from -128
  if(bitsToWrite < 256){
    bitsToWrite = bitsToWrite & 0xf0ff;
  }
  
  //if bit size is 8
  if(bitSize == 8){
    out->currentByte = bitsToWrite;
    fputc(out->currentByte, out->file);
  }
  //if bit size is 12
  else{
    if(out->size == 0){
      temp = bitsToWrite >> 4;
      temp = out->currentByte | temp;
    }
    else{
      temp = bitsToWrite >> 8;
      temp = out->currentByte | temp;
    }

    for(i = 0 ; i < 8 ; i++){

      out->currentByte = out->currentByte << 1;
      bit = (temp >> 7-i)&0x01;
      streamWriteBit(out, bit);

    }
    fputc(out->currentByte, out->file);
    
    if(out->size == 0){
      out->currentByte = bitsToWrite << 4;
      out->size = 1;
    }
    else{
      out->currentByte = bitsToWrite;
      streamFlush(out);
      out->currentByte = bitsToWrite << 8;
      out->size = 0;
    }

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


