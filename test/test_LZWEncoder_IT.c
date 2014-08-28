#include "unity.h"
#include <stdio.h>
#include "LZWEncoder.h"
#include "CException.h"
#include "InStream.h"
#include "OutStream.h"
#include "Dictionary.h"
unsigned char currentByte;
void setUp(){}
void tearDown(){}

// lzwEncoder test//
void xtest_lzwEncoder_encode_b(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);
  currentByte = 0;
  
  in = openInStream("test/Data/lzw_b.txt", "rb");
  out = openOutStream("test/Data/lzw_b_enc.txt", "wb");
  
  lzwEncoder(in, dictionary, out);

}

void xtest_lzwEncoder_encode_banana(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);
  currentByte = 0;
  
  in = openInStream("test/Data/lzw_banana.txt", "rb");
  out = openOutStream("test/Data/lzw_banana_enc.txt", "wb");
  

  lzwEncoder(in, dictionary, out);

}

void xtest_lzwEncoder_encode_aaaaaa(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);
  currentByte = 0;
  in = openInStream("test/Data/lzw_aaaaaa.txt", "rb");
  out = openOutStream("test/Data/lzw_aaaaaa_enc.txt", "wb");
  
  lzwEncoder(in, dictionary, out);

}

void xtest_lzwEncoder_encode_banana_nanaba(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);
  currentByte = 0;
  in = openInStream("test/Data/lzw_banana_nanaba.txt", "rb");
  out = openOutStream("test/Data/lzw_banana_nanaba_enc.txt", "wb");

  lzwEncoder(in, dictionary, out);
}

// void test_lzwEncoder_to_encode_a_file(){
  // CEXCEPTION_T e;
  // OutStream *out;
  // InStream *in;
  // Dictionary *dictionary = dictionaryNew(4000);
  // currentByte = 0;
  // in = openInStream("test/Data/LZW_Encode_Test_Input.txt", "r");
  // out = openOutStream("test/Data/LZW_Encode_Test_Output.txt", "w");

  // lzwEncoder(in, dictionary, out);
  
  // closeInStream(in);
  // closeOutStream(out);
// }

void test_lzwEncoder_encode_ban(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);
  currentByte = 0;
  in = openInStream("test/Data/LZWDecodeOutput_3.txt", "rb");
  out = openOutStream("test/Data/LZWDecodeOutput_3_enc.txt", "wb");
  lzwEncoder(in, dictionary, out);
}

void test_lzwEncoder_encode_bananana(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);
  currentByte = 0;
  in = openInStream("test/Data/LZWDecodeOutput_6.txt", "rb");
  out = openOutStream("test/Data/LZWDecodeOutput_6_enc.txt", "wb");
 
  lzwEncoder(in, dictionary, out);
}

// getIntFromChar test//
void test_getIntFromChar_get_97(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *code = "a";
  
  TEST_ASSERT_EQUAL(97, getIntFromChar(dictionary, code));

}

void test_getIntFromChar_get_32(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *code = " ";

  TEST_ASSERT_EQUAL(32, getIntFromChar(dictionary, code));
}

void test_getIntFromChar_get_256(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *code = "ba";
  
  dictionary->entries[256].code = "ba";
  
  TEST_ASSERT_EQUAL(256, getIntFromChar(dictionary, code));

}

void test_getIntFromChar_get_257(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *code = "ba";
  
  dictionary->entries[256].code = "na";
  dictionary->entries[257].code = "ba";
  dictionary->entries[258].code = "ra";
  
  TEST_ASSERT_EQUAL(257, getIntFromChar(dictionary, code));

}

void test_getIntFromChar_get_258(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *code = "*a";
  
  dictionary->entries[256].code = "na";
  dictionary->entries[257].code = "ba";
  dictionary->entries[258].code = "*a";
  
  TEST_ASSERT_EQUAL(258, getIntFromChar(dictionary, code));

}

