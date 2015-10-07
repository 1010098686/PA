#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"sub-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"sub-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"sub-template.h"
#undef DATA_BYTE

make_helper(sub_i2rm_w);
make_helper(sub_i2rm_l);
make_helper(sub_i2rm_b);
make_helper_v(sub_i2rm)
make_helper(sub_si2rm_l);
make_helper(sub_si2rm_w);
make_helper_v(sub_si2rm)
make_helper(sub_i2a_b);
make_helper(sub_i2a_w);
make_helper(sub_i2a_l);
make_helper_v(sub_i2a)
make_helper(sub_r2rm_b);
make_helper(sub_r2rm_w);
make_helper(sub_r2rm_l);
make_helper_v(sub_r2rm)
make_helper(sub_rm2r_b);
make_helper(sub_rm2r_w);
make_helper(sub_rm2r_l);
make_helper_v(sub_rm2r)
