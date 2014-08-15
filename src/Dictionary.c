#include "Dictionary.h"
#include "CException.h"
#include "LZWEncoder.h"
#include "ErrorCode.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "InStream.h"

char *codeNewAndAppend(char *oldCode, char codeToAppend){
  char *newCode = malloc((strlen(oldCode))+ 2);

  strcpy(newCode, oldCode);
  newCode[(strlen(oldCode))] = codeToAppend;
  newCode[(strlen(oldCode))+1] = '\0';

  return newCode;
}

Dictionary *dictionaryNew(int length){
  Dictionary *dictionary;

  dictionary = malloc(sizeof(Dictionary));
  dictionary->entries = calloc(length, sizeof(DictionaryEntry));
  dictionary->length = length;
  dictionary->size = 256;
  return dictionary;
}

void dictionaryDel(Dictionary *dict){
  int i;

  for(i =0 ; i < dict->length ; i++){
    if(dict->entries[i].code != NULL)
      free(dict->entries[i].code);
  }

  free(dict);
}

int dictionaryAdd(Dictionary *dict, char *code, int index){
  int availability =0;

  if(dict->length > index){
    dict->entries[index].code = code;
    dict->entries[index].length = strlen(code);
    availability = 1;
  }

  return availability;
}

DictionaryEntry *dictionaryFindLongestMatchingEntry(InStream *in, Dictionary *dictionary){
  int byte, firstByte, end;
  int index, markIndex, longestCode = 0, k = 0;

  /*
  * take in the first byte
  * save the first byte into firstByte
  * firstMarkIndex is to find the first entry for the dictionaryFindLongestMatchingEntry to start
  * destroy: markIndex
  */
  byte = streamReadBits(in, 8);
  firstByte = byte;
  markIndex = firstMarkIndex(dictionary, firstByte);

  //to loop through dictionary
  for(index = 0 ; dictionary->length > index ; index++){

    //ensure code is not null
    if(dictionary->entries[markIndex].code != NULL && dictionary->entries[index].code != NULL){

      //compare if marked code and current code is the same, if not go to the next entry
      if(isBlockSame(dictionary->entries[markIndex].code, dictionary->entries[index].code, longestCode) == 0){

        for(k ; dictionary->entries[index].length > k ; k++){

          /*
          * compare if current byte is the same with byte in entry, if it's the same mark current index as longest and code
          * if it's not the same return to entry
          * destroy: longest code & index
          */
          if(byte == dictionary->entries[index].code[k]){
            markIndex = index;
            longestCode = k;
          }

          else if(byte != dictionary->entries[index].code[k]){

            break;
          }

          byte = streamReadBits(in, 8);

          //ending marker
          if(byte == -1){
            break;
          }
        }
      }
    }
  }

  return &dictionary->entries[markIndex];
}

int isBlockSame(char *source, char *source2, int byteSize){
  int i, result=0;

  for(i = 0 ; byteSize >= i ; i++){

    if(source[i] == source2[i]){
    }
    else{
      result = 1;
      break;
    }
  }
  return result;
}

/*
* to find the first entry for the code to start
* return starting entry
*/
int firstMarkIndex(Dictionary *dictionary, int byte){
  int i;

  for(i = 0 ; dictionary->length > i ; i++){

    if(byte == dictionary->entries[i].code[0])
      return i;
  }
 
  Throw(NO_ENTRY);

}

//to initialize ASCII into dictionary
void dictionaryEntryInitializer(Dictionary *dictionary){
  int i;

  for(i = 0 ; i < 256 ; i++){
    dictionary->entries[i].code = codeNewAndAppend("", i);
    dictionary->entries[i].length = 1;
  }

}


