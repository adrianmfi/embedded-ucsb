
Minimize
	 obj : latency

Subject To
latency - stop_START - stop_latency >= 0

\ Node Control Step Constraints
start_START - 1 start_1 - 2 start_2 - 3 start_3 - 4 start_4 - 5 start_5 - 6 start_6 - 7 start_7 - 8 start_8 - 9 start_9 - 10 start_10 - 11 start_11 = 0
start_1 + start_2 + start_3 + start_4 + start_5 + start_6 + start_7 + start_8 + start_9 + start_10 + start_11 = 1
T1_START - 1 T1_1 - 2 T1_2 - 3 T1_3 - 4 T1_4 - 5 T1_5 - 6 T1_6 - 7 T1_7 - 8 T1_8 - 9 T1_9 - 10 T1_10 - 11 T1_11 = 0
T1_1 + T1_2 + T1_3 + T1_4 + T1_5 + T1_6 + T1_7 + T1_8 + T1_9 + T1_10 + T1_11 = 1
T2_START - 1 T2_1 - 2 T2_2 - 3 T2_3 - 4 T2_4 - 5 T2_5 - 6 T2_6 - 7 T2_7 - 8 T2_8 - 9 T2_9 - 10 T2_10 - 11 T2_11 = 0
T2_1 + T2_2 + T2_3 + T2_4 + T2_5 + T2_6 + T2_7 + T2_8 + T2_9 + T2_10 + T2_11 = 1
T4_START - 1 T4_1 - 2 T4_2 - 3 T4_3 - 4 T4_4 - 5 T4_5 - 6 T4_6 - 7 T4_7 - 8 T4_8 - 9 T4_9 - 10 T4_10 - 11 T4_11 = 0
T4_1 + T4_2 + T4_3 + T4_4 + T4_5 + T4_6 + T4_7 + T4_8 + T4_9 + T4_10 + T4_11 = 1
T3_START - 1 T3_1 - 2 T3_2 - 3 T3_3 - 4 T3_4 - 5 T3_5 - 6 T3_6 - 7 T3_7 - 8 T3_8 - 9 T3_9 - 10 T3_10 - 11 T3_11 = 0
T3_1 + T3_2 + T3_3 + T3_4 + T3_5 + T3_6 + T3_7 + T3_8 + T3_9 + T3_10 + T3_11 = 1
T5_START - 1 T5_1 - 2 T5_2 - 3 T5_3 - 4 T5_4 - 5 T5_5 - 6 T5_6 - 7 T5_7 - 8 T5_8 - 9 T5_9 - 10 T5_10 - 11 T5_11 = 0
T5_1 + T5_2 + T5_3 + T5_4 + T5_5 + T5_6 + T5_7 + T5_8 + T5_9 + T5_10 + T5_11 = 1
T7_START - 1 T7_1 - 2 T7_2 - 3 T7_3 - 4 T7_4 - 5 T7_5 - 6 T7_6 - 7 T7_7 - 8 T7_8 - 9 T7_9 - 10 T7_10 - 11 T7_11 = 0
T7_1 + T7_2 + T7_3 + T7_4 + T7_5 + T7_6 + T7_7 + T7_8 + T7_9 + T7_10 + T7_11 = 1
T6_START - 1 T6_1 - 2 T6_2 - 3 T6_3 - 4 T6_4 - 5 T6_5 - 6 T6_6 - 7 T6_7 - 8 T6_8 - 9 T6_9 - 10 T6_10 - 11 T6_11 = 0
T6_1 + T6_2 + T6_3 + T6_4 + T6_5 + T6_6 + T6_7 + T6_8 + T6_9 + T6_10 + T6_11 = 1
T8_START - 1 T8_1 - 2 T8_2 - 3 T8_3 - 4 T8_4 - 5 T8_5 - 6 T8_6 - 7 T8_7 - 8 T8_8 - 9 T8_9 - 10 T8_10 - 11 T8_11 = 0
T8_1 + T8_2 + T8_3 + T8_4 + T8_5 + T8_6 + T8_7 + T8_8 + T8_9 + T8_10 + T8_11 = 1
stop_START - 1 stop_1 - 2 stop_2 - 3 stop_3 - 4 stop_4 - 5 stop_5 - 6 stop_6 - 7 stop_7 - 8 stop_8 - 9 stop_9 - 10 stop_10 - 11 stop_11 = 0
stop_1 + stop_2 + stop_3 + stop_4 + stop_5 + stop_6 + stop_7 + stop_8 + stop_9 + stop_10 + stop_11 = 1

\ Dependency Constraints
start_START + start_latency - T1_START <= 0
start_START + start_latency - T2_START <= 0
start_START + start_latency - T4_START <= 0
T1_START + T1_latency - T3_START <= 0
T2_START + T2_latency - T3_START <= 0
T4_START + T4_latency - T5_START <= 0
T3_START + T3_latency - T7_START <= 0
T3_START + T3_latency - T6_START <= 0
T5_START + T5_latency - T6_START <= 0
T7_START + T7_latency - T8_START <= 0
T6_START + T6_latency - T8_START <= 0
T8_START + T8_latency - stop_START <= 0

\ Mapping Constraints
nop_start=1
start_latency - 0 nop_start = 0
R1_T1=1
T1_latency - 1 R1_T1 = 0
R2_T2=1
T2_latency - 1 R2_T2 = 0
R1_T4+R2_T4=1
T4_latency - 1 R1_T4 - 1 R2_T4 = 0
R2_T3+R3_T3=1
T3_latency - 1 R2_T3 - 1 R3_T3 = 0
R4_T5+R5_T5=1
T5_latency - 1 R4_T5 - 1 R5_T5 = 0
R1_T7+R4_T7=1
T7_latency - 1 R1_T7 - 1 R4_T7 = 0
R5_T6=1
T6_latency - 1 R5_T6 = 0
R3_T8=1
T8_latency - 1 R3_T8 = 0
nop_stop=1
stop_latency - 0 nop_stop = 0

\ Resource Concurrency

\ 	 Resource Concurrency Constraint for Resource R5
T5_1 + T6_1 <= 1
T5_2 + T6_2 <= 1
T5_3 + T6_3 <= 1
T5_4 + T6_4 <= 1
T5_5 + T6_5 <= 1
T5_6 + T6_6 <= 1
T5_7 + T6_7 <= 1
T5_8 + T6_8 <= 1
T5_9 + T6_9 <= 1
T5_10 + T6_10 <= 1

\ 	 Resource Concurrency Constraint for Resource R3
T3_1 + T8_1 <= 1
T3_2 + T8_2 <= 1
T3_3 + T8_3 <= 1
T3_4 + T8_4 <= 1
T3_5 + T8_5 <= 1
T3_6 + T8_6 <= 1
T3_7 + T8_7 <= 1
T3_8 + T8_8 <= 1
T3_9 + T8_9 <= 1
T3_10 + T8_10 <= 1

\ 	 Resource Concurrency Constraint for Resource R1
T1_1 + T4_1 + T7_1 <= 1
T1_2 + T4_2 + T7_2 <= 1
T1_3 + T4_3 + T7_3 <= 1
T1_4 + T4_4 + T7_4 <= 1
T1_5 + T4_5 + T7_5 <= 1
T1_6 + T4_6 + T7_6 <= 1
T1_7 + T4_7 + T7_7 <= 1
T1_8 + T4_8 + T7_8 <= 1
T1_9 + T4_9 + T7_9 <= 1
T1_10 + T4_10 + T7_10 <= 1

\ 	 Resource Concurrency Constraint for Resource R2
T2_1 + T3_1 + T4_1 <= 1
T2_2 + T3_2 + T4_2 <= 1
T2_3 + T3_3 + T4_3 <= 1
T2_4 + T3_4 + T4_4 <= 1
T2_5 + T3_5 + T4_5 <= 1
T2_6 + T3_6 + T4_6 <= 1
T2_7 + T3_7 + T4_7 <= 1
T2_8 + T3_8 + T4_8 <= 1
T2_9 + T3_9 + T4_9 <= 1
T2_10 + T3_10 + T4_10 <= 1

\ 	 Resource Concurrency Constraint for Resource nop
 <= 10
 <= 10
 <= 10
 <= 10
 <= 10
 <= 10
 <= 10
 <= 10
 <= 10
 <= 10
 <= 10

\ 	 Resource Concurrency Constraint for Resource R4
T5_1 + T7_1 <= 1
T5_2 + T7_2 <= 1
T5_3 + T7_3 <= 1
T5_4 + T7_4 <= 1
T5_5 + T7_5 <= 1
T5_6 + T7_6 <= 1
T5_7 + T7_7 <= 1
T5_8 + T7_8 <= 1
T5_9 + T7_9 <= 1
T5_10 + T7_10 <= 1

T3_1 - mpy1_T3_1 - mpy2_T3_1 = 0
T3_2 - mpy1_T3_2 - mpy2_T3_2 = 0
T3_3 - mpy1_T3_3 - mpy2_T3_3 = 0
T3_4 - mpy1_T3_4 - mpy2_T3_4 = 0
T3_5 - mpy1_T3_5 - mpy2_T3_5 = 0
T3_6 - mpy1_T3_6 - mpy2_T3_6 = 0
T3_7 - mpy1_T3_7 - mpy2_T3_7 = 0
T3_8 - mpy1_T3_8 - mpy2_T3_8 = 0
T3_9 - mpy1_T3_9 - mpy2_T3_9 = 0
T3_10 - mpy1_T3_10 - mpy2_T3_10 = 0
T3_11 - mpy1_T3_11 - mpy2_T3_11 = 0
T8_1 - mpy1_T8_1 - mpy2_T8_1 = 0
T8_2 - mpy1_T8_2 - mpy2_T8_2 = 0
T8_3 - mpy1_T8_3 - mpy2_T8_3 = 0
T8_4 - mpy1_T8_4 - mpy2_T8_4 = 0
T8_5 - mpy1_T8_5 - mpy2_T8_5 = 0
T8_6 - mpy1_T8_6 - mpy2_T8_6 = 0
T8_7 - mpy1_T8_7 - mpy2_T8_7 = 0
T8_8 - mpy1_T8_8 - mpy2_T8_8 = 0
T8_9 - mpy1_T8_9 - mpy2_T8_9 = 0
T8_10 - mpy1_T8_10 - mpy2_T8_10 = 0
T8_11 - mpy1_T8_11 - mpy2_T8_11 = 0
\Bounds on Decisions Variables
Bounds
0 <=                R1_T1 <= 1
0 <=                R1_T7 <= 1
0 <=                R1_T4 <= 1
0 <=                T3_10 <= 1
0 <=                T3_11 <= 1
0 <=                 T8_1 <= 1
0 <=                T6_11 <= 1
0 <=                T6_10 <= 1
0 <=               stop_6 <= 1
0 <=               stop_8 <= 1
0 <=                T8_11 <= 1
0 <=                T8_10 <= 1
0 <=                 T5_8 <= 1
0 <=                 T5_9 <= 1
0 <=                 T5_1 <= 1
0 <=                 T5_2 <= 1
0 <=                 T5_3 <= 1
0 <=                 T5_4 <= 1
0 <=                 T5_5 <= 1
0 <=                 T5_6 <= 1
0 <=                 T5_7 <= 1
0 <=                T5_10 <= 1
0 <=                T5_11 <= 1
0 <=                R4_T5 <= 1
0 <=                R4_T7 <= 1
0 <=                 T8_2 <= 1
0 <=                 T8_5 <= 1
0 <=                 T8_4 <= 1
0 <=                 T8_7 <= 1
0 <=                 T8_6 <= 1
0 <=                 T8_9 <= 1
0 <=                 T8_8 <= 1
0 <=                 T7_8 <= 1
0 <=                 T7_9 <= 1
0 <=                 T7_6 <= 1
0 <=                 T7_7 <= 1
0 <=                 T7_4 <= 1
0 <=                 T7_5 <= 1
0 <=                 T7_2 <= 1
0 <=                 T7_3 <= 1
0 <=                 T8_3 <= 1
0 <=                 T7_1 <= 1
0 <=               stop_9 <= 1
0 <=                R3_T8 <= 1
0 <=                 T1_8 <= 1
0 <=                 T1_9 <= 1
0 <=                 T1_4 <= 1
0 <=                 T1_5 <= 1
0 <=                 T1_6 <= 1
0 <=                 T1_7 <= 1
0 <=                 T1_1 <= 1
0 <=                 T1_2 <= 1
0 <=                 T1_3 <= 1
0 <=                 T3_2 <= 1
0 <=                 T3_3 <= 1
0 <=                 T4_3 <= 1
0 <=                 T3_1 <= 1
0 <=                 T3_6 <= 1
0 <=                 T3_7 <= 1
0 <=                 T3_4 <= 1
0 <=                 T4_6 <= 1
0 <=                 T4_9 <= 1
0 <=                 T4_8 <= 1
0 <=                 T3_8 <= 1
0 <=                 T3_9 <= 1
0 <=                 T6_7 <= 1
0 <=                 T6_6 <= 1
0 <=                 T6_5 <= 1
0 <=                 T6_4 <= 1
0 <=                 T6_3 <= 1
0 <=                 T6_2 <= 1
0 <=                 T6_1 <= 1
0 <=                 T6_9 <= 1
0 <=                 T6_8 <= 1
0 <=                T7_10 <= 1
0 <=                T7_11 <= 1
0 <=              stop_11 <= 1
0 <=              stop_10 <= 1
0 <=                R3_T3 <= 1
0 <=             nop_stop <= 1
0 <=              start_8 <= 1
0 <=              start_9 <= 1
0 <=              start_6 <= 1
0 <=              start_7 <= 1
0 <=              start_4 <= 1
0 <=              start_5 <= 1
0 <=              start_2 <= 1
0 <=              start_3 <= 1
0 <=              start_1 <= 1
0 <=                 T4_1 <= 1
0 <=                 T4_2 <= 1
0 <=                 T4_5 <= 1
0 <=               stop_1 <= 1
0 <=                 T4_4 <= 1
0 <=               stop_3 <= 1
0 <=               stop_2 <= 1
0 <=                 T2_9 <= 1
0 <=                 T2_8 <= 1
0 <=               stop_7 <= 1
0 <=                 T4_7 <= 1
0 <=               stop_5 <= 1
0 <=               stop_4 <= 1
0 <=                 T2_3 <= 1
0 <=                 T2_2 <= 1
0 <=                 T2_1 <= 1
0 <=                 T3_5 <= 1
0 <=                 T2_7 <= 1
0 <=                 T2_6 <= 1
0 <=                 T2_5 <= 1
0 <=                 T2_4 <= 1
0 <=            nop_start <= 1
0 <=             start_10 <= 1
0 <=             start_11 <= 1
0 <=                T4_11 <= 1
0 <=                T4_10 <= 1
0 <=                R2_T2 <= 1
0 <=                R2_T3 <= 1
0 <=                R5_T6 <= 1
0 <=                R5_T5 <= 1
0 <=                R2_T4 <= 1
0 <=                T1_10 <= 1
0 <=                T1_11 <= 1
0 <=                T2_11 <= 1
0 <=                T2_10 <= 1
0 <=           T2_latency <= 100
0 <=          start_START <= 100
0 <=             T6_START <= 100
0 <=        start_latency <= 100
0 <=             T5_START <= 100
0 <=           T4_latency <= 100
0 <=           T8_latency <= 100
0 <=         stop_latency <= 100
0 <=             T8_START <= 100
0 <=           T7_latency <= 100
0 <=           T6_latency <= 100
0 <=             T1_START <= 100
0 <=           T3_latency <= 100
0 <=           T5_latency <= 100
0 <=           T1_latency <= 100
0 <=             T3_START <= 100
0 <=           stop_START <= 100
0 <=             T4_START <= 100
0 <=             T7_START <= 100
0 <=             T2_START <= 100
General
	R1_T1
	R1_T7
	R1_T4
	T3_10
	T3_11
	T8_1
	T6_11
	T6_10
	stop_6
	stop_8
	T8_11
	T8_10
	T5_8
	T5_9
	T5_1
	T5_2
	T5_3
	T5_4
	T5_5
	T5_6
	T5_7
	T5_10
	T5_11
	R4_T5
	R4_T7
	T8_2
	T8_5
	T8_4
	T8_7
	T8_6
	T8_9
	T8_8
	T7_8
	T7_9
	T7_6
	T7_7
	T7_4
	T7_5
	T7_2
	T7_3
	T8_3
	T7_1
	stop_9
	R3_T8
	T1_8
	T1_9
	T1_4
	T1_5
	T1_6
	T1_7
	T1_1
	T1_2
	T1_3
	T3_2
	T3_3
	T4_3
	T3_1
	T3_6
	T3_7
	T3_4
	T4_6
	T4_9
	T4_8
	T3_8
	T3_9
	T6_7
	T6_6
	T6_5
	T6_4
	T6_3
	T6_2
	T6_1
	T6_9
	T6_8
	T7_10
	T7_11
	stop_11
	stop_10
	R3_T3
	nop_stop
	start_8
	start_9
	start_6
	start_7
	start_4
	start_5
	start_2
	start_3
	start_1
	T4_1
	T4_2
	T4_5
	stop_1
	T4_4
	stop_3
	stop_2
	T2_9
	T2_8
	stop_7
	T4_7
	stop_5
	stop_4
	T2_3
	T2_2
	T2_1
	T3_5
	T2_7
	T2_6
	T2_5
	T2_4
	nop_start
	start_10
	start_11
	T4_11
	T4_10
	R2_T2
	R2_T3
	R5_T6
	R5_T5
	R2_T4
	T1_10
	T1_11
	T2_11
	T2_10
End
