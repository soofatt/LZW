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
  
  out = openOutStream("test/Data/write_a.txt", "wb");
  streamWriteBits(out, 97, 12);
  streamWriteBits(out, 0, 12);
  closeOutStream(out);
  
  in = openInStream("test/Data/write_a.txt", "rb");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(6, result);      
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(16, result);     
  closeInStream(in);
  
}

void test_streamWriteBits_write_b_256(){
  OutStream *out;
  int result;
  InStream *in;
 
  out = openOutStream("test/Data/write_b_256.txt", "wb");
  streamWriteBits(out, 98, 12);
  streamWriteBits(out, 256, 12);
  streamWriteBits(out, 0, 12);
  closeOutStream(out);

  in = openInStream("test/Data/write_b_256.txt", "rb");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(6, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(33, result);    
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(0, result);   
  closeInStream(in);
}

void test_streamWriteBits_write_ba(){
  OutStream *out;
  int result;
  InStream *in;

  out = openOutStream("test/Data/write_ba.txt", "wb");
  streamWriteBits(out, 98, 12);
  streamWriteBits(out, 97, 12);
  streamWriteBits(out, 0, 12);
  closeOutStream(out);

  in = openInStream("test/Data/write_ba.txt", "rb");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(6, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(32, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(97, result);
  closeInStream(in);

}

void test_streamWriteBits_write_bit_b_256_257(){
  OutStream *out;
  int result;
  InStream *in;

  out = openOutStream("test/Data/write_b_256_257.txt", "wb");
  streamWriteBits(out, 98, 12);
  streamWriteBits(out, 256, 12);
  streamWriteBits(out, 257, 12);
  streamWriteBits(out, 0, 12);
  streamWriteBits(out, 0, 12);
  closeOutStream(out);
  
  in = openInStream("test/Data/write_b_256_257.txt", "rb");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(6, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(33, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(0, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(16, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(16, result);
  closeInStream(in);
  
}

void test_streamWriteBits_write_12_characters(){
  OutStream *out;
  int result;
  InStream *in;

  out = openOutStream("test/Data/write_8.txt", "wb");
  streamWriteBits(out, 98, 12);
  streamWriteBits(out, 256, 12);
  streamWriteBits(out, 257, 12);
  streamWriteBits(out, 258, 12);
  streamWriteBits(out, 259, 12);
  streamWriteBits(out, 260, 12);
  streamWriteBits(out, 261, 12);
  streamWriteBits(out, 262, 12);
  streamWriteBits(out, 263, 12);
  streamWriteBits(out, 264, 12);
  streamWriteBits(out, 265, 12);
  streamWriteBits(out, 0, 12);
  streamWriteBits(out, 0, 12);
  streamWriteBits(out, 0, 12);
  streamWriteBits(out, 0, 12);
  streamWriteBits(out, 0, 12);
  streamWriteBits(out, 0, 12);
  streamWriteBits(out, 0, 12);
  closeOutStream(out);
  
  in = openInStream("test/Data/write_8.txt", "rb");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(6, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(33, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(0, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(16, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(17, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(2, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(16, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(49, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(4, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(16, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(81, result); 
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(6, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(16, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(113, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(8, result); 
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(16, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(144, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(0, result);
  closeInStream(in);
  
}

void test_streamWriteBits_write_b_a_n(){
  OutStream *out;
  int result;
  InStream *in;
  
  out = openOutStream("test/Data/write_b_a_n.txt", "wb");
  streamWriteBits(out, 98, 12);
  streamWriteBits(out, 97, 12);
  streamWriteBits(out, 110, 12);
  streamWriteBits(out, 0, 12);
  streamWriteBits(out, 0, 12);
  closeOutStream(out);

  in = openInStream("test/Data/write_b_a_n.txt", "rb");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(6, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(32, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(97, result);  
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(6, result); 
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(224, result);
  closeInStream(in);
}

void test_streamWriteBits_write_129(){
  OutStream *out;
  int result;
  InStream *in;
  
  out = openOutStream("test/Data/write_129.txt", "wb");
  streamWriteBits(out, 129, 12);
  streamWriteBits(out, 0, 12);
  closeOutStream(out);

  in = openInStream("test/Data/write_129.txt", "rb");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(8, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(16, result);  
  closeInStream(in);
}

void test_streamWriteBits_write_246(){
  OutStream *out;
  int result;
  InStream *in;
  
  out = openOutStream("test/Data/write_246.txt", "wb");
  streamWriteBits(out, 246, 12);
  streamWriteBits(out, 0, 12);
  closeOutStream(out);

  in = openInStream("test/Data/write_246.txt", "rb");
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(15, result);
  result = streamReadBits(in, 8);
  TEST_ASSERT_EQUAL(96, result);  
  closeInStream(in);
}

void test_streaWriteBit_write_bit_97(){
  OutStream *out;
  out->currentByte = 0x02;
  
  streamWriteBit(out, 1);
  
  TEST_ASSERT_EQUAL(3, out->currentByte);
}
