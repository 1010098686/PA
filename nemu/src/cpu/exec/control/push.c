#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"push-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"push-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"push-template.h"
#undef DATA_BYTE

make_helper(push_r2rm_l);
make_helper(push_r2rm_w);
make_helper(push_r2rm_b);

