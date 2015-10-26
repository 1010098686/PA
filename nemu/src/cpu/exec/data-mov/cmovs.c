#include"cpu/exec/helper.h"

#define DATA_BYTE 2
#include"cmovs-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"cmovs-template.h"
#undef DATA_BYTE

make_helper(cmovs_rm2r_w);
make_helper(cmovs_rm2r_l);
make_helper_v(cmovs_rm2r)
