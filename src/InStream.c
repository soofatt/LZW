#include <stdio.h>
#include "InStream.h"
#include "CException.h"
#include "ErrorCode.h"
#include <malloc.h>

/*
* to open file to read 
* 
* input: -  fileName: name of file
*        -openMethod: to read, r
*/
InStream *openInStream(char *fileName, char *openMethod){
  InStream *inStream = calloc(1, sizeof(InStream));

  inStream->file = fopen(fileName, openMethod);
  
  if(inStream->file == NULL)
    Throw(ERR_CANNOT_OPEN_FILE);
  
  inStream->filename = fileName;
  inStream->currentbyte = 0;
  inStream->bitIndex = 0;
  return inStream;
}

/*
* to read bits from file
*
* input: -     in: InStream struct pointer
*        -bitSize: number of bits to read
*
* output: -    -1: to indicate end of file
          -output: the bits to read
*/
int streamReadBits(InStream *in, int bitSize){
  int input, output = 0, i;
  unsigned char byteToRead, temp;
  
  input = fgetc(in->file);
  byteToRead = input;
  
  if(input == EOF){
    in->byteIndex = -1;
    return -1;
  }
  
  for(i = 0 ; i < 8 ; i++){
    output = output << 1;
    temp  = streamReadBit(byteToRead);
    output = output | temp;
    byteToRead = byteToRead << 1;
  }
  
  return output;

}

int streamReadBit(char byteToRead){
  int bit=0, mask = 0x80;
  
  bit = (byteToRead & mask) >> 7;
  
  return bit;
}

void closeInStream(InStream *in){
  fclose(in->file);
  free(in);
}
