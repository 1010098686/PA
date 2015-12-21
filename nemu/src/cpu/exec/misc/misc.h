#ifndef __MISC_H__
#define __MISC_H__

make_helper(nop);
make_helper(int3);
make_helper(lea);
make_helper(leave);
make_helper(ret);
make_helper(cltd);
make_helper(cld);
make_helper(lgdt);
make_helper(ljmp);
make_helper(std);
make_helper(lidt);
make_helper(INT);
make_helper(pusha);
make_helper(popa);
make_helper(iret);
#endif
