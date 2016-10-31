#ifndef qhsmelevator_h
#define qhsmelevator_h

enum QHsmElevatorSignals {
    A_SIG = Q_USER_SIG,
    B_SIG,
    C_SIG,
    D_SIG,
    E_SIG,
    F_SIG,
    G_SIG,
    H_SIG,
    I_SIG,
    TERMINATE_SIG,
    IGNORE_SIG,
    MAX_SIG
};

extern struct QHsmElevatorTag HSM_QHsmElevator;       /* the sole instance of QHsmElevator */

void QHsmElevator_ctor(void);              /* instantiate and initialize the HSM */

/* Board Support Package */
void BSP_display(char const *msg);
void BSP_exit(void);

#endif                                                         /* qhsmelevator_h */
