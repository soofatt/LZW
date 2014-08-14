#include "InStream.h"
#include "OutStream.h"
#include "Dictionary.h"
#include "LZWEncoder.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

void lzwEncoder(InStream *in, Dictionary *dictionary, OutStream *out){
  int i, dictIndex = 256, k;
  char *code;
  
  for(i = 0 ; i < 10 ; i++){
    
    code = dictionaryFindLongestMatchingEntry(in, dictionary)->code;
    dictionaryAdd(dictionary, codeNewAndAppend(code, streamReadBits(in, 8)), dictIndex);
    dictIndex++;
    streamWriteBits(out, getIntFromChar(dictionary, code), 8);
    
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
