#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"cmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"cmp-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"cmp-template.h"
#undef DATA_BYTE

make_helper(cmp_si2rm_l);
make_helper(cmp_si2rm_w);
make_helper_v(cmp_si2rm)
