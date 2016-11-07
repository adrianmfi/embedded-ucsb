#include "qpn_port.h"
#include "qhsmelevator.h"
#include <stdio.h>

/* QHsmElevator class -----------------------------------------------------------*/
typedef struct QHsmElevatorTag {
    QHsm super;                                        /* extend class QHsm */
                                             /* extended state variables... */
    uint8_t recentFloor;
    uint8_t unassignedOrder[NUM_FLOORS];
    uint8_t assignedOrder[NUM_FLOORS];
    uint32_t curr_time;
    uint32_t timer_start; 

    uint32_t lastPressTimes[5];
    uint32_t totalPressTimes[5];
    uint32_t numPresses[5];

    int pplGoingOnAtFloor[5];
    int pplLeavingAtFloor[5];

} QHsmElevator;


void   QHsmElevator_ctor(void);                               /* the ctor */
static QState QHsmElevator_initial(QHsmElevator *me);  /* initial pseudostate-handler */
static QState QHsmElevator_top    (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_idle    (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_upStopped  (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_upMoving (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_downStopped  (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_downMoving (QHsmElevator *me);                  /* state-handler */

/* global objects ----------------------------------------------------------*/
QHsmElevator HSM_QHsmElevator;                /* the sole instance of the QHsmElevator HSM */


/* get functions-------- */
int getTick(){
	return HSM_QHsmElevator.curr_time;
}
int getFloor(){
	return HSM_QHsmElevator.recentFloor+1;
}
double getAvg(int floor){
	return (double)HSM_QHsmElevator.totalPressTimes[floor-1]/(double)HSM_QHsmElevator.numPresses[floor-1];
}

int pplInElevator(){
    int tot = 0;
    int i;
    for (i = 0; i < 5; i++){
        tot += HSM_QHsmElevator.pplLeavingAtFloor[i];
    }
    return tot;
}
int pplInSim(){
    int tot = 0;
    int i;
    for (i = 0; i < 5; i++){
        tot += HSM_QHsmElevator.pplGoingOnAtFloor[i];
    }
    tot += pplInElevator();
    return tot;
}
/*..........................................................................*/
void QHsmElevator_ctor(void) {
    QHsm_ctor(&HSM_QHsmElevator.super, (QStateHandler)&QHsmElevator_initial);
    HSM_QHsmElevator.recentFloor = 0;              /* initialize extended state variables */
    int i;
    for (i = 0; i < NUM_FLOORS; i++){
    	HSM_QHsmElevator.assignedOrder[NUM_FLOORS] = 0;
    	HSM_QHsmElevator.unassignedOrder[NUM_FLOORS] = 0;

	    HSM_QHsmElevator.lastPressTimes[i] = 0;
	    HSM_QHsmElevator.totalPressTimes[i] = 0;
	    HSM_QHsmElevator.numPresses[i] = 0;

        HSM_QHsmElevator.pplLeavingAtFloor[i] = 0;
        HSM_QHsmElevator.pplGoingOnAtFloor[i] = 0;
    }
    HSM_QHsmElevator.curr_time = 0;
    HSM_QHsmElevator.timer_start = -1;
}

/*..........................................................................*/
QState QHsmElevator_initial(QHsmElevator *me) {
    //BSP_display("top-INIT;");
    return Q_TRAN(&QHsmElevator_idle);
}
/*..........................................................................*/
QState QHsmElevator_top(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
          //  BSP_display("top-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            //BSP_display("top-EXIT;");
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            //BSP_display("top-INIT;");
            return Q_TRAN(&QHsmElevator_idle);
        }
        case BTN_SIG: {
        	me->unassignedOrder[Q_PAR(me)-1] = 1;
        	me->lastPressTimes[Q_PAR(me)-1] = me->curr_time;
            me->numPresses[Q_PAR(me)-1]++;
            //BSP_display("top-BUTTON;");
            return Q_HANDLED();
        }
        
        case TICK_SIG:{
            //BSP_display("top-TICK;");
            me->curr_time +=1;
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&QHsm_top);
}
/*..........................................................................*/
QState QHsmElevator_idle(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            //BSP_display("idle-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            //BSP_display("idle-EXIT;");
            return Q_HANDLED();
        }

        case BTN_SIG: {
            //BSP_display("idle-BUTTON;");
        	if (Q_PAR(me)-1 < me->recentFloor){
                if (!me->assignedOrder[Q_PAR(me-1)]  && !me->unassignedOrder[Q_PAR(me-1)]){
                me->lastPressTimes[Q_PAR(me)-1] = me->curr_time;
                me->numPresses[Q_PAR(me)-1]++;
                }
    			me->assignedOrder[Q_PAR(me)-1] = 1;
    			//printf("Moving down, time = %d\n", me->curr_time);
                me->pplLeavingAtFloor[Q_PAR(me)-1]++;
                writeStop(me->curr_time,pplInSim(),pplInElevator(),me->recentFloor);

        		return Q_TRAN(&QHsmElevator_downMoving);
        	}
        	else if (Q_PAR(me)-1 == me->recentFloor){
            	me->numPresses[Q_PAR(me)-1]++;

    			//printf("Opening doors, time = %d\n", me->curr_time);
        		return Q_TRAN(&QHsmElevator_upStopped);
        	}
        	else{
                if (!me->assignedOrder[Q_PAR(me-1)]  && !me->unassignedOrder[Q_PAR(me-1)]){
                
                me->lastPressTimes[Q_PAR(me)-1] = me->curr_time;
            	me->numPresses[Q_PAR(me)-1]++;
                }
                me->assignedOrder[Q_PAR(me)-1] = 1;
                me->pplLeavingAtFloor[Q_PAR(me)-1]++;
                writeStop(me->curr_time,pplInSim(),pplInElevator(),me->recentFloor);

    			//printf("Moving up, time = %d\n", me->curr_time);
        		return Q_TRAN(&QHsmElevator_upMoving);
        	}
        }
    }
    return Q_SUPER(&QHsmElevator_top);
}
/*..........................................................................*/
QState QHsmElevator_upMoving(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
        	me->timer_start = me->curr_time;
            //BSP_display("upMoving-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            //BSP_display("upMoving-EXIT;");
            return Q_HANDLED();
        }
        case BTN_SIG: {
            
            if(Q_PAR(me)-1 == me->recentFloor || Q_PAR(me)-1 == me->recentFloor+1)
                return Q_HANDLED();
            if (!me->assignedOrder[Q_PAR(me-1)]  && !me->unassignedOrder[Q_PAR(me-1)]){
               me->lastPressTimes[Q_PAR(me)-1] = me->curr_time;
               me->numPresses[Q_PAR(me)-1]++;
                me->pplGoingOnAtFloor[Q_PAR(me)-1]++;
                writeUp(me->curr_time,pplInSim(),pplInElevator(),me->recentFloor);
    		
            }	
        	me->unassignedOrder[Q_PAR(me)-1] = 1;
            //BSP_display("top-BUTTON;");
            return Q_HANDLED();
        }
        case TICK_SIG: {
            //BSP_display("upMoving-TICK;");
            me->curr_time += 1;
            if(me->curr_time == me->timer_start + 5){ //Floor reached
            	me->recentFloor += 1;
            	//assign
	        	int i;
	        	for (i = me-> recentFloor; i < NUM_FLOORS; i++){
	        		if(me->unassignedOrder[i]){
	        			me->assignedOrder[i] = 1;
	        			me->unassignedOrder[i] = 0;
	        		} 
	        	}
            	if(me->assignedOrder[me->recentFloor]){
            		me->assignedOrder[me->recentFloor] = 0;
            		me->totalPressTimes[me->recentFloor] += me->curr_time-me->lastPressTimes[me->recentFloor];
                    me->pplLeavingAtFloor[me->recentFloor]=me->pplGoingOnAtFloor[me->recentFloor];
                    me->pplGoingOnAtFloor[me->recentFloor] = 0;
                writeUp(me->curr_time,pplInSim(),pplInElevator(),me->recentFloor);
            		
        			//printf("Opening doors, time = %d\n", me->curr_time);
            		return Q_TRAN(&QHsmElevator_upStopped);
            	}
            	else{
            		return Q_TRAN(&QHsmElevator_upMoving);
            	}
            }
            return Q_HANDLED();
        }
	}
    return Q_SUPER(&QHsmElevator_top);
}

/*..........................................................................*/
QState QHsmElevator_upStopped(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            //BSP_display("upStopped-ENTRY;");
        	me->timer_start = me->curr_time;
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            //BSP_display("upStopped-EXIT;");
            return Q_HANDLED();
        }

        case TICK_SIG:{
            //BSP_display("upStopped-TICK;");
            me->curr_time += 1;
        	//assign orders
        	int i;
        	for (i = me-> recentFloor; i < NUM_FLOORS; i++){
        		if(me->unassignedOrder[i]){
        			me->assignedOrder[i] = 1;
        			me->unassignedOrder[i] = 0;
        		} 
        	}
        	//next transition
        	if(me->assignedOrder[me->recentFloor]){
        		me->assignedOrder[me->recentFloor] = 0;
        		return Q_TRAN(&QHsmElevator_upStopped);
        	}
            if(me->curr_time == me->timer_start + 10){
            	for(i = me->recentFloor; i < NUM_FLOORS; i++){
            		if(me->assignedOrder[i]){
		    			//printf("Moving up, time = %d\n", me->curr_time);
        				return Q_TRAN(&QHsmElevator_upMoving);
            		}
            	}
	        	for(i = me->recentFloor-1; i >= 0; i--){
            		if(me->unassignedOrder[i]){
		       			me->assignedOrder[i] = 1;
        				me->unassignedOrder[i] = 0;
		    			//printf("Moving down, time = %d\n", me->curr_time);

        				return Q_TRAN(&QHsmElevator_downMoving);
            		}
            	}
				return Q_TRAN(&QHsmElevator_idle);            			
            }
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&QHsmElevator_top);
}
/*..........................................................................*/
QState QHsmElevator_downMoving(QHsmElevator *me) {
   switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
        	me->timer_start = me->curr_time;
            //BSP_display("downMoving-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            //BSP_display("downMoving-EXIT;");
            return Q_HANDLED();
        }
        case BTN_SIG: {
        	if(Q_PAR(me)-1 == me->recentFloor || Q_PAR(me)-1 == me->recentFloor-1)
        		return Q_HANDLED();
            if (!me->assignedOrder[Q_PAR(me-1)]  && !me->unassignedOrder[Q_PAR(me-1)]){
      		me->lastPressTimes[Q_PAR(me)-1] = me->curr_time;
        	me->numPresses[Q_PAR(me)-1]++;
                me->pplGoingOnAtFloor[Q_PAR(me)-1]++;
                
            }
            me->unassignedOrder[Q_PAR(me)-1] = 1;
            //BSP_display("top-BUTTON;");
            return Q_HANDLED();
        }
        case TICK_SIG: {
            //BSP_display("downMoving-TICK;");
            me->curr_time += 1;
            if(me->curr_time == me->timer_start + 5){ //Floor reached
            	me->recentFloor -= 1;
            	//assign
	        	int i;
	        	for (i = 0; i <= me->recentFloor; i++){
	        		if(me->unassignedOrder[i]){
	        			me->assignedOrder[i] = 1;
	        			me->unassignedOrder[i] = 0;
	        		} 
	        	}
            	if(me->assignedOrder[me->recentFloor]){
            		me->assignedOrder[me->recentFloor] = 0;
            		me->totalPressTimes[me->recentFloor] += me->curr_time-me->lastPressTimes[me->recentFloor];
	    			//printf("Opening doors, time = %d\n", me->curr_time);
                    me->pplLeavingAtFloor[me->recentFloor]=me->pplGoingOnAtFloor[me->recentFloor];
            		me->pplGoingOnAtFloor[me->recentFloor] = 0;
                writeDown(me->curr_time,pplInSim(),pplInElevator(),me->recentFloor);
                   
                    return Q_TRAN(&QHsmElevator_downStopped);
            	}
            	else{
            		return Q_TRAN(&QHsmElevator_downMoving);
            	}
	        }
    		return Q_HANDLED();
    	}
    }
    return Q_SUPER(&QHsmElevator_top);
}
/*..........................................................................*/
QState QHsmElevator_downStopped(QHsmElevator *me) {
     switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            //BSP_display("downStopped-ENTRY;");
        	me->timer_start = me->curr_time;
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            //BSP_display("downStopped-EXIT;");
            return Q_HANDLED();
        }
        case TICK_SIG:{
            //BSP_display("downStopped-TICK;");
            me->curr_time += 1;
        	//assign orders
        	int i;
        	for (i = 0; i <= me-> recentFloor; i++){
        		if(me->unassignedOrder[i]){
        			me->assignedOrder[i] = 1;
        			me->unassignedOrder[i] = 0;
        		} 
        	}
        	//next transition
        	if(me->assignedOrder[me->recentFloor]){
        		me->assignedOrder[me->recentFloor] = 0;
        		return Q_TRAN(&QHsmElevator_downStopped);
        	}
            if(me->curr_time == me->timer_start + 10){
            	for(i = 0; i < me->recentFloor; i++){
            		if(me->assignedOrder[i]){
		    			//printf("Moving down, time = %d\n", me->curr_time);
        				return Q_TRAN(&QHsmElevator_downMoving);
            		}
            	}
	        	for(i = me->recentFloor+1; i < NUM_FLOORS; i++){
            		if(me->unassignedOrder[i]){
		       			me->assignedOrder[i] = 1;
        				me->unassignedOrder[i] = 0;
		    			//printf("Moving up, time = %d\n", me->curr_time);
        				return Q_TRAN(&QHsmElevator_upMoving);
            		}
            	}
				return Q_TRAN(&QHsmElevator_idle);            			
            }
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&QHsmElevator_top);
}
