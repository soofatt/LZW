#include "CException.h"
#include "Dictionary.h"
#include "InStream.h"
#include "OutStream.h"
#include "LZWDecoder.h"
#include "ErrorCode.h"
#include "Utils.h"
#include <stdio.h>
#include <malloc.h>
#include <String.h>

#define getIndex(x) (x - 256)
#define bitWriteSize     8
#define bitReadSize     12

char *(*_getDictTranslation)(Dictionary *dict, int inputIndex) = getDictTranslation;

/*To decode a given stream of inputs
 *
 *Input: *in -> the input stream from file.
 *       *dict -> the dictionary.
 *       *out -> the output stream to file.
 *
 *Output: -
 *
 *Throw:  ERR_INVALID_INDEX -> Thrown when given input code is <0.
 *        ERR_EXCEEDING_DICTIONARY_SIZE -> Thrown when attempting to add another
 *                                         entry to a full custom dictionary
 *
 */
void lzwDecode(InStream *in, Dictionary *dict, OutStream *out){
  int inputCode, dictIndex = 0, bitLimit, bitsToRead, counter = 0;
  char *currentString, *translation, *newDictEntry;
  
  bitsToRead = getBitsToRead(dict);
  
  inputCode = streamReadBits(in, bitReadSize);
  
  if(inputCode < -1 || inputCode > (dict->length + 256))
    Throw(ERR_INVALID_INDEX);
  else if(inputCode == -1)
    printf("EOF?\n");
    
  emitCode(dict, inputCode, out);
  translation = _getDictTranslation(dict, inputCode);
  currentString = translation;
  bitLimit = 1 << (bitsToRead - 1);
  
  while(inputCode != -2){
    inputCode = streamReadBits(in, bitReadSize);
    if(inputCode == -1)
      Throw(END_OF_STREAM);
    else if(inputCode > (dict->length + 256))
      Throw(ERR_INVALID_INDEX);
      
    translation = _getDictTranslation(dict, inputCode);
    
    if(translation == NULL)//To deal with missing dictionary entry
      translation = codeNewAndAppend(currentString, currentString[0]);
    else{}//Do nothing
    
    newDictEntry = codeNewAndAppend(currentString, translation[0]);
    
    if(dictionaryAdd(dict, newDictEntry, dictIndex) == 1){
      dictIndex++;
    }
    else{
      Throw(ERR_EXCEEDING_DICTIONARY_SIZE);
    }
    
    emitCode(dict, inputCode, out);
    currentString = translation;
    
    counter++;
    if(counter == bitLimit){
      bitsToRead++;
      bitLimit = 1 << (bitsToRead - 1);
    }
  }
}

/*To find the number of bits to be read by streamReadBits function.
 *
 *Input: *dict -> the dictionary.
 *
 *Output:i -> the number of bits that is to be read.
 *
 *Throw:  -
 *
 */
int getBitsToRead(Dictionary *dict){
  int i;
  
  for(i = 0; i < dict->size; i++){
    if((1 << i) > dict->size){
      return i;
    }
  }
}

/*To find the translation of a given code if it is within the custom dictionary
 *
 *Input: *dict -> the dictionary.
 *       inputIndex -> input code.
 *
 *Output:translation -> the translation of the input code.
 *
 *Throw:  -
 *
 */
char *getDictTranslation(Dictionary *dict, int inputIndex){
  char *translation = "";
  int index;
  
  if(inputIndex >= 0 && inputIndex < 256)
    translation = codeNewAndAppend("", (uint8)inputIndex);
  else if(inputIndex > 255){
    index = getIndex(inputIndex);//To find the corresponding index for the custom dictionary
    translation = dict->entries[index].code;
  }
  // else if(inputIndex > (dict->length + 256))
    // Throw(ERR_EXCEEDING_DICTIONARY_SIZE);
  
  return translation;
}

/*To find the translation of a given code and output through streamWriteBits function.
 *
 *Input: *dict -> the dictionary.
 *       inputIndex -> input code (which is also the dictionary index to be searched).
 *       *out  -> output stream to file.
 *
 *Output: -
 *
 *Throw:  ERR_INVALID_INDEX -> Thrown if index is <0.
 *
 */
void emitCode(Dictionary *dict, int inputIndex, OutStream *out){
  char *translation;
  int i;
  
  if(inputIndex < 256 && inputIndex > 0){
    streamWriteBits(out, inputIndex, bitWriteSize);
  }
  else if(inputIndex == 0){}//Do Nothing
  else if(inputIndex >= 256){
    translation = _getDictTranslation(dict, inputIndex);
    for(i = 0; i < strlen(translation); i++){
      streamWriteBits(out, translation[i], bitWriteSize);
    }
  }
  else{
    Throw(ERR_INVALID_INDEX);
  }
}