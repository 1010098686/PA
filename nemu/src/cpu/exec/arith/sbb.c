#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"sbb-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"sbb-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"sbb-template.h"
#undef DATA_BYTE

make_helper(sbb_i2a_b);
make_helper(sbb_i2a_w);
make_helper(sbb_i2a_l);
make_helper_v(sbb_i2a)
make_helper(sbb_i2rm_b);
make_helper(sbb_i2rm_w);
make_helper(sbb_i2rm_l);
make_helper_v(sbb_i2rm)
make_helper(sbb_si2rm_w);
make_helper(sbb_si2rm_l);
make_helper_v(sbb_si2rm)
make_helper(sbb_r2rm_b);
make_helper(sbb_r2rm_w);
make_helper(sbb_r2rm_l);
make_helper_v(sbb_r2rm)
make_helper(sbb_rm2r_b);
make_helper(sbb_rm2r_w);
make_helper(sbb_rm2r_l);
make_helper_v(sbb_rm2r)

