#include"cpu/helper.h"
#include"mov-decode.h"

#define make_helper_mov_v(name) \
	make_helper(concat(name,_v)) \
       { \
		   return (ops_decoded.is_data_size_16? concat(name,_w):concat(name,_l)) (eip);\
	   }

#define do_mov_execute concat6(do_,instr,_,SUFFIX1,_,SUFFIX2)

#define make_instr_helper_mov(type) \
	make_helper(concat7(instr, _, type,_,SUFFIX1,_,SUFFIX2))\
       {\
		   return idex(eip,concat6(decode_,type,_,SUFFIX1,_,SUFFIX2),do_mov_execute);\
	   }
extern char assemly[];
#define print_asm_mov(...)
#define print_asm_template2_mov()\
	print_asm_mov(str(instr) str(SUFFIX1) str(SUFFIX2),"%s, %s",op_src->str,op_dest->str)
