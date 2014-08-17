#include "Dictionary.h"
#include "CException.h"
#include "LZWEncoder.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "InStream.h"

/*
* to append a character to a string or another character
* 
* input : -     oldCode: old string or character
*         -codeToAppend: the character to be appended
*
* output: -newCode: the new string
*/
char *codeNewAndAppend(char *oldCode, char codeToAppend){
  char *newCode = malloc((strlen(oldCode))+ 2);

  strcpy(newCode, oldCode);
  newCode[(strlen(oldCode))] = codeToAppend;
  newCode[(strlen(oldCode))+1] = '\0';

  return newCode;
}

/*
* new dictionary
*
* input : -length: dictionary length
*
* output: -dictionary: the dictionary
*/
Dictionary *dictionaryNew(int length){
  Dictionary *dictionary;

  dictionary = malloc(sizeof(Dictionary));
  dictionary->entries = calloc(length, sizeof(DictionaryEntry));
  dictionary->length = length;
  dictionary->size = 256;
  return dictionary;
}

/*
* delete dictionary
* 
* input : -dict: the dictionary
*/
void dictionaryDel(Dictionary *dict){
  int i;

  for(i =0 ; i < dict->length ; i++){
    if(dict->entries[i].code != NULL)
      free(dict->entries[i].code);
  }

  free(dict);
}

/*
* add new dictionary entry
* 
* input : - dict: the dictionary
*       : - code: the code to add
*       : -index: the dictionary index where the code is supposed to be saved at
*
* output: -availability: 1 if successful, 0 if failed
*/
int dictionaryAdd(Dictionary *dict, char *code, int index){
  int availability =0;

  if(dict->length > index){
    dict->entries[index].code = code;
    dict->entries[index].length = strlen(code);
    availability = 1;
  }

  return availability;
}

/*
* to find the longest matching dictionary entry
*
* input : -        in: the input from file
*         -dictionary: the dictionary
*
* output: -&dictionary->entries[markIndex]: the longest matching entry
*/
DictionaryEntry *dictionaryFindLongestMatchingEntry(InStream *in, Dictionary *dictionary){
  int byte, index, markIndex, longestCode = 0, k = 0;
  
  /*
  * check if in->currentbyte is 0
  *  0: byte will get value from file
  * !0: byte will get value from in->currentbyte
  * 
  * firstMarkIndex will locate the first dictionary index that matches byte
  */
  if(in->currentbyte == 0)
    byte = streamReadBits(in, 8);
  else
    byte = in->currentbyte;
    
  markIndex = firstMarkIndex(dictionary, byte);
  
  //to loop through dictionary
  for(index = 0 ; dictionary->length > index ; index++){

    //ensure code is not null
    if(dictionary->entries[markIndex].code != NULL && dictionary->entries[index].code != NULL){

      /* 
      * compare if marked code and current code is the same, if not go to the next entry
      * longestCode will determine how many characters markIndex and index should compare
      */
      if(isBlockSame(dictionary->entries[markIndex].code, dictionary->entries[index].code, longestCode) == 0){

        for(k ; dictionary->entries[index].length > k ; k++){

          /*
          * compare if current byte is the same with byte in entry
          *     same: mark current index and mark code as longest
          * not same: return to entry
          *
          * destroy: longest code & mark index
          */
          if(byte == dictionary->entries[index].code[k]){
            markIndex = index;
            longestCode = k;
          }

          else if(byte != dictionary->entries[index].code[k])
            break;
          
          //after marking longest index, read a byte
          byte = streamReadBits(in, 8);
          
          //if byte is -1, end
          if(byte == -1)
            return &dictionary->entries[markIndex];
          
          //save byte in in->currentbyte
          in->currentbyte = byte;
        }
      }
    }
  }
  
  return &dictionary->entries[markIndex];
}

/*
* to compare source and source2
*
* input : -  source: the first source for comparison 
*         - source2: the second source for comparison
*         -byteSize: the amount of bits that source and source2 should compare
*
* output: -result: 0 if same, 1 if different
*/
int isBlockSame(char *source, char *source2, int byteSize){
  int i, result = 0;
  
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
*
* note: this function will cause bad memory if dictionary->entries[i].code[0] were to access an empty entry but this function
*       will not access an empty entry because dictionaryEntryInitializer will initialize all 255 entries with ASCII characters
*       and this function will only be called by dictionaryFindLongestMatchingEntry which will provide the value for the
*       "byte" parameter, which must be an ASCII character  
*
* input : -dictionary: the dictionary
*         -      byte: the input byte to be located in the dictionary
*
* output: -i: the dictionary index with the code that matches with the input byte
*/
int firstMarkIndex(Dictionary *dictionary, int byte){
  int i;

  for(i = 0 ; i < 256 ; i++){

    if(byte == dictionary->entries[i].code[0])
      return i;
  }
}

//to initialize ASCII into dictionary
void dictionaryEntryInitializer(Dictionary *dictionary){
  int i;

  for(i = 0 ; i < 256 ; i++){
    dictionary->entries[i].code = codeNewAndAppend("", i);
    dictionary->entries[i].length = 1;
  }

}


