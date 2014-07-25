#include "LZWEncoder.h"
#include <stdio.h>
#include <malloc.h>

char *codeNewAndAppend(char *oldCode, char codeToAppend){

return codeToAppend;
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