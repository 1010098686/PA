#include "cpu/exec/helper.h"

#define DATA_BYTE 1
#include "crmov-template.h"
#undef DATA_BYTE

#define DATA_BYTE 2
#include "crmov-template.h"
#undef DATA_BYTE

#define DATA_BYTE 4
#include "crmov-template.h"
#undef DATA_BYTE

make_helper(crmov_r2rm_l);
make_helper(crmov_rm2r_l);


