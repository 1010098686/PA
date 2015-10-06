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

make_helper(jump_i_b);
make_helper(jump_i_w);
make_helper(jump_i_l);
