#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"ja-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"ja-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"ja-template.h"
#undef DATA_BYTE

make_helper(ja_si_b);
make_helper(ja_si_w);
make_helper(ja_si_l);
make_helper_v(ja_si)

