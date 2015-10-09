#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"jge-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"jge-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"jge-template.h"
#undef DATA_BYTE

make_helper(jge_si_b);
make_helper(jge_si_w);
make_helper(jge_si_l);
make_helper_v(jge_si)
