#include <stdio.h>
#include "InStream.h"
#include "CException.h"
#include "ErrorCode.h"
#include <malloc.h>

InStream *openInStream(char *fileName, char *openMethod){
  InStream *inStream = calloc(1, sizeof(InStream));

  inStream->file = fopen(fileName, openMethod);
  inStream->filename = fileName;

  if(inStream->file == NULL)
    Throw(ERR_CANNOT_OPEN_FILE);
}