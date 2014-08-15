#include "OutStream.h"
#include "unity.h"
#include "CException.h"
#include <stdio.h>

void setUp(void){}
void tearDown(void){}

// void test_openOutStream_throw_no_file_found(void){
	// CEXCEPTION_T e;
  // OutStream *out;
  
  // Try{
    // out = openOutStream("sup.txt", "w");
  // }Catch(e){
    // TEST_ASSERT_EQUAL(1, e);
  // }
// }

void test_streamWriteBits_write_bit_a(){
  CEXCEPTION_T e;
  OutStream *out;
  int result;
  
  Try{
    out = openOutStream("hi.txt", "w");
  }Catch(e){
    TEST_ASSERT_EQUAL(1, e);
  }
  
  streamWriteBits(out, 97, 8);
  
  closeOutStream(out);

}