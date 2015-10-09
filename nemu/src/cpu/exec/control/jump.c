#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"jump-template.h"
#undef DATA_BYTE 

#define DATA_BYTE 2
#include"jump-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"jump-template.h"
#undef DATA_BYTE

make_helper(jump_si_b);
make_helper(jump_si_w);
make_helper(jump_si_l);
make_helper(jump_rm_w);
make_helper(jump_rm_l);
make_helper_v(jump_si);
make_helper_v(jump_rm)
