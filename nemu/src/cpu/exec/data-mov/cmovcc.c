#include"cpu/exec/helper.h"

#define DATA_BYTE 2
#include"cmovcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"cmovcc-template.h"
#undef DATA_BYTE

make_helper(cmovcc_rm2r_w);
make_helper(cmovcc_rm2r_l);
make_helper_v(cmovcc_rm2r)

