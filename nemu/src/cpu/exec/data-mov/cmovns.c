#include"cpu/exec/helper.h"

#define DATA_BYTE 2
#include"cmovns-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"cmovns-template.h"
#undef DATA_BYTE

make_helper(cmovns_rm2r_w);
make_helper(cmovns_rm2r_l);
make_helper_v(cmovns_rm2r)
