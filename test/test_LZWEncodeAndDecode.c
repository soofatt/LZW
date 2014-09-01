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
  Dictionary *dictionary = dictionaryNew(4096);
  currentByte = 0;
  in = openInStream("test/Data/LZW_Encode_Test_Input.txt", "rb");
  out = openOutStream("test/Data/LZW_Encode_Test_Output.txt", "wb");

  lzwEncoder(in, dictionary, out);
  
  closeInStream(in);
  closeOutStream(out);
}

void test_lzwDecoder_to_decode_a_file(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4096);
  
  in = openInStream("test/Data/LZW_Encode_Test_Output.txt", "rb");
  out = openOutStream("test/Data/LZW_Decode_Test_Output.txt", "wb");

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
  
  InStream *origFile;
  InStream *decodeFile;
  int i, getChar1, getChar2;
  
  origFile = openInStream("test/Data/LZW_Encode_Test_Input.txt", "rb");
  decodeFile = openInStream("test/Data/LZW_Decode_Test_Output.txt", "rb");
  
  for(i = 0; ; i++){
    getChar1 = fgetc(origFile->file);
    getChar2 = fgetc(decodeFile->file);

    TEST_ASSERT_EQUAL(getChar1, getChar2);
    
    if(getChar1 == EOF && getChar2 == EOF)
      break;
  }
}

void test_lzwEncoder_to_encode_a_file_case2(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4096);
  currentByte = 0;
  in = openInStream("test/Data/README.txt", "rb");
  out = openOutStream("test/Data/README_Output.txt", "wb");

  lzwEncoder(in, dictionary, out);
  
  closeInStream(in);
  closeOutStream(out);
}

void test_lzwDecoder_to_decode_a_file_case2(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4096);
  
  in = openInStream("test/Data/README_Output.txt", "rb");
  out = openOutStream("test/Data/README_DecodeOutput.txt", "wb");

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
  
  InStream *origFile;
  InStream *decodeFile;
  int i, getChar1, getChar2;
  
  origFile = openInStream("test/Data/README.txt", "rb");
  decodeFile = openInStream("test/Data/README_DecodeOutput.txt", "rb");
  
  for(i = 0; ; i++){
    getChar1 = fgetc(origFile->file);
    getChar2 = fgetc(decodeFile->file);

    TEST_ASSERT_EQUAL(getChar1, getChar2);
    
    if(getChar1 == EOF && getChar2 == EOF)
      break;
  }
}