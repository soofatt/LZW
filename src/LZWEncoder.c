#include "LZWEncoder.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

char *codeNewAndAppend(char *oldCode, char codeToAppend){
  char *newCode = malloc((strlen(oldCode))+ 2);
  
  strcpy(newCode, oldCode);
  newCode[(strlen(newCode))] = codeToAppend;
  newCode[(strlen(newCode))+1] = '\0';  
  // newCode[1] = codeToAppend;
  // newCode[2] = '\0';
  printf("%d", (strlen(newCode)));
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

void dictionaryAdd(Dictionary *dict, char *code, int index){

}