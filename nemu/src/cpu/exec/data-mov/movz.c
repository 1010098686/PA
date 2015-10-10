#include"mov-helper.h"

#define DATA_BYTE1 1
#define DATA_BYTE2 2
#include"movz-template.h"
#undef DATA_BYTE1
#undef DATA_BYTE2

#define DATA_BYTE1 1
#define DATA_BYTE2 4
#include"movz-template.h"
#undef DATA_BYTE1
#undef DATA_BYTE2

#define DATA_BYTE1 2
#define DATA_BYTE2 4
#include"movz-template.h"
#undef DATA_BYTE1
#undef DATA_BYTE2

make_helper(movz_rm2r_b_l);
make_helper(movz_rm2r_b_w);
make_helper(movz_rm2r_w_l);
make_helper_mov_v(movz_rm2r_b)

