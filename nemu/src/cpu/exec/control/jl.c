#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"jl-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"jl-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"jl-template.h"
#undef DATA_BYTE

make_helper(jl_si_b);
make_helper(jl_si_w);
make_helper(jl_si_l);
make_helper_v(jl_si)
