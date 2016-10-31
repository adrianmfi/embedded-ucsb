#include "qpn_port.h"
#include "qhsmelevator.h"
#include <stdlib.h>
#include <stdio.h>

/* local objects -----------------------------------------------------------*/
static FILE *l_outFile = (FILE *)0;
static void dispatch(QSignal sig);

/*..........................................................................*/
int main(int argc, char *argv[]) {
    QHsmElevator_ctor();                                  /* instantiate the HSM */

    if (argc > 1) {                                  /* file name provided? */
        l_outFile = fopen(argv[1], "w");
    }

    if (l_outFile == (FILE *)0) {                   /* interactive version? */
        l_outFile = stdout;            /* use the stdout as the output file */

        printf("QHsmElevator example, built on %s at %s,\n"
               "QP-nano: %s.\nPress ESC to quit...\n",
               __DATE__, __TIME__, QP_getVersion());

        QHsm_init((QHsm *)&HSM_QHsmElevator);    /* take the initial transitioin */

        for (;;) {                                            /* event loop */
            int c;

            printf("\n>");
            c = getchar();
            printf(": ");

            if ('a' <= c && c <= 'i') {                        /* in range? */
                Q_SIG((QHsm *)&HSM_QHsmElevator) = (QSignal)(c - 'a' + A_SIG);
            }
            else if ('A' <= c && c <= 'I') {                   /* in range? */
                Q_SIG((QHsm *)&HSM_QHsmElevator) = (QSignal)(c - 'A' + A_SIG);
            }
            else if (c == '\33') {                          /* the ESC key? */
                Q_SIG((QHsm *)&HSM_QHsmElevator) = TERMINATE_SIG;
            }
            else {
                Q_SIG((QHsm *)&HSM_QHsmElevator) = IGNORE_SIG;
            }

            QHsm_dispatch((QHsm *)&HSM_QHsmElevator);      /* dispatch the event */
        }
    }
    else {                                                 /* batch version */
        printf("QHsmElevator example, built on %s at %s, QP-nano %s\n"
               "output saved to %s\n",
               __DATE__, __TIME__, QP_getVersion(),
               argv[1]);

        fprintf(l_outFile, "QHsmElevator example, QP-nano %s\n",
                QP_getVersion());

        QHsm_init((QHsm *)&HSM_QHsmElevator);    /* take the initial transitioin */

                                     /* testing all kinds of transitions... */
        dispatch(A_SIG);
        dispatch(B_SIG);
        dispatch(D_SIG);
        dispatch(E_SIG);
        dispatch(I_SIG);
        dispatch(F_SIG);
        dispatch(I_SIG);
        dispatch(I_SIG);
        dispatch(F_SIG);
        dispatch(A_SIG);
        dispatch(B_SIG);
        dispatch(D_SIG);
        dispatch(D_SIG);
        dispatch(E_SIG);
        dispatch(G_SIG);
        dispatch(H_SIG);
        dispatch(H_SIG);
        dispatch(C_SIG);
        dispatch(G_SIG);
        dispatch(C_SIG);
        dispatch(C_SIG);

        fclose(l_outFile);
    }

    return 0;
}
/*..........................................................................*/
void Q_onAssert(char const Q_ROM * const Q_ROM_VAR file, int line) {
    fprintf(stderr, "Assertion failed in %s, line %d", file, line);
    exit(-1);
}
/*..........................................................................*/
void BSP_display(char const *msg) {
    fprintf(l_outFile, msg);
}
/*..........................................................................*/
void BSP_exit(void) {
    printf("Bye, Bye!");
    exit(0);
}
/*..........................................................................*/
static void dispatch(QSignal sig) {
    fprintf(l_outFile, "\n%c:", 'A' + sig - A_SIG);
    Q_SIG((QHsm *)&HSM_QHsmElevator) = sig;
    QHsm_dispatch((QHsm *)&HSM_QHsmElevator);              /* dispatch the event */
}
