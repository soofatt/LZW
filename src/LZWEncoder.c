#include "InStream.h"
#include "OutStream.h"
#include "Dictionary.h"
#include "LZWEncoder.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

void lzwEncoder(InStream *in, Dictionary *dictionary, OutStream *out){
  int i, dictIndex = 256, bitsToWrite = 8, marker = 256;
  char *code;
  
  dictionaryEntryInitializer(dictionary);
  
  for(i = 0 ; ; i++){
  
    code = dictionaryFindLongestMatchingEntry(in, dictionary)->code;

    if(dictionaryAdd(dictionary, codeNewAndAppend(code, streamReadBits(in, 8)), dictIndex) == 1){
      streamWriteBits(out, getIntFromChar(dictionary, code), bitsToWrite);
      
      //condition to add bitsToWrite
      if(dictIndex == marker){ 
        marker = marker * 2;
        bitsToWrite++;
      }
      
      dictIndex++;
    }
  }
}

/*
* to obtain an integer from character and to locate strings from dictionary entry to return it's index
* return ASCII in integer form
* return an index of a dictionary entry
*/
int getIntFromChar(Dictionary *dict, char *code){
  int byte, i;
  if(strlen(code) == 1){
    byte = code[0];
    return byte;
  }
  
  else
    for(i = 256 ; dict->length > i ; i++){
      if(strcmp(code, dict->entries[i].code) == 0){
        return i;
      }
    }
}
