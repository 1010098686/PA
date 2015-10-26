#include"cpu/exec/helper.h"


#define DATA_BYTE 1
#include"setcc-template.h"
#undef DATA_BYTE


make_helper(setcc_rm_b);
