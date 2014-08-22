#include "unity.h"
#include "CException.h"
#include <stdio.h>
#include "InStream.h"

void setUp(void){}
void tearDown(void){}

//test openInStream //
void test_openInStream_throw_no_file_found(){
	CEXCEPTION_T e;
  InStream *in;
  
  Try{
    in = openInStream("test/Data/not_found.txt", "a");
  }Catch(e){
    TEST_ASSERT_EQUAL(1, e);
  }
}

//test streamReadBits //
void test_streamReadBits_read_test_97_a_txt_contain_a(){
	CEXCEPTION_T e;
  InStream *in;
  int result;
  
  Try{
    in = openInStream("test/Data/read_a.txt", "r");
  }Catch(e){
    TEST_ASSERT_EQUAL(1, e);
  }
  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('a', result);
  closeInStream(in);
  
}

void test_streamReadBits_read_test_98_97_ba_txt_contain_b_and_a(){
	CEXCEPTION_T e;
  InStream *in;
  int result;
  
  Try{
    in = openInStream("test/Data/read_ba.txt", "r");
  }Catch(e){
    TEST_ASSERT_EQUAL(1, e);
  }
  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('b', result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('a', result);
  
  closeInStream(in);
  
}

void test_streamReadBits_read_94_txt_contain_symbol(){
	CEXCEPTION_T e;
  InStream *in;
  int result;
  
  Try{
    in = openInStream("test/Data/read_94.txt", "r");
  }Catch(e){
    TEST_ASSERT_EQUAL(1, e);
  }
  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('^', result);
  
  closeInStream(in);
  
}

//test streamReadBit //
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
