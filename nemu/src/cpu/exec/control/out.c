#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "out-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "out-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "out-template.h"
#undef DATA_BYTE

make_helper(out_i2a_b);
make_helper(out_i2a_w);
make_helper(out_i2a_l);
make_helper_v(out_i2a)
make_helper(out_rm2r_b);
make_helper(out_rm2r_w);
make_helper(out_rm2r_l);
make_helper_v(out_rm2r)
