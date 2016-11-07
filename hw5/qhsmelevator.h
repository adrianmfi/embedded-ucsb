#ifndef qhsmelevator_h
#define qhsmelevator_h
#define NUM_FLOORS 5

enum QHsmElevatorSignals {
    BTN_SIG = Q_USER_SIG,
    TICK_SIG
};

extern struct QHsmElevatorTag HSM_QHsmElevator;       /* the sole instance of QHsmElevator */

int getTick();
int getFloor();
double getAvg(int floor);


void QHsmElevator_ctor(void);              /* instantiate and initialize the HSM */

/* Board Support Package */
void BSP_display(char const *msg);
void BSP_exit(void);
void writeUp();
void writeStop(int T,int P, int PE, int F);
void writeDown();
#endif                                                         /* qhsmelevator_h */
