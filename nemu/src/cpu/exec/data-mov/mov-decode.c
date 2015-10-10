#include"common.h"
#include"mov-decode.h"

Operands ops_decoded;

#define DATA_BYTE1 1
#define DATA_BYTE2 2
#include"mov-decode-template.h"
#undef DATA_BYTE1
#undef DATA_BYTE2

#define DATA_BYTE1 1
#define DATA_BYTE2 4
#include"mov-decode-template.h"
#undef DATA_BYTE1
#undef DATA_BYTE2

#define DATA_BYTE1 2
#define DATA_BYTE2 4
#include"mov-decode-template.h"
#undef DATA_BYTE1
#undef DATA_BYTE2

