#include "InStream.h"
#include "OutStream.h"
#include "Dictionary.h"
#include "LZWEncoder.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

char currentByte;

/*
* dictIndex and marker is used to determine if bitsToWrite should increase to x bits
* eg. when dictionary index > 255, bitsToWrite should be 9 bits
*
* the code utilizes byteIndex to stop encoding
*
* input: -        in: InStream pointer
*        -       out: OutStream pointer
*        -dictionary: the dictionary
*/
void lzwEncoder(InStream *in, Dictionary *dictionary, OutStream *out){
  int dictIndex = 256, bitSize = 8, marker = 256, result;
  char *code;
  dictionaryEntryInitializer(dictionary);

  while(1){
    code = dictionaryFindLongestMatchingEntry(in, dictionary)->code;

    /*
    * append in->currentByte to the marked code passed in from dictionaryFindLongestMatchingEntry then add it into dictionary
    * utilizes getIntFromChar to dig through the dictionary to obtain the correct index to be written
    */
    if(dictionaryAdd(dictionary, codeNewAndAppend(code, currentByte), dictIndex) == 1){

      result = getIntFromChar(dictionary, code);
      streamWriteBits(out, result, bitSize);

      //condition to add bitSize
      if(dictIndex == marker){
        marker = marker * 2;
        bitSize++;
      }

     //end
     if(in->byteIndex == -1){
        streamWriteBits(out, 0, bitSize);
        break;
      }

      dictIndex++;
    }

  }
}

/*
* to obtain an integer from character and to locate strings from dictionary entry to return it's index
*
* input : -dict: the dictionary
*         -code: the code to be located in the dictionary
*
* output: -byte: the integer form of the character
*         -   i: the dictionary index that contains the entry that matches the input code
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
