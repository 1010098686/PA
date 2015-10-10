#include"cpu/exec/helper.h"

#if DATA_BYTE1 == 1
#define SUFFIX1 b
#define DATA_TYPE1 uint8_t 
#define DATA_TYPE1_S int8_t 

#elif DATA_BYTE1 == 2
#define SUFFIX1 w
#define DATA_TYPE1 uint16_t
#define DATA_TYPE1_S int16_t 

#elif DATA_BYTE1 ==4
#define SUFFIX1 l
#define DATA_TYPE1 uint32_t 
#define DATA_TYPE1_S int32_t 

#else 
#error unkonwn DATA_BYTE1
#endif

#if DATA_BYTE2 ==1
#define SUFFIX2 b
#define DATA_TYPE2 uint8_t 
#define DATA_BYTE2_S int8_t 

#elif DATA_BYTE2 == 2
#define SUFFIX2 w
#define DATA_TYPE2 uint16_t 
#define DATA_TYPE2_S int16_t 

#elif DATA_BYTE2 ==4
#define SUFFIX2 l
#define DATA_TYPE2 uint32_t 
#define DATA_TYPE2_S int32_t 

#else 
#error unknown DATA_BYTE2
#endif

#define REG_mov(index) concat(reg_,SUFFIX2) (index)
#define REG_NAME_mov(index) concat(regs,SUFFIX2) [index]

#define MEM_R_mov(addr) swaddr_read(addr,DATA_BYTE1)
#define MEM_W_mov(addr,data) swaddr_write(addr,DATA_BYTE2,data)

#define OPERAND_W_mov(op,src) concat(write_operand_,SUFFIX2) (op,src)

#define MSB_mov(n) ((DATA_TYPE1)(n) >> ((DATA_BYTE1<<3)-1))
