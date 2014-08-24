#include "unity.h"
#include "LZWEncoder.h"
#include "CException.h"
#include "Dictionary.h"
#include "InStream.h"
#include "OutStream.h"
#include "ErrorCode.h"
#include "LZWDecoder.h"
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

void test_lzwEncoder_to_encode_a_file(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);
  currentByte = 0;
  in = openInStream("test/Data/LZW_Encode_Test_Input.txt", "r");
  out = openOutStream("test/Data/LZW_Encode_Test_Output.txt", "w");

  lzwEncoder(in, dictionary, out);
  
  closeInStream(in);
  closeOutStream(out);
}

void test_lzwDecoder_to_decode_a_file(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);
  
  in = openInStream("test/Data/LZW_Encode_Test_Output.txt", "r");
  out = openOutStream("test/Data/LZW_Decode_Test_Output.txt", "w");

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