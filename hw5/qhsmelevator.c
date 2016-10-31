#include "qpn_port.h"
#include "qhsmelevator.h"

/* QHsmElevator class -----------------------------------------------------------*/
typedef struct QHsmElevatorTag {
    QHsm super;                                        /* extend class QHsm */
                                             /* extended state variables... */
    uint8_t foo;
} QHsmElevator;

void   QHsmElevator_ctor(void);                               /* the ctor */
static QState QHsmElevator_initial(QHsmElevator *me);  /* initial pseudostate-handler */
static QState QHsmElevator_s    (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_s1   (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_s11  (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_s111 (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_s2   (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_s21  (QHsmElevator *me);                  /* state-handler */
static QState QHsmElevator_s211 (QHsmElevator *me);                  /* state-handler */

/* global objects ----------------------------------------------------------*/
QHsmElevator HSM_QHsmElevator;                /* the sole instance of the QHsmElevator HSM */

/*..........................................................................*/
void QHsmElevator_ctor(void) {
    QHsm_ctor(&HSM_QHsmElevator.super, (QStateHandler)&QHsmElevator_initial);
    HSM_QHsmElevator.foo = 0;              /* initialize extended state variable */
}

/*..........................................................................*/
QState QHsmElevator_initial(QHsmElevator *me) {
    BSP_display("top-INIT;");
    return Q_TRAN(&QHsmElevator_s2);
}
/*..........................................................................*/
QState QHsmElevator_s(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            BSP_display("s-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            BSP_display("s-EXIT;");
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            BSP_display("s-INIT;");
            return Q_TRAN(&QHsmElevator_s111);
        }
        case E_SIG: {
            BSP_display("s-E;");
            return Q_TRAN(&QHsmElevator_s111);
        }
        case I_SIG: {                   /* internal transition with a guard */
            if (me->foo) {
                BSP_display("s-I;");
                me->foo = 0;
                return Q_HANDLED();
            }
            break;
        }
        case TERMINATE_SIG: {
            BSP_exit();
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&QHsm_top);
}
/*..........................................................................*/
QState QHsmElevator_s1(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            BSP_display("s1-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            BSP_display("s1-EXIT;");
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            BSP_display("s1-INIT;");
            return Q_TRAN(&QHsmElevator_s11);
        }
        case B_SIG: {
            BSP_display("s1-B;");
            return Q_TRAN(&QHsmElevator_s111);
        }
        case C_SIG: {
            BSP_display("s1-C;");
            return Q_TRAN(&QHsmElevator_s2);
        }
        case D_SIG: {                            /* transition with a guard */
            if (!me->foo) {
                BSP_display("s1-D;");
                me->foo = 1;
                return Q_TRAN(&QHsmElevator_s);
            }
            break;
        }
        case I_SIG: {                                /* internal transition */
            BSP_display("s1-I;");
            return Q_HANDLED();
        }
    }
    return Q_SUPER(&QHsmElevator_s);
}
/*..........................................................................*/
QState QHsmElevator_s11(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            BSP_display("s11-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            BSP_display("s11-EXIT;");
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            BSP_display("s11-INIT;");
            return Q_TRAN(&QHsmElevator_s111);
        }
        case A_SIG: {
            BSP_display("s11-A;");
            return Q_TRAN(&QHsmElevator_s11);
        }
        case D_SIG: {
            BSP_display("s11-D;");
            return Q_TRAN(&QHsmElevator_s1);
        }
        case G_SIG: {
            BSP_display("s11-G;");
            return Q_TRAN(&QHsmElevator_s21);
        }
    }
    return Q_SUPER(&QHsmElevator_s1);
}
/*..........................................................................*/
QState QHsmElevator_s111(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            BSP_display("s111-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            BSP_display("s111-EXIT;");
            return Q_HANDLED();
        }
        case F_SIG: {                            /* transition with a guard */
            if (me->foo) {
                BSP_display("s111-F;");
                me->foo = 0;
                return Q_TRAN(&QHsmElevator_s2);
            }
            break;
        }
        case H_SIG: {
            BSP_display("s111-H;");
            return Q_TRAN(&QHsmElevator_s);
        }
    }
    return Q_SUPER(&QHsmElevator_s11);
}
/*..........................................................................*/
QState QHsmElevator_s2(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            BSP_display("s2-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            BSP_display("s2-EXIT;");
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            BSP_display("s2-INIT;");
            return Q_TRAN(&QHsmElevator_s211);
        }
        case C_SIG: {
            BSP_display("s2-C;");
            return Q_TRAN(&QHsmElevator_s1);
        }
        case I_SIG: {                   /* internal transition with a guard */
            if (!me->foo) {
                BSP_display("s2-I;");
                me->foo = (uint8_t)1;
                return Q_HANDLED();
            }
            break;
        }
    }
    return Q_SUPER(&QHsmElevator_s);
}
/*..........................................................................*/
QState QHsmElevator_s21(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            BSP_display("s21-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            BSP_display("s21-EXIT;");
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            BSP_display("s21-INIT;");
            return Q_TRAN(&QHsmElevator_s211);
        }
        case A_SIG: {
            BSP_display("s21-A;");
            return Q_TRAN(&QHsmElevator_s2);
        }
        case B_SIG: {
            BSP_display("s21-B;");
            return Q_TRAN(&QHsmElevator_s211);
        }
        case H_SIG: {
            BSP_display("s21-H;");
            return Q_TRAN(&QHsmElevator_s);
        }
    }
    return Q_SUPER(&QHsmElevator_s2);
}
/*..........................................................................*/
QState QHsmElevator_s211(QHsmElevator *me) {
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            BSP_display("s211-ENTRY;");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            BSP_display("s211-EXIT;");
            return Q_HANDLED();
        }
        case D_SIG: {
            BSP_display("s211-D;");
            return Q_TRAN(&QHsmElevator_s21);
        }
        case F_SIG: {
            BSP_display("s211-F;");
            return Q_TRAN(&QHsmElevator_s1);
        }
        case G_SIG: {
            BSP_display("s211-G;");
            return Q_TRAN(&QHsmElevator_s111);
        }
    }
    return Q_SUPER(&QHsmElevator_s21);
}


