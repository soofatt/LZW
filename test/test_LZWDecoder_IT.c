#include "unity.h"
#include "CException.h"
#include "Dictionary.h"
#include "InStream.h"
#include "OutStream.h"
#include "ErrorCode.h"
#include "LZWDecoder.h"

void setUp(void){}
void tearDown(void){}

// void test_lzwDecoder_to_decode_a_file(){
  // CEXCEPTION_T e;
  // OutStream *out;
  // InStream *in;
  // Dictionary *dictionary = dictionaryNew(4000);
  // currentByte = 0;
  // in = openInStream("test/Data/LZW_Encode_Test_Output.txt", "r");
  // out = openOutStream("test/Data/LZW_Decode_Test_Output.txt", "w");

  // Try{
    // lzwDecode(in, dictionary, out);
  // }Catch(e){
    // switch(e){
      // case 3 :
        // TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        // break;
      // case 4:
        // TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        // break;
    // }
  // }
  
  // closeInStream(in);
  // closeOutStream(out);
// }

void test_lzwDecode_given_code_97_should_decode_into_a(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  OutStream *out = openOutStream("test/data/LZWDecodeOutput_1.txt", "wb");
  InStream *in = openInStream("test/data/LZWDecodeInput_1.txt", "rb");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
  }
  
  closeInStream(in);
  closeOutStream(out);
  
}

void test_lzwDecode_given_code_98_97_should_decode_into_ba(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  OutStream *out = openOutStream("test/data/LZWDecodeOutput_2.txt", "wb");
  InStream *in = openInStream("test/data/LZWDecodeInput_2.txt", "rb");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[0].code);
  }
  
  closeInStream(in);
  closeOutStream(out);
}

void test_lzwDecode_given_code_98_97_110_should_decode_into_ban(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(100);
  OutStream *out = openOutStream("test/data/LZWDecodeOutput_3.txt", "wb");
  InStream *in = openInStream("test/data/LZWDecodeInput_3.txt", "rb");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("an", dictionary->entries[1].code);
  }
  
  closeInStream(in);
  closeOutStream(out);
}

/*
 * Input : 97, 98, 99, 100, 256, 99(Integer)
 *         0x61, 0x62, 0x63, 0x64, 0x100, 0x63(Hex)
 *
 *         In file(fixed for 12 bits):
 *         0x06, 0x10, 0x62, 0x06, 0x30, 0x64, 0x10, 0x00, 0x63
 *
 * Output : abcdabc
 *
 */
void test_lzwDecode_case_1_should_decode_into_abcdabc(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(4096);
  OutStream *out = openOutStream("test/data/LZWDecodeOutput_4.txt", "wb");
  InStream *in = openInStream("test/data/LZWDecodeInput_4.txt", "rb");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("ab", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("bc", dictionary->entries[1].code);
    TEST_ASSERT_EQUAL_STRING("cd", dictionary->entries[2].code);
    TEST_ASSERT_EQUAL_STRING("da", dictionary->entries[3].code);
    TEST_ASSERT_EQUAL_STRING("abc", dictionary->entries[4].code);
  }
  
  closeInStream(in);
  closeOutStream(out);
}

/*
 * Input : 97, 256, 257, 97
 *         0x61, 0x100, 0x101, 0x61
 *
 *         In file(fixed for 12 bits):
 *         0x06, 0x11, 0x00, 0x10, 0x10, 0x61
 *
 * Output : aaaaaaa
 *
 */
void test_lzwDecode_case_2_should_decode_into_aaaaaaa(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(4096);
  OutStream *out = openOutStream("test/data/LZWDecodeOutput_5.txt", "wb");
  InStream *in = openInStream("test/data/LZWDecodeInput_5.txt", "rb");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("aa", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("aaa", dictionary->entries[1].code);
    TEST_ASSERT_EQUAL_STRING("aaaa", dictionary->entries[2].code);
  }
  
  closeInStream(in);
  closeOutStream(out);
}

/*
 * Input : 98, 97, 110, 257, 259
 *         0x62, 0x61, 0x6e, 0x101, 0x103
 *
 *         In file(fixed for 12 bits):
 *         0x06, 0x20, 0x61, 0x06, 0xe1, 0x01, 0x10, 0x30
 *
 * Output : bananana
 *
 */
void test_lzwDecode_case_3_should_decode_into_bananana(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(4096);
  OutStream *out = openOutStream("test/data/LZWDecodeOutput_6.txt", "wb");
  InStream *in = openInStream("test/data/LZWDecodeInput_6.txt", "rb");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("an", dictionary->entries[1].code);
    TEST_ASSERT_EQUAL_STRING("na", dictionary->entries[2].code);
    TEST_ASSERT_EQUAL_STRING("ana", dictionary->entries[3].code);
  }
  
  closeInStream(in);
  closeOutStream(out);
}

/*
 * Input : 98, 97, 110, 257, 97, 95, 258, 258, 256
 *         0x62, 0x61, 0x6e, 0x101, 0x61, 0x5f, 0x102, 0x102, 0x100
 *
 *         In file(fixed for 12 bits):
 *         0x06, 0x20, 0x61, 0x06, 0xe1, 0x01, 0x06, 0x10, 0x5f, 0x10, 0x21, 0x02, 0x10, 0x00
 *
 * Output : banana_nanaba
 *
 */
void test_lzwDecode_case_4_should_decode_into_banana_nanaba(){
  CEXCEPTION_T e;
  Dictionary *dictionary = dictionaryNew(4096);
  OutStream *out = openOutStream("test/data/LZWDecodeOutput_7.txt", "wb");
  InStream *in = openInStream("test/data/LZWDecodeInput_7.txt", "rb");
  
  Try{
    lzwDecode(in, dictionary, out);
  }Catch(e){
    switch(e){
      case 3 :
        TEST_ASSERT_EQUAL(END_OF_STREAM, e);
        break;
      case 4:
        TEST_ASSERT_EQUAL(ERR_CANNOT_OPEN_FILE, e);
        break;
    }
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[0].code);
    TEST_ASSERT_EQUAL_STRING("an", dictionary->entries[1].code);
    TEST_ASSERT_EQUAL_STRING("na", dictionary->entries[2].code);
    TEST_ASSERT_EQUAL_STRING("ana", dictionary->entries[3].code);
    TEST_ASSERT_EQUAL_STRING("a_", dictionary->entries[4].code);
    TEST_ASSERT_EQUAL_STRING("_n", dictionary->entries[5].code);
    TEST_ASSERT_EQUAL_STRING("nan", dictionary->entries[6].code);
    TEST_ASSERT_EQUAL_STRING("nab", dictionary->entries[7].code);
  }
  
  closeInStream(in);
  closeOutStream(out);
}
