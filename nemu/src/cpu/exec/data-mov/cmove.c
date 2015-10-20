#include"cpu/exec/helper.h"

#define DATA_BYTE 2
#include"cmove-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"cmove-template.h"
#undef DATA_BYTE

make_helper(cmove_rm2r_w);
make_helper(cmove_rm2r_l);
make_helper_v(cmove_rm2r)
