#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"jg-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"jg-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"jg-template.h"
#undef DATA_BYTE

make_helper(jg_si_b);
make_helper(jg_si_w);
make_helper(jg_si_l);
make_helper_v(jg_si)

