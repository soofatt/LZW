#include "Dictionary.h"
#include <stdio.h>
#include <string.h>
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

DictionaryEntry *dictionaryFindLongestMatchingEntry(char *code, Dictionary *dictionary){
  Dictionary *dictStack = dictionary;
  int i, j, numberOfMatches = 0; 
  
  /*
  *  big loop    small loop
  *  abcd |      abcd  
  *  dcba |      dcba
  *  cbda |      cbda 
  *  dacb V      dacb
  *              --->
  * 
  * numberOfMatches: denotes the longest number of character matches in a string, if it's longer than the previous string, save into dictStack
  *               j: denotes the n-th number of character of the string, the larger the j, the more character matches in the string
  */
  
  for(i = 0 ; dictionary->length > i ; i++){ //to loop through dictionary

    for(j =0 ; strlen(code) > j; j++){ //to loop through length of code and get it's longest match

      if(code[j] == dictionary->entries[i].code[j]){ //if match found, save the entry into dictStack->entry[0]
        if(numberOfMatches < j){
          numberOfMatches = j;
          dictStack->entries[0] = dictionary->entries[i];
        }
      }
      
      else if(code[j] != dictionary->entries[i].code[j]){ //if doesnt match break from loop, return to dictionary length loop
        break;
      }
      
    }
    
  }

  return &dictStack->entries[0];
  
}











