#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cache_model.h"

#define NR_TESTS 500000

int main(int argc, char const *argv[])
{
	int cmax = 0;
	srand(time(0));
	cm_init();
	cm_enable_cache();
	for (int i = 0; i < NR_TESTS; i++){
		int address = (rand() % CM_ADDRESS_SPACE_SIZE );
		cm_do_access(address);
		int cycles = cm_get_last_access_cycles();
		if (cycles > cmax){
			cmax = cycles;
			printf("max found with cache enabled, val = %d\n", cmax);
		}
	}
	cm_disable_cache();
	for (int i = 0; i < NR_TESTS; i++){
		int address = (rand() % CM_ADDRESS_SPACE_SIZE );
		cm_do_access(address);
		int cycles = cm_get_last_access_cycles();
		if (cycles > cmax){
			cmax = cycles;
			printf("max found with cache disabled, val = %d\n", cmax);
		}
	}
	return 0;
}