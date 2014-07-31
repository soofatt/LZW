#include "LZWEncoder.h"
#include "unity.h"

void setUp(){}
void tearDown(){}

void test_dictionaryNew_add_new_dict(){
  int newLength;
  Dictionary *dictionary;
  
  dictionary = dictionaryNew(4000);

  TEST_ASSERT_NULL(dictionary->entries[6].code);
}

void test_codeNewAndAppend(){
  Dictionary *dictionary = dictionaryNew(40);
  char shouldAdd = 'a'; 
  
  TEST_ASSERT_EQUAL_STRING("ba",codeNewAndAppend("b", shouldAdd));
}














