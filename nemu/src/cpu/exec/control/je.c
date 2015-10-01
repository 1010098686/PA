#include"cpu/exec/helper.h"

#define DATA_BYTE 1
#include"je-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include"je-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include"je-template.h"
#undef DATA_BYTE

make_helper(je_si_b);
make_helper(je_si_w);
make_helper(je_si_l);

