#include <stdio.h>
#include <stdlib.h>
#include "kmp.h"


int main(int argc, char *argv[]) {
	char *a = "aaaab";
	char *b = "aaasss8baaaab";
	int ak[10] = {0};
	int pos =  Index_KMP(b,a,0);
	printf("pos = %d\n",pos);
	return 0;
}
