#include "unity.h"
#include <stdio.h>
#include <string.h>
#include "Dictionary.h"
#include "mock_InStream.h"
#include "mock_OutStream.h"

void setUp(){}
void tearDown(){}

void test_dictionaryNew_add_new_dict(){
  int newLength;
  Dictionary *dictionary;
  
  dictionary = dictionaryNew(4000);

  TEST_ASSERT_NULL(dictionary->entries[6].code);
}

void test_codeNewAndAppend_b_to_ba(){
  Dictionary *dictionary = dictionaryNew(40);
  char shouldAdd = 'a'; 
  
  TEST_ASSERT_EQUAL_STRING("ba",codeNewAndAppend("b", shouldAdd));
}

void test_codeNewAndAppend_ba_to_ban(){
  Dictionary *dictionary = dictionaryNew(40);
  char shouldAdd = 'n'; 
  

  TEST_ASSERT_EQUAL_STRING("ban",codeNewAndAppend("ba", shouldAdd));
}

void test_codeNewAndAppend_ban_to_bana(){
  Dictionary *dictionary = dictionaryNew(40);
  char shouldAdd = 'a'; 
  

  TEST_ASSERT_EQUAL_STRING("bana",codeNewAndAppend("ban", shouldAdd));
}

void test_dictionaryAdd_should_add_ab(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *shouldAdd = "ab";
  int index = 1;
  
  TEST_ASSERT_EQUAL(1, dictionaryAdd(dictionary, shouldAdd, index));
}

void test_dictionaryAdd_should_add_aba(){
  Dictionary *dictionary = dictionaryNew(4000);
  dictionary->entries[0].code = "ab";
  char *shouldAdd = "aba";
  int index = 1;
  
  TEST_ASSERT_EQUAL(1, dictionaryAdd(dictionary, shouldAdd, index));
}

void test_dictionaryAdd_exceed_length_should_return_0(){
  Dictionary *dictionary = dictionaryNew(4000);
  dictionary->length = 2;
  char *shouldAdd = "aba";
  int index = 3;
  
  TEST_ASSERT_EQUAL(0, dictionaryAdd(dictionary, shouldAdd, index));
}

void test_dictionaryFindLongestMatchingEntry_find_entry_aa(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *shouldFind = "aa";
  DictionaryEntry *result;
  
  dictionary->length = 4;
  dictionary->entries[0].code = "ba"; 
  dictionary->entries[1].code = "aa"; 
  dictionary->entries[2].code = "dc"; 
  dictionary->entries[3].code = "ab"; 

  result = dictionaryFindLongestMatchingEntry(shouldFind, dictionary);
 
  TEST_ASSERT_EQUAL_STRING("aa", result->code);

}

void test_dictionaryFindLongestMatchingEntry_find_entry_aaaa(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *shouldFind = "aaaa";
  DictionaryEntry *result;
  
  dictionary->length = 5;
  dictionary->entries[0].code = "ba"; 
  dictionary->entries[1].code = "aa"; 
  dictionary->entries[2].code = "aba"; 
  dictionary->entries[3].code = "acb"; 
  dictionary->entries[4].code = "aaaa"; 
  
  result = dictionaryFindLongestMatchingEntry(shouldFind, dictionary);
 
  TEST_ASSERT_EQUAL_STRING("aaaa", result->code);

}

void test_dictionaryFindLongestMatchingEntry_find_entry_aaac(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *shouldFind = "aaaca";
  DictionaryEntry *result;
  
  dictionary->length = 5;
  dictionary->entries[0].code = "ba"; 
  dictionary->entries[1].code = "aa"; 
  dictionary->entries[2].code = "aca"; 
  dictionary->entries[3].code = "aaba"; 
  dictionary->entries[4].code = "aaac"; 
  
  result = dictionaryFindLongestMatchingEntry(shouldFind, dictionary);
 
  TEST_ASSERT_EQUAL_STRING("aaac", result->code);

}

void test_dictionaryFindLongestMatchingEntry_find_entry_aaacaa(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *shouldFind = "aaaca";
  DictionaryEntry *result;
  
  dictionary->length = 6;
  dictionary->entries[0].code = "ba"; 
  dictionary->entries[1].code = "aa"; 
  dictionary->entries[2].code = "aca"; 
  dictionary->entries[3].code = "aaba"; 
  dictionary->entries[4].code = "aaaca"; 
  dictionary->entries[5].code = "aaacab"; 
  
  result = dictionaryFindLongestMatchingEntry(shouldFind, dictionary);
 
  TEST_ASSERT_EQUAL_STRING("aaaca", result->code);

}

//try aaaaaaaaa



