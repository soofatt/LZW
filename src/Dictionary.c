#include "Dictionary.h"
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
    availability = 1;
  }
    
  return availability;
}

DictionaryEntry *dictionaryFindLongestMatchingEntry(InStream *in, Dictionary *dictionary){
  int byte, firstByte;
  int index, markIndex, longestCode = 0, k = 0;
  
  byte = streamReadBits(in, 8);
  firstByte = byte;
  
  markIndex = firstMarkIndex(dictionary, firstByte);
  
  for(index = 0 ; dictionary->length > index ; index++){ //to loop through dictionary
   
    if(dictionary->entries[markIndex].code != NULL && dictionary->entries[index].code != NULL){

      if(isBlockSame(dictionary->entries[markIndex].code, dictionary->entries[index].code, longestCode) == 0){
        
        for(k ; dictionary->entries[index].length > k ; k++){

          if(byte == dictionary->entries[index].code[k]){
            markIndex = index;
            longestCode = k;
          }  
          
          else if(byte != dictionary->entries[index].code[k]){
           
            break;
          }
          
          byte = streamReadBits(in, 8);

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

int firstMarkIndex(Dictionary *dictionary, int byte){
  int i;
  
  for(i = 0 ; dictionary->length > i ; i++){
    if(byte == dictionary->entries[i].code[0])
      return i;
  }

}






