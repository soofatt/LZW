#include "LZWEncoder.h"
#include <string.h>
#include "Dictionary.h"
#include <stdio.h>
#include <malloc.h>
#include "InStream.h"
#include "OutStream.h"

void LZWEncoder(InStream *in, Dictionary *dictionary, OutStream *out){
  int i, byte;
  
  for(i = 1 ; i < 10 ; i++){
    
    
    if(dictionaryFindLongestMatchingEntry(in, dictionary)->code == dictionary->entries[i].code){
    
    }
    
    else if(dictionaryAdd(dictionary, dictionaryFindLongestMatchingEntry(in, dictionary)->code, i) == 1){
      streamWriteBits(out, (int)dictionary->entries[i].code ,8);
    }
    else
      codeNewAndAppend(dictionary->entries[i].code, byte);

  }
}

/*
* abcdabc
* aaaaaaa
*
*/