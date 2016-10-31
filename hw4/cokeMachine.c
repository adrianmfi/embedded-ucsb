#include <stdio.h>

typedef struct CokeMachineTag{
	int state;
}CokeMachine;

enum CokeMachineSignals{
	Q_SIG,
	CB_SIG,
	CD_SIG,
	CS_SIG,
	TAKE_SIG
};

enum CokeMachineStates{
	IDLE_STATE,
	ONEQ_STATE,
	TWOQ_STATE,
	DISPENSE_COKE_STATE,
	DISPENSE_DCOKE_STATE,
	DISPENSE_SPRITE_STATE
};


void cokeMachineInit(CokeMachine *me){
	me->state = IDLE_STATE;
}


void cokeMachineDispatch(CokeMachine *me, int event){
	switch(me->state){
		case IDLE_STATE:{
			switch(event){
				case Q_SIG:{
					me->state = ONEQ_STATE;
					printf("Changed state from IDLE_STATE to ONEQ_STATE\n");
				}
				case CB_SIG:{
					break;
				}
				case CD_SIG:{
					break;
				}
				case CS_SIG:{
					break;
				}
				case TAKE_SIG:{
					break;
				}
			}
			break;
		}
		case ONEQ_STATE:{
			switch(event){
				case Q_SIG:{
					me->state = TWOQ_STATE;
					printf("Changed state from ONEQ_STATE to TWOQ_STATE\n");
				}
				case CB_SIG:{
					break;
				}
				case CD_SIG:{
					break;
				}
				case CS_SIG:{
					break;
				}
				case TAKE_SIG:{
					break;
				}
			}
			break;
		}
		case TWOQ_STATE:{
			switch(event){
				case Q_SIG:{
					break;
				}
				case CB_SIG:{
					me->state = DISPENSE_COKE_STATE;
					printf("Changed state from TWOQ_STATE to DISPENSE_DCOKE_STATE\n");
					break;
				}
				case CD_SIG:{
					me->state = DISPENSE_DCOKE_STATE;
					printf("Changed state from TWOQ_STATE to DISPENSE_DCOKE_STATE\n");
					break;
				}
				case CS_SIG:{
					me->state = DISPENSE_SPRITE_STATE;
					printf("Changed state from TWOQ_STATE to DISPENSE_SPRITE_STATE\n");
					break;
				}
				case TAKE_SIG:{
					break;
				}
			}
			break;
		}
		case DISPENSE_COKE_STATE:{
			switch(event){
				case Q_SIG:{
					break;
				}
				case CB_SIG:{
					break;
				}
				case CD_SIG:{
					break;
				}
				case CS_SIG:{
					break;
				}
				case TAKE_SIG:{
					me->state = IDLE_STATE;
					printf("Changed state from DISPENSE_COKE_STATE to IDLE_STATE\n");
					break;
				}
			}
			break;
		}
		case DISPENSE_DCOKE_STATE:{
			switch(event){
				case Q_SIG:{
					break;
				}
				case CB_SIG:{
					break;
				}
				case CD_SIG:{
					break;
				}
				case CS_SIG:{
					break;
				}
				case TAKE_SIG:{
					me->state = IDLE_STATE;
					printf("Changed state from DISPENSE_DCOKE_STATE to IDLE_STATE\n");
					break;
				}
			}
			break;
		}		
		case DISPENSE_SPRITE_STATE:{
			switch(event){
				case Q_SIG:{
					break;
				}
				case CB_SIG:{
					break;
				}
				case CD_SIG:{
					break;
				}
				case CS_SIG:{
					break;
				}
				case TAKE_SIG:{
					me->state = IDLE_STATE;
					printf("Changed state from DISPENSE_SPRITE_STATE to IDLE_STATE\n");
					break;
				}
			}
			break;
		}
	}
}

static CokeMachine cokeM;

int main () {
	cokeMachineInit (&cokeM);
	for(;;){
		char input;
		printf ("Type in signal q, b, d, s, t \n");
		scanf (" %c", &input);
		switch (input){
			case 'q':{
				cokeMachineDispatch(&cokeM,Q_SIG);		
				break;
			}
			case 'b':{
				cokeMachineDispatch(&cokeM,CB_SIG);		
				break;
			}
			case 'd':{
				cokeMachineDispatch(&cokeM,CD_SIG);		
				break;
			}
			case 's':{
				cokeMachineDispatch(&cokeM,CS_SIG);		
				break;
			}
			case 't':{
				cokeMachineDispatch(&cokeM,TAKE_SIG);		
				break;
			}
		}

	}
}