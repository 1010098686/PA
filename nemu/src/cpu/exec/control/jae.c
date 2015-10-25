#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"jae-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"jae-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"jae-template.h"
#undef DATA_BYTE

make_helper(jae_si_b);
make_helper(jae_si_w);
make_helper(jae_si_l);
make_helper_v(jae_si)

