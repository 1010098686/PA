#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"pop-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"pop-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"pop-template.h"
#undef DATA_BYTE

make_helper(pop_r_b);
make_helper(pop_r_w);
make_helper(pop_r_l);
make_helper(pop_rm_b);
make_helper(pop_rm_w);
make_helper(pop_rm_l);
make_helper_v(pop_rm)
make_helper_v(pop_r)
