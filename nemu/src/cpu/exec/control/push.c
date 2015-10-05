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

make_helper(push_r_l);
make_helper(push_r_w);
make_helper(push_r_b);
make_helper(push_rm_b);
make_helper(push_rm_w);
make_helper(push_rm_l);
make_helper(push_i_b);
make_helper(push_i_w);
make_helper(push_i_l);
make_helper_v(push_rm)
