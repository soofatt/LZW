#include "OutStream.h"
#include "InStream.h"
#include "unity.h"
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

void test_streamWriteBits_write_bit_a(){
  OutStream *out;
  InStream *in;
  int result;
  
  out = openOutStream("write_a.txt", "w");
  streamWriteBits(out, 97, 8);
  closeOutStream(out);
  
  in = openInStream("write_a.txt", "r");
  result = streamReadBits(in, 8);
  closeInStream(in);
  
  TEST_ASSERT_EQUAL('a', result);

}

//1 0000 0000 -> 1000 0000 |0 (carry to next byte)
void test_streamWriteBits_write_bit_256(){
  OutStream *out;
  InStream *in;
  int result;
  
  out = openOutStream("write_256.txt", "w");
  streamWriteBits(out, 256, 9);
  closeOutStream(out);
  
  in = openInStream("write_256.txt", "r");
  result = streamReadBits(in, 8);
  closeInStream(in);
  
  TEST_ASSERT_EQUAL(128, result);
}

/*
* 1 0000 0001 -> 1000 0000 |1 (carry to next byte)
*   0110 0001 -> (carry over) 1011 0000 |1 (carry to next byte)
*/
void test_streamWriteBits_write_bit_256_and_97(){
  OutStream *out;
  int result;
  InStream *in;
  
  out = openOutStream("write_257_a.txt", "w");
  streamWriteBits(out, 257, 9);
  streamWriteBits(out, 97, 9);
  closeOutStream(out);

  in = openInStream("write_257_a.txt", "r");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(128, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(176, result);
  closeInStream(in);
}

/*
*   0110 0001 -> 0110 0001 (nothing to carry to next byte)
* 1 0000 0001 -> 1000 0000 |1 (carry to next byte)
*/
void test_streamWriteBits_write_bit_97_and_257(){
  OutStream *out;
  int result;
  InStream *in;
  
  out = openOutStream("write_a_257.txt", "w");
  streamWriteBits(out, 97, 8);
  streamWriteBits(out, 257, 9);
  closeOutStream(out);

  in = openInStream("write_a_257.txt", "r");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('a', result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(128, result);
  closeInStream(in);
}

/*
*   0110 0001 -> 0110 0001
* 1 0000 0001 -> 1000 0000 |1
*   0110 0001 -> 1011 0000 |1
*/
void test_streamWriteBits_write_bit_97_257_97(){
  OutStream *out;
  int result;
  InStream *in;
  
  out = openOutStream("write_a_257_a.txt", "w");
  streamWriteBits(out, 97, 8);
  streamWriteBits(out, 257, 9);
  streamWriteBits(out, 97, 9);
  closeOutStream(out);
  
  in = openInStream("write_a_257_a.txt", "r");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('a', result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(128, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(176, result);
  closeInStream(in);
  
}

/*
*   0110 0001 -> 0110 0001
* 0 0110 0001 -> 0011 0000 1
*/
void test_streamWriteBits_write_bit_97_97(){
  OutStream *out;
  int result;
  InStream *in;
  
  out = openOutStream("write_a_a.txt", "w");
  streamWriteBits(out, 97, 8);
  streamWriteBits(out, 97, 9);
  closeOutStream(out);

  in = openInStream("write_a_a.txt", "r");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL('a', result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(48, result);
  closeInStream(in);
}

void test_streaWriteBit_write_bit_97(){
  OutStream *out;
  out->currentbyte = 0x02;
  
  streamWriteBit(out, 1);
  
  TEST_ASSERT_EQUAL(3, out->currentbyte);


}
