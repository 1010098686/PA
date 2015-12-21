#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include "in-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "in-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "in-template.h"
#undef DATA_BYTE

make_helper(in_i2a_b);
make_helper(in_i2a_w);
make_helper(in_i2a_l);
make_helper_v(in_i2a)
make_helper(in_rm2r_b);
make_helper(in_rm2r_w);
make_helper(in_rm2r_l);
make_helper_v(in_rm2r)
