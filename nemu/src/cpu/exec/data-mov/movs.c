#include"mov-helper.h"

#define DATA_BYTE1 1
#define DATA_BYTE2 2
#include"movs-template.h"
#undef DATA_BYTE1
#undef DATA_BYTE2

#define DATA_BYTE1 1
#define DATA_BYTE2 4
#include"movs-template.h"
#undef DATA_BYTE1
#undef DATA_BYTE2

#define DATA_BYTE1 2
#define DATA_BYTE2 4
#include"movs-template.h"
#undef DATA_BYTE1
#undef DATA_BYTE2

make_helper(movs_rm2r_b_l);
make_helper(movs_rm2r_b_w);
make_helper(movs_rm2r_w_l);
make_helper_mov_v(movs_rm2r_b)
