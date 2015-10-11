#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"call-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"call-template.h"
#undef DATA_BYTE

make_helper(call_si_l);
make_helper(call_si_w);
make_helper(call_si_b);
make_helper_v(call_si)
make_helper(call_rm_b);
make_helper(call_rm_w);
make_helper(call_rm_l);
make_helper_v(call_rm)

