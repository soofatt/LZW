#include "unity.h"
#include <stdio.h>
#include <string.h>
#include "Dictionary.h"
#include "mock_InStream.h"

void setUp(){}
void tearDown(){}

//codeNewAndAppend test//
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

//dictionaryNew test//
void test_dictionaryNew_add_new_dict(){
  int newLength;
  Dictionary *dictionary;

  dictionary = dictionaryNew(4000);

  TEST_ASSERT_NULL(dictionary->entries[6].code);
}

//dictionaryAdd test//
void test_dictionaryAdd_should_add_ab(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *shouldAdd = "ab";
  int index = 0;

  TEST_ASSERT_EQUAL(1, dictionaryAdd(dictionary, shouldAdd, index));
  TEST_ASSERT_EQUAL_STRING("ab", dictionary->entries[0].code);
}

void test_dictionaryAdd_should_add_aba(){
  Dictionary *dictionary = dictionaryNew(4000);
  dictionary->entries[0].code = "ab";
  char *shouldAdd = "aba";
  int index = 1;

  TEST_ASSERT_EQUAL(1, dictionaryAdd(dictionary, shouldAdd, index));
}

void test_dictionaryAdd_exceed_length_should_return_0(){
  Dictionary *dictionary = dictionaryNew(2);
  char *shouldAdd = "aba";
  int index = 3;

  TEST_ASSERT_EQUAL(0, dictionaryAdd(dictionary, shouldAdd, index));
}

//dictionaryFindLongestMatchingentry test//
void test_dictionaryFindLongestMatchingEntry_find_entry_abc(){

  Dictionary *dictionary = dictionaryNew(4000);
  DictionaryEntry *result;
  InStream *in;
  in->currentByte = 0;
  dictionary->entries[0].code = "ab";
  dictionary->entries[1].code = "bc";
  dictionary->entries[2].code = "cd";
  dictionary->entries[3].code = "da";

  dictionary->entries[0].length = 2;
  dictionary->entries[1].length = 2;
  dictionary->entries[2].length = 2;
  dictionary->entries[3].length = 2;

  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamReadBits_ExpectAndReturn(in, 8, 98);
  streamReadBits_ExpectAndReturn(in, 8, 99);

  result = dictionaryFindLongestMatchingEntry(in, dictionary);

  TEST_ASSERT_EQUAL_STRING("ab", result->code);


}

void test_dictionaryFindLongestMatchingEntry_find_entry_def(){

  Dictionary *dictionary = dictionaryNew(4000);
  DictionaryEntry *result;
  InStream *in;

  in->currentByte = 0;
  dictionary->entries[0].code = "ab";
  dictionary->entries[1].code = "bc";
  dictionary->entries[2].code = "cd";
  dictionary->entries[3].code = "da";
  dictionary->entries[4].code = "de";

  dictionary->entries[0].length = 2;
  dictionary->entries[1].length = 2;
  dictionary->entries[2].length = 2;
  dictionary->entries[3].length = 2;
  dictionary->entries[4].length = 2;

  streamReadBits_ExpectAndReturn(in, 8, 100);
  streamReadBits_ExpectAndReturn(in, 8, 101);
  streamReadBits_ExpectAndReturn(in, 8, 102);

  result = dictionaryFindLongestMatchingEntry(in, dictionary);

  TEST_ASSERT_EQUAL_STRING("de", result->code);


}

void test_dictionaryFindLongestMatchingEntry_find_entry_aaac(){

  Dictionary *dictionary = dictionaryNew(4000);
  DictionaryEntry *result;
  InStream *in;

  in->currentByte = 0;
  dictionary->entries[0].code = "aa";
  dictionary->entries[1].code = "aaa";

  dictionary->entries[0].length = 2;
  dictionary->entries[1].length = 3;

  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamReadBits_ExpectAndReturn(in, 8, 99);


  result = dictionaryFindLongestMatchingEntry(in, dictionary);

  TEST_ASSERT_EQUAL_STRING("aaa", result->code);


}

void test_dictionaryFindLongestMatchingEntry_find_entry_aacaad(){

  Dictionary *dictionary = dictionaryNew(4000);
  DictionaryEntry *result;
  InStream *in;

  in->currentByte = 0;
  dictionary->entries[0].code = "aa";
  dictionary->entries[1].code = "ac";
  dictionary->entries[2].code = "aac";
  dictionary->entries[3].code = "aacv";
  dictionary->entries[4].code = "aacaa";
  dictionary->entries[5].code = "aacaae";
  dictionary->entries[6].code = "aacaad";
  dictionary->entries[7].code = "aacaade";
  dictionary->entries[8].code = "aacaadf";

  dictionary->entries[0].length = 2;
  dictionary->entries[1].length = 2;
  dictionary->entries[2].length = 3;
  dictionary->entries[3].length = 4;
  dictionary->entries[4].length = 5;
  dictionary->entries[5].length = 6;
  dictionary->entries[6].length = 6;
  dictionary->entries[7].length = 7;
  dictionary->entries[8].length = 7;

  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamReadBits_ExpectAndReturn(in, 8, 99);
  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamReadBits_ExpectAndReturn(in, 8, 100);
  streamReadBits_ExpectAndReturn(in, 8, 97);

  result = dictionaryFindLongestMatchingEntry(in, dictionary);

  TEST_ASSERT_EQUAL_STRING("aacaad", result->code);
}

//isBlockSame test//
void test_isBlockSame_compare_aa_with_ab_should_return_1(){
  char *source1 = "aa";
  char *source2 = "ab";
  int byteSize = 2;

  TEST_ASSERT_EQUAL(1, isBlockSame(source1, source2, byteSize));

}

void test_isBlockSame_compare_aaaca_with_abcaa_should_return_1(){
  char *source1 = "aaaca";
  char *source2 = "abcaa";
  int byteSize = 5;

  TEST_ASSERT_EQUAL(1, isBlockSame(source1, source2, byteSize));

}

void test_isBlockSame_compare_aa_with_bb_should_return_1(){
  char *source1 = "aa";
  char *source2 = "bb";
  int byteSize = 2;

  TEST_ASSERT_EQUAL(1, isBlockSame(source1, source2, byteSize));

}

void test_isBlockSame_compare_symbol_with_symbol_should_return_1(){
  char *source1 = "&";
  char *source2 = "*";
  int byteSize = 1;

  TEST_ASSERT_EQUAL(1, isBlockSame(source1, source2, byteSize));

}

void test_isBlockSame_compare_aa_with_aa_should_return_0(){
  char *source1 = "aa";
  char *source2 = "aa";
  int byteSize = 2;

  TEST_ASSERT_EQUAL(0, isBlockSame(source1, source2, byteSize));

}

void test_isBlockSame_compare_aaaca_with_aaaca_should_return_0(){
  char *source1 = "aaaca";
  char *source2 = "aaaca";
  int byteSize = 5;

  TEST_ASSERT_EQUAL(0, isBlockSame(source1, source2, byteSize));

}

void test_isBlockSame_compare_aaaca_with_aaa_should_return_0(){
  char *source1 = "aaaca";
  char *source2 = "aaa";
  int byteSize = 5;

  TEST_ASSERT_EQUAL(1, isBlockSame(source1, source2, byteSize));

}

void test_isBlockSame_compare_symbol_with_symbol_should_return_0(){
  char *source1 = "&";
  char *source2 = "&";
  int byteSize = 1;

  TEST_ASSERT_EQUAL(0, isBlockSame(source1, source2, byteSize));

}

//firstMarkIndex test//
void test_firstMarkIndex_find_index_3(){
  Dictionary *dictionary = dictionaryNew(4000);
  int byte = 97;

  dictionary->entries[0].code = "ba";
  dictionary->entries[1].code = "na";
  dictionary->entries[2].code = "gas";
  dictionary->entries[3].code = "aaa";

  TEST_ASSERT_EQUAL(3, firstMarkIndex(dictionary, byte));

}

void test_firstMarkIndex_find_index_0(){
  Dictionary *dictionary = dictionaryNew(4000);
  int byte = 97;

  dictionary->entries[0].code = "aa";
  dictionary->entries[1].code = "na";
  dictionary->entries[2].code = "gas";
  dictionary->entries[3].code = "ha";

  TEST_ASSERT_EQUAL(0, firstMarkIndex(dictionary, byte));

}

void test_firstMarkIndex_find_index_symbol_2(){
  Dictionary *dictionary = dictionaryNew(4000);
  int byte = 95;

  dictionary->entries[0].code = "aa";
  dictionary->entries[1].code = "na";
  dictionary->entries[2].code = "_as";
  dictionary->entries[3].code = "ha";

  TEST_ASSERT_EQUAL(2, firstMarkIndex(dictionary, byte));

}

//dictionaryEntryInitializer test//
void test_dictionaryEntryInitializer_initialize_ASCII(){
  Dictionary *dictionary = dictionaryNew(4000);

  dictionaryEntryInitializer(dictionary);

  TEST_ASSERT_EQUAL('a', dictionary->entries[97].code[0]);
  TEST_ASSERT_EQUAL('b', dictionary->entries[98].code[0]);
  TEST_ASSERT_EQUAL('c', dictionary->entries[99].code[0]);
  TEST_ASSERT_EQUAL('d', dictionary->entries[100].code[0]);
  TEST_ASSERT_EQUAL('_', dictionary->entries[95].code[0]);

}



