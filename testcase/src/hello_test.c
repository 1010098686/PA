#include <stdio.h>
#include <string.h>
#include "trap.h"

char buf[128];

/* This function is defined only to make the newlibc linkable.
 * Without it, errors will be reported during linking.
 * But the execution flow should not reach here.
 */
void *sbrk(int incr) {
	nemu_assert(0);
	return NULL;
}

int main() {
	sprintf(buf, "%s", "   \n");
	nemu_assert(strcmp(buf, "   \n") == 0);

	

	HIT_GOOD_TRAP;
	return 0;
}
