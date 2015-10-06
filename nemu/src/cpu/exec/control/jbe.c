#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"jbe-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"jbe-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"jbe-template.h"
#undef DATA_BYTE

make_helper(jbe_si_b);
make_helper(jbe_si_w);
make_helper(jbe_si_l);
make_helper_v(jbe_si)

