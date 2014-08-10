#include "LZWEncoder.h"
#include "unity.h"
#include "mock_InStream.h"
#include "mock_OutStream.h"
#include "Dictionary.h"

void setUp(){}
void tearDown(){}

void test_LZWEncoder_try(){

  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);
  
  dictionary->entries[0].code = "a";
  dictionary->entries[1].code = "b";
  dictionary->entries[2].code = "n";
  
  dictionary->entries[0].length = 1;
  dictionary->entries[1].length = 1;
  dictionary->entries[2].length = 1;
  
  
  streamReadBits_ExpectAndReturn(in, 8, 98);
  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamWriteBits_Expect(out, 98, 8);
  streamReadBits_ExpectAndReturn(in, 8, 110);
  streamWriteBits_Expect(out, 97, 8);
  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamWriteBits_Expect(out, 110, 8);
  streamReadBits_ExpectAndReturn(in, 8, 110);
  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamWriteBits_Expect(out, 256, 8);
  streamReadBits_ExpectAndReturn(in, 8, 97);
  streamWriteBits_Expect(out, 97, 8);
  streamReadBits_ExpectAndReturn(in, 0, 0);
  
  
  LZWEncoder(in, dictionary, out);

  TEST_ASSERT_EQUAL_STRING("an", dictionary->entries[0].code);
}





