#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"jle-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"jle-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"jle-template.h"
#undef DATA_BYTE

make_helper(jle_si_b);
make_helper(jle_si_w);
make_helper(jle_si_l);
make_helper_v(jle_si)
