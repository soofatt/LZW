#include "OutStream.h"
#include "InStream.h"
#include "unity.h"
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

void test_streamWriteBits_write_a(){
  OutStream *out;
  InStream *in;
  int result;
  
  out = openOutStream("test/Data/write_a.txt", "w");
  streamWriteBits(out, 97, 8);
  closeOutStream(out);
  
  in = openInStream("test/Data/write_a.txt", "r");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('a', result);     
  closeInStream(in);
  
}

/*
*  should write 0110 0010 1000 0000 0000 0000
*               b         128       0
*/
void test_streamWriteBits_write_b_256(){
  OutStream *out;
  int result;
  InStream *in;
 
  out = openOutStream("test/Data/write_b_256.txt", "w");
  streamWriteBits(out, 98, 8);
  streamWriteBits(out, 256, 9);
  streamWriteBits(out, 0, 9);
  closeOutStream(out);

  in = openInStream("test/Data/write_b_256.txt", "r");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(98, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(128, result);    
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(0, result);  
  closeInStream(in);
}

/*
* should write 0110 0010 0011 0000 1000 0000
*              b         48        128
*/
void test_streamWriteBits_write_ba(){
  OutStream *out;
  int result;
  InStream *in;

  out = openOutStream("test/Data/write_ba.txt", "w");
  streamWriteBits(out, 98, 8);
  streamWriteBits(out, 97, 9);
  streamWriteBits(out, 0, 9);
  closeOutStream(out);

  in = openInStream("test/Data/write_ba.txt", "r");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('b', result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(48, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(128, result);
  closeInStream(in);

}

/*
* should write 0110 0010 1000 0000 0100 0000 0100 0000 
*              b         128       64        64
*/
void test_streamWriteBits_write_bit_b_256_257(){
  OutStream *out;
  int result;
  InStream *in;

  out = openOutStream("test/Data/write_b_256_257.txt", "w");
  streamWriteBits(out, 98, 8);
  streamWriteBits(out, 256, 9);
  streamWriteBits(out, 257, 9);
  streamWriteBits(out, 0, 9);
  closeOutStream(out);
  
  in = openInStream("test/Data/write_b_256_257.txt", "r");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('b', result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(128, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(64, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(64, result);
  closeInStream(in);
  
}

void test_streamWriteBits_write_bit_8(){
  OutStream *out;
  int result;
  InStream *in;

  out = openOutStream("test/Data/write_8.txt", "w");
  streamWriteBits(out, 98, 8);
  streamWriteBits(out, 256, 9);
  streamWriteBits(out, 257, 9);
  streamWriteBits(out, 258, 9);
  streamWriteBits(out, 259, 9);
  streamWriteBits(out, 260, 9);
  streamWriteBits(out, 261, 9);
  streamWriteBits(out, 262, 9);
  streamWriteBits(out, 263, 9);
  streamWriteBits(out, 264, 9);
  streamWriteBits(out, 265, 9);
  streamWriteBits(out, 0, 9);
  closeOutStream(out);
  
  in = openInStream("test/Data/write_8.txt", "r");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('b', result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(128, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(64, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(96, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(80, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(56, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(36, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(22, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(13, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(7, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(132, result); 
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(66, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(64, result);
  closeInStream(in);
  
}

/*
* should write 0110 0010 0011 0000 1001 1011 1000 0000
*              b         48        155       128
*/
void test_streamWriteBits_write_b_a_n(){
  OutStream *out;
  int result;
  InStream *in;
  
  out = openOutStream("test/Data/write_b_a_n.txt", "w");
  streamWriteBits(out, 98, 8);
  streamWriteBits(out, 97, 9);
  streamWriteBits(out, 110, 9);
  streamWriteBits(out, 0, 9);
  closeOutStream(out);

  in = openInStream("test/Data/write_b_a_n.txt", "r");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('b', result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(48, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(155, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(128, result);
  closeInStream(in);
}

void test_streaWriteBit_write_bit_97(){
  OutStream *out;
  out->currentByte = 0x02;
  
  streamWriteBit(out, 1);
  
  TEST_ASSERT_EQUAL(3, out->currentByte);
}
