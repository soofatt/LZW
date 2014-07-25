#ifndef OutStream_H
#define OutStream_H

typedef struct{

}OutStream;

void streamWriteBits(OutStream *out, int bitsToWrite, int bitSize);
void streamFlush(OutStream *out);
#endif // OutStream_H
