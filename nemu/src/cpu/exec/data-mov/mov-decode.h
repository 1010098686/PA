#include"cpu/helper.h"

make_helper(decode_rm2r_b_w);
make_helper(decode_rm2r_b_l);
make_helper(decode_rm2r_w_l);

void write_operand_b(Operand*,uint8_t);
void write_operand_w(Operand*,uint16_t);
void write_operand_l(Operand*,uint32_t);

