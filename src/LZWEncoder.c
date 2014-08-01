#include "LZWEncoder.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

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

