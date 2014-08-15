#include "unity.h"
#include "CException.h"
#include <stdio.h>
#include "InStream.h"

void setUp(void){}
void tearDown(void){}

void test_openInStream_throw_no_file_found(void){
	CEXCEPTION_T e;
  InStream *in;
  
  Try{
    in = openInStream("sup.txt", "a");
  }Catch(e){
    TEST_ASSERT_EQUAL(1, e);
  }
}

void test_streamReadBits_read_test_txt(void){
	CEXCEPTION_T e;
  InStream *in;
  int result;
  
  Try{
    in = openInStream("test.txt", "r");
  }Catch(e){
    TEST_ASSERT_EQUAL(1, e);
  }
  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(97, result);
  closeInStream(in);
  
}


void test_streamReadBit_read_1_from_0xff(){
  int result, byte;
  
  byte = 0x97;
  result = streamReadBit(byte);
  
  TEST_ASSERT_EQUAL_HEX(0x1, result);
}

void test_streamReadBit_read_0_from_0x0f(){
  int result, byte;
  
  byte = 0x0f;
  result = streamReadBit(byte);
  
  TEST_ASSERT_EQUAL(0, result);
}
