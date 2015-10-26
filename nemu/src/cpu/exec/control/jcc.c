#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"jcc-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"jcc-template.h"
#undef DATA_BYTE 

#define DATA_BYTE 4
#include"jcc-template.h"

make_helper(jcc_si_b);
make_helper(jcc_si_w);
make_helper(jcc_si_l);
make_helper_v(jcc_si)


