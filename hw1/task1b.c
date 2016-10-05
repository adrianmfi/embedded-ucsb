#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cache_model.h"

#define NR_TESTS 500000

int main(int argc, char const *argv[])
{
	//Setup model and variables
	int sum = 0;
	srand(time(0));
	cm_init();
	cm_enable_cache();
	int address = (rand() % CM_ADDRESS_SPACE_SIZE );
	for (int i = 0; i < NR_TESTS; i++){
		//Generate next access
		int p = rand() % 100;
		if (p < 60){
			address = address + 1;
		}
		else if (p < 95){
			address = address + rand()%80 - 40;
			if(address < 0){
				address += 40;
			}
			if(address >= CM_ADDRESS_SPACE_SIZE){
				address -= 40;
			}

		}
		else if (p < 100){
			address = rand();
		}
		address = address %CM_ADDRESS_SPACE_SIZE;

		cm_do_access(address);
		int cycles = cm_get_last_access_cycles();
		sum += cycles;
	}
	printf("avg %f\n", (float)sum/(float)NR_TESTS);
	return 0;
}