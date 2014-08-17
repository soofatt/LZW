#include "OutStream.h"
#include "unity.h"
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

void test_streamWriteBits_write_bit_a(){
  OutStream *out;
  int result;
  
  out = openOutStream("hi.txt", "w");
  streamWriteBits(out, 97, 8);
  
  closeOutStream(out);

}

void test_streamWriteBits_write_bit_256(){
  OutStream *out;
  int result;
  out->bitIndex = 0;
  out = openOutStream("bye.txt", "w");
  streamWriteBits(out, 256, 9);
  
  closeOutStream(out);

}


void test_streamWriteBits_write_bit_256_and_97(){
  OutStream *out;
  int result;
  out->bitIndex = 0;
  out = openOutStream("cya.txt", "w");
  streamWriteBits(out, 257, 9);
  streamWriteBits(out, 97, 9);
  
  closeOutStream(out);

}

void test_streamWriteBits_write_bit_97_and_257(){
  OutStream *out;
  int result;
  out->bitIndex = 0;
  out = openOutStream("cyu.txt", "w");
  streamWriteBits(out, 97, 8);
  streamWriteBits(out, 257, 9);
  
  closeOutStream(out);

}

void test_streamWriteBits_write_bit_97_257_97(){
  OutStream *out;
  int result;
  out->bitIndex = 0;
  out = openOutStream("cye.txt", "w");
  streamWriteBits(out, 97, 8);
  streamWriteBits(out, 257, 9);
  streamWriteBits(out, 97, 9);
  
  closeOutStream(out);

}


