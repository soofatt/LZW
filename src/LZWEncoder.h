#ifndef LZWEncoder_H
#define LZWEncoder_H


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

#endif // LZWEncoder_H
