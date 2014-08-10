#ifndef Dictionary_H
#define Dictionary_H
#include "InStream.h"
typedef struct{
  char *code;
  int length;
}DictionaryEntry;

typedef struct{
  DictionaryEntry *entries;
  int length;
}Dictionary;

char *codeNewAndAppend(char *oldCode, char codeToAppend);
Dictionary *dictionaryNew(int length);
void dictionaryDel(Dictionary *dict);
int dictionaryAdd(Dictionary *dict, char *code, int index);
DictionaryEntry *dictionaryFindLongestMatchingEntry(InStream *in, Dictionary *dictionary);
int firstMarkIndex(Dictionary *dictionary, int byte);
#endif // Dictionary_H
