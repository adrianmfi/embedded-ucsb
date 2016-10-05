#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cache_model.h"

#define SAMPLE_SIZE 500000
#define RESAMPLE_SIZE 1000
#define RESAMPLE_TIMES 40	

int compare_function(const void *a,const void *b) {
	double *x = (double *) a;
	double *y = (double *) b;
	if (*x < *y) return -1;
	else if (*x > *y) return 1; 
	return 0;
}

void mean1a(){
	srand(time(0));
	cm_init();
	cm_enable_cache();
	int samples[SAMPLE_SIZE];
	double resample_means[RESAMPLE_TIMES];

	for (int i = 0; i < SAMPLE_SIZE; i++){
		int address = (rand() % CM_ADDRESS_SPACE_SIZE );
		cm_do_access(address); 
		samples[i] = cm_get_last_access_cycles();
	}
	for (int i = 0; i < RESAMPLE_TIMES; i++){
		int resample_sum = 0;
		for (int j = 0; j < RESAMPLE_SIZE; j++){
			resample_sum += samples[rand() % SAMPLE_SIZE];
		}
		resample_means[i] = (double)resample_sum / (double)RESAMPLE_SIZE;
	}
	qsort(resample_means,RESAMPLE_TIMES,sizeof(double),compare_function);
	for(int i = 0; i < RESAMPLE_TIMES; i++){
		printf("%lf\n", resample_means[i]);
	}
	printf("Lower percentile limit %lf, upper percentile %lf\n", resample_means[2], resample_means[37]);

}
void mean1b(){
	srand(time(0));
	cm_init();
	cm_disable_cache();
	int samples[SAMPLE_SIZE];
	double resample_means[RESAMPLE_TIMES];

	int address = (rand() % CM_ADDRESS_SPACE_SIZE );
	for (int i = 0; i < SAMPLE_SIZE; i++){
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
		samples[i] = cm_get_last_access_cycles();
	}
	for (int i = 0; i < RESAMPLE_TIMES; i++){
		int resample_sum = 0;
		for (int j = 0; j < RESAMPLE_SIZE; j++){
			resample_sum += samples[rand() % SAMPLE_SIZE];
		}
		resample_means[i] = (double)resample_sum / (double)RESAMPLE_SIZE;
	}
	qsort(resample_means,RESAMPLE_TIMES,sizeof(double),compare_function);
	for(int i = 0; i < RESAMPLE_TIMES; i++){
		printf("%lf\n", resample_means[i]);
	}
	printf("Lower 25 percentile limit %lf, upper 25 percentile %lf\n", resample_means[2], resample_means[37]);
}
int main(int argc, char const *argv[])
{
	mean1a();
	return 0;

}