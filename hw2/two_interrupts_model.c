#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RND (rand()/(double )RAND_MAX)
#define BINS 10
#define CYCLES 1000000
#define INTERRUPTS 3
#define HIST_WIDTH 4

struct {
  double prob;  /* Probability of interrupt occurence */
  int priority; /* Interrupt Priority - higher number => higher priority */ 
  int run_time_left; /* Time to service the interrupt */
  int start_time; /* Start time for the interrupt routine */ 
  int arrive_time_present; /* Arrive time for the interrupt currently being serviced */
  int arrive_time_next; /* Arrive time for the interrupt in queue */
  int active; /* active = 1 => Current interrupt is being serviced */
  int missed; /* Stores the count of missed interrupts */
  int pending; /* pending = 1 => Current interrupt is in queue, some other interrupt is active */
  int max_latency;
  int preempted;
} inter[INTERRUPTS] = {
  {.prob = 0.1, .priority = 1, .run_time_left = 3, .active = 0, .missed = 0, .pending = 0, .max_latency = 3, .preempted = 0 },
  {.prob = 0.003, .priority = 2, .run_time_left = 5, .active = 0, .missed = 0, .pending = 0, .max_latency = 5, .preempted = 0 },
  {.prob = 0.001, .priority = 3, .run_time_left = 7, .active = 0, .missed = 0, .pending = 0, .max_latency =7, .preempted = 0}
};

int hist_data[BINS][INTERRUPTS]; /* Stores histogram data for each interrupt */
void histogram(int inter_no, int val); /* Puts val in the right bin for interrupt inter_no */
int clock_time = 0;

main() {
	int tot_serv_time_0 = 0;
	int tot_serv_time_1 = 0;
	int tot_serv_time_2 = 0;
	int num_interrupts_0 = 0;
	int num_interrupts_1 = 0;
	int num_interrupts_2 = 0;

	int fire;
	int trigger[INTERRUPTS];
  	int i, j, active, pending, priority;
  	time_t seconds;
  
  	seconds = time(NULL);

  	srand(seconds);

  	while (clock_time < CYCLES) {
    	/* who is requested */
    	for (i=0; i< INTERRUPTS; i++) trigger[i] = (inter[i].prob > RND)?1:0;

    	/* who is active (only one can be active at a time!) */
    	active = -1; for (i=0; i<INTERRUPTS; i++) if (inter[i].active == 1) active = i;
    
	    /* who got missed */
	    for (i=0; i<INTERRUPTS; i++)
			if (inter[i].pending == 1 && trigger[i] == 1) inter[i].missed++;

    	/* who is pending */
    	for (i=0; i<INTERRUPTS; i++)
        	if (active != -1 && trigger[i] == 1 && (inter[i].pending !=1)) {
				inter[i].pending = 1; 
				inter[i].arrive_time_next = clock_time;
			}

    	/* highest priority pending */
    	pending = -1; 
    	for (i=priority=0; i<INTERRUPTS; i++) 
			if (inter[i].pending && (priority < inter[i].priority)) {
				pending = i; 
				priority = inter[i].priority;
	 		}
	 	int firedmax = -1
		for (i=priority=0; i<INTERRUPTS; i++) 
			if (inter[i].pending && (priority < inter[i].priority)) {
				pending = i; 
				priority = inter[i].priority;
	 		}
	 	
		int preempted = -1;
		int i = 0;
		for (; i < INTERRUPTS; i++){
			if (inter[i].preempted && inter[i].priority > inter[pending].priority)
				preempted == i;
		}
    	/* who becomes active (only one can be active at a time!) */
    	if (active != -1) /* somebody is active */{
      		
			if (inter[active].run_time_left <= clock_time - inter[active].start_time) { /* somebody has finished executing */ inter[active].run_time_left = inter[active].max_latency;
				inter[active].active = 0;
				histogram(active, clock_time-inter[active].arrive_time_present);
				/**********/
				if(active == 0){
					num_interrupts_0 += 1;
					tot_serv_time_0 += clock_time-inter[active].start_time;
				}else if (active == 1){
					num_interrupts_1 += 1;
					tot_serv_time_1 += clock_time-inter[active].start_time;
				}else if(active == 2){
					num_interrupts_2 += 1;
					tot_serv_time_2 += clock_time-inter[active].start_time;
				}
				/**********/
				if (preempted != -1 && inter[preempted].priority >= inter[pending].priority){
					inter[preempted].preempted = 0;
					inter[preempted].active = 1;
				}
				else if (pending != -1) { /* Highest priority pending interrupt is made active */
	  				inter[pending].active = 1;
	  				inter[pending].start_time = clock_time;
	  				inter[pending].pending = 0;
	  				inter[pending].arrive_time_present = inter[pending].arrive_time_next;
	  			}
			}
			/*Interrupt nest*/
			else if (inter[pending].priority > inter[active].priority){
  				printf("%d interrupted %d\n", pending,active);

  				inter[active].active = 0; 
  				inter[active].preempted = 1;
  				inter[active].run_time_left -= clock_time - inter[active].start_time;
				
				inter[pending].active = 1;
  				inter[pending].start_time = clock_time;
  				inter[pending].pending = 0;
			
			}
		}
		else { /* nobody is active */
			fire = -1; /* find highest priority triggered interrupt */
			for (i = priority = 0; i<INTERRUPTS; i++)
	  		if ((trigger[i] == 1) && (priority < inter[i].priority)) { /* Found someone with a higher priority */
            	if (fire != -1) { /* Make the lower priority interrupt pending */
					inter[fire].pending = 1; 
					inter[fire].arrive_time_next=clock_time;
				}
	    	fire = i; 
	    	priority = inter[i].priority;
	  	}
	 	if (fire != -1) { /*somebody was triggered */
	   	/* fire the interrupt with the highest priority */
	   		inter[fire].active = 1;
	   		inter[fire].start_time = clock_time;
	   		inter[fire].arrive_time_present = clock_time;
		}
  	}
    clock_time++;
}

	//prints data for all interrupts
	for (i=0; i<INTERRUPTS; i++){
       printf("Number of missed interrupt %d's: %d\n",i,inter[i].missed);
	   printf("Max latency for interrupt %d: %d\n",i,inter[i].max_latency);
	   printf("Histogram data for interrupt %d\n",i);
	   for (j=0; j<BINS; j++) printf("Bin %d count: %d\n",j,hist_data[j][i]);
	   printf("\n");
	}
	printf("Interrupt 0 occured %d times, with total service time %d\n", num_interrupts_0,tot_serv_time_0);
	printf("average service  time is then %f\n", (double)tot_serv_time_0/(double)num_interrupts_0);
	printf("Interrupt 1 occured %d times, with total service time %d\n", num_interrupts_1,tot_serv_time_1);
	printf("average service  time is then %f\n", (double)tot_serv_time_1/(double)num_interrupts_1);
	printf("Interrupt 2 occured %d times, with total service time %d\n", num_interrupts_2,tot_serv_time_2);
	printf("average service  time is then %f\n", (double)tot_serv_time_2/(double)num_interrupts_2);
}

void histogram(int inter_no , int val){

	int min, max, binSize, binIndex;

	//min and max initialized
	min = inter[inter_no].run_time_left;
	max = (inter[inter_no].run_time_left)*HIST_WIDTH;

	binSize = (max - min)/BINS;

	//Bin number is found here
	
		binIndex = 0;
		if (binSize > 0) {
			binIndex = (val - min)/binSize;
			if (binIndex == BINS) binIndex-- ;
			hist_data[binIndex][inter_no]++;
		}
		else hist_data[0][inter_no]++;

		if (val > inter[inter_no].max_latency) inter[inter_no].max_latency = val;

}
