#include "cpu/exec/helper.h"

make_helper(exec);

make_helper(rep) {
	int len;
	int count = 0;
	int opcode=ops_decoded.opcode;
	//printf("%x\n",opcode);
	if(instr_fetch(eip + 1, 1) == 0xc3) {
		/* repz ret */
		exec(eip + 1);
		len = -1;
	}
	else {
		while(cpu.ecx) {
			exec(eip + 1);
			count ++;
			cpu.ecx --;
			//printf("%x\n",ops_decoded.opcode);
			assert(ops_decoded.opcode == 0xa4	// movsb
				|| ops_decoded.opcode == 0xa5	// movsw
				|| ops_decoded.opcode == 0xaa	// stosb
				|| ops_decoded.opcode == 0xab	// stosw
				|| ops_decoded.opcode == 0xa6	// cmpsb
				|| ops_decoded.opcode == 0xa7	// cmpsw
				|| ops_decoded.opcode == 0xae	// scasb
				|| ops_decoded.opcode == 0xaf	// scasw
				);

			/* TODO: Jump out of the while loop if necessary. */
			if(ops_decoded.opcode==0xa6 || ops_decoded.opcode==0xa7 || ops_decoded.opcode==0xae || ops_decoded.opcode==0xaf) //cmpsb cmpsw scasb scasw
			{
			  if(opcode==0xf2 && cpu.eflags.ZF==0) break; //repnz repne
			  if(opcode==0xf3 && cpu.eflags.ZF==1) break; //rep repe repz
			}
		}
		len = 1;
	}

#ifdef DEBUG
	char temp[80];
	sprintf(temp, "rep %s", assembly);
	sprintf(assembly, "%s[cnt = %d]", temp, count);
#endif
	
	return len + 1;
}
