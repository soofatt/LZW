#include "OutStream.h"
#include "unity.h"
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

void test_streamWriteBits_write_bit_a(){
  OutStream *out;
  int result;
  
  out = openOutStream("write_a.txt", "w");
  streamWriteBits(out, 97, 8);
  
  closeOutStream(out);

}

void test_streamWriteBits_write_bit_256(){
  OutStream *out;
  int result;
  out->bitIndex = 0;
  out = openOutStream("write_256.txt", "w");
  streamWriteBits(out, 256, 9);
  
  closeOutStream(out);

}

void test_streamWriteBits_write_bit_256_and_97(){
  OutStream *out;
  int result;
  out->bitIndex = 0;
  out = openOutStream("write_257_a.txt", "w");
  streamWriteBits(out, 257, 9);
  streamWriteBits(out, 97, 9);
  
  closeOutStream(out);

}

void test_streamWriteBits_write_bit_97_and_257(){
  OutStream *out;
  int result;
  out->bitIndex = 0;
  out = openOutStream("write_a_257.txt", "w");
  streamWriteBits(out, 97, 8);
  streamWriteBits(out, 257, 9);
  
  closeOutStream(out);

}

void test_streamWriteBits_write_bit_97_257_97(){
  OutStream *out;
  int result;
  out->bitIndex = 0;
  out = openOutStream("write_a_257_a.txt", "w");
  streamWriteBits(out, 97, 8);
  streamWriteBits(out, 257, 9);
  streamWriteBits(out, 97, 9);
  
  closeOutStream(out);

}

void test_streamWriteBits_write_bit_97_97(){
  OutStream *out;
  int result;
  out->bitIndex = 0;
  out = openOutStream("write_a_a.txt", "w");
  streamWriteBits(out, 97, 8);
  streamWriteBits(out, 97, 9);
  
  
  closeOutStream(out);

}

void test_streaWriteBit_write_bit_97(){
  OutStream *out;
  out->currentbyte = 0x02;
  
  streamWriteBit(out, 1);
  
  TEST_ASSERT_EQUAL(3, out->currentbyte);


}
