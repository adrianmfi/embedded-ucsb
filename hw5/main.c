#include "qpn_port.h"
#include "qhsmelevator.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define callTimeFreq 20;
#define totalSimTime 1000;

/* local objects -----------------------------------------------------------*/
static FILE *l_outFile = (FILE *)0;

int cmpfunc(const void *x, const void *y)
{
return (*(double*)x - *(double*)y);
}

/*..........................................................................*/
int main(int argc, char *argv[]) {
    QHsmElevator_ctor();                                  /* instantiate the HSM */
    QHsm_init((QHsm *)&HSM_QHsmElevator);    /* take the initial transitioin */

    if (argc > 1) {                                  /* file name provided? */
        l_outFile = fopen(argv[1], "w");
    }

    if (l_outFile == (FILE *)0) { //the version that generates results.out
        l_outFile = fopen("results.out","w");

        //Place your input and dispatches here!

        fprintf(l_outFile, "1:%f 2:%f 3:%f 4:%f 5:%f",getAvg(1),getAvg(2),getAvg(3),getAvg(4),getAvg(5));

            /*interactive version - deprecated 
            l_outFile = stdout;
            int c;
            for(;;){
                printf("\n>");
                c = getchar();
                printf(": ");

                if ('1' <= c && c <= '5') {                      
                    Q_SIG((QHsm *)&HSM_QHsmElevator) = BTN_SIG;
                    Q_PAR((QHsm *)&HSM_QHsmElevator) = c - '0';
                    QHsm_dispatch((QHsm *)&HSM_QHsmElevator);    
                }
                else if (c == 't') {                   
                    Q_SIG((QHsm *)&HSM_QHsmElevator) = TICK_SIG;
                    QHsm_dispatch((QHsm *)&HSM_QHsmElevator);  
                    
                }
                else if (c == 'c') {                          
                    printf("\n tick = %d\n", getTick());
                }
                  else if (c == 'f') {                          
                    printf("\n floor = %d\n", getFloor());
                }
            
        }   
*/
    }
    else {   
    /*  task 1a
        int buttonPresses[] = {2,3,5,2,5,3,4,1};
        int pressTimes[] = {0,20,50,100,110,150,200,210};
        int j = 0;
        for(j = 0; j < 8; j++){
            while(getTick() < pressTimes[j]){

                Q_SIG((QHsm *)&HSM_QHsmElevator) = TICK_SIG;
                QHsm_dispatch((QHsm *)&HSM_QHsmElevator);                
            }
            Q_SIG((QHsm *)&HSM_QHsmElevator) = BTN_SIG;
            Q_PAR((QHsm *)&HSM_QHsmElevator) = buttonPresses[j];
            QHsm_dispatch((QHsm *)&HSM_QHsmElevator);              
        }

*/      int k ;
        double avgTimes1[40] = {0};
        double avgTimes2[40] = {0};
        double avgTimes3[40] = {0};
        double avgTimes4[40] = {0};
        double avgTimes5[40] = {0};

        int seconds[] = {200,100,50,25,10};
        int s = 0;
        for(s = 0; s < 5; s++){
        srand(time(NULL));
        for(k = 0; k < 40; k++){
            QHsmElevator_ctor();                                  /* instantiate the HSM */

            int i;
            for(i = 0; i < 10000; i++){
                int btnPress = 1+rand()%5; 
                Q_SIG((QHsm *)&HSM_QHsmElevator) = BTN_SIG;
                Q_PAR((QHsm *)&HSM_QHsmElevator) = btnPress; 
                QHsm_dispatch((QHsm *)&HSM_QHsmElevator);  
                int j;
                for(j = 0; j < seconds[s]; j++){
                    Q_SIG((QHsm *)&HSM_QHsmElevator) = TICK_SIG;
                    QHsm_dispatch((QHsm *)&HSM_QHsmElevator);    
                }
            }
            avgTimes1[k] = getAvg(1);
            avgTimes2[k] = getAvg(2);
            avgTimes3[k] = getAvg(3);
            avgTimes4[k] = getAvg(4);
            avgTimes5[k] = getAvg(5);
            fclose(l_outFile);
        }
        qsort(avgTimes1, 40, sizeof(double), cmpfunc);
        qsort(avgTimes2, 40, sizeof(double), cmpfunc);
        qsort(avgTimes3, 40, sizeof(double), cmpfunc);
        qsort(avgTimes4, 40, sizeof(double), cmpfunc);
        qsort(avgTimes5, 40, sizeof(double), cmpfunc);
        printf("\nElevator model, button press every %d seconds\n", seconds[s]);
        printf("95 confidence interval for 1: [%f, %f]\n",avgTimes1[1], avgTimes1[38]);
        printf("95 confidence interval for 2: [%f, %f]\n",avgTimes2[1], avgTimes2[38]);
        printf("95 confidence interval for 3: [%f, %f]\n",avgTimes3[1], avgTimes3[38]);
        printf("95 confidence interval for 4: [%f, %f]\n",avgTimes4[1], avgTimes4[38]);
        printf("95 confidence interval for 5: [%f, %f]\n",avgTimes5[1], avgTimes5[38]);
        }
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

void writeStop(int T,int P, int PE, int F){
    fprintf(l_outFile, "T:%d P:%d PE: %d F:%d D:Standing still\n",T,P,PE,F);
}
void writeUp(int T,int P, int PE, int F){
    fprintf(l_outFile, "T:%d P:%d PE: %d F:%d D:Up\n",T,P,PE,F);
}
void writeDown(int T,int P, int PE, int F){
    fprintf(l_outFile, "T:%d P:%d PE: %d F:%d D:Down\n",T,P,PE,F);
}