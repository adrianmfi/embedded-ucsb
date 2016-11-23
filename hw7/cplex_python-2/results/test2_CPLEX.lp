
Minimize
	 obj : latency

Subject To
latency - stop_START - stop_latency >= 0

\ Node Control Step Constraints
start_START - 1 start_1 - 2 start_2 - 3 start_3 - 4 start_4 - 5 start_5 - 6 start_6 - 7 start_7 - 8 start_8 - 9 start_9 = 0
start_1 + start_2 + start_3 + start_4 + start_5 + start_6 + start_7 + start_8 + start_9 = 1
n1_START - 1 n1_1 - 2 n1_2 - 3 n1_3 - 4 n1_4 - 5 n1_5 - 6 n1_6 - 7 n1_7 - 8 n1_8 - 9 n1_9 = 0
n1_1 + n1_2 + n1_3 + n1_4 + n1_5 + n1_6 + n1_7 + n1_8 + n1_9 = 1
n2_START - 1 n2_1 - 2 n2_2 - 3 n2_3 - 4 n2_4 - 5 n2_5 - 6 n2_6 - 7 n2_7 - 8 n2_8 - 9 n2_9 = 0
n2_1 + n2_2 + n2_3 + n2_4 + n2_5 + n2_6 + n2_7 + n2_8 + n2_9 = 1
n3_START - 1 n3_1 - 2 n3_2 - 3 n3_3 - 4 n3_4 - 5 n3_5 - 6 n3_6 - 7 n3_7 - 8 n3_8 - 9 n3_9 = 0
n3_1 + n3_2 + n3_3 + n3_4 + n3_5 + n3_6 + n3_7 + n3_8 + n3_9 = 1
n4_START - 1 n4_1 - 2 n4_2 - 3 n4_3 - 4 n4_4 - 5 n4_5 - 6 n4_6 - 7 n4_7 - 8 n4_8 - 9 n4_9 = 0
n4_1 + n4_2 + n4_3 + n4_4 + n4_5 + n4_6 + n4_7 + n4_8 + n4_9 = 1
p1_START - 1 p1_1 - 2 p1_2 - 3 p1_3 - 4 p1_4 - 5 p1_5 - 6 p1_6 - 7 p1_7 - 8 p1_8 - 9 p1_9 = 0
p1_1 + p1_2 + p1_3 + p1_4 + p1_5 + p1_6 + p1_7 + p1_8 + p1_9 = 1
p2_START - 1 p2_1 - 2 p2_2 - 3 p2_3 - 4 p2_4 - 5 p2_5 - 6 p2_6 - 7 p2_7 - 8 p2_8 - 9 p2_9 = 0
p2_1 + p2_2 + p2_3 + p2_4 + p2_5 + p2_6 + p2_7 + p2_8 + p2_9 = 1
p3_START - 1 p3_1 - 2 p3_2 - 3 p3_3 - 4 p3_4 - 5 p3_5 - 6 p3_6 - 7 p3_7 - 8 p3_8 - 9 p3_9 = 0
p3_1 + p3_2 + p3_3 + p3_4 + p3_5 + p3_6 + p3_7 + p3_8 + p3_9 = 1
p4_START - 1 p4_1 - 2 p4_2 - 3 p4_3 - 4 p4_4 - 5 p4_5 - 6 p4_6 - 7 p4_7 - 8 p4_8 - 9 p4_9 = 0
p4_1 + p4_2 + p4_3 + p4_4 + p4_5 + p4_6 + p4_7 + p4_8 + p4_9 = 1
stop_START - 1 stop_1 - 2 stop_2 - 3 stop_3 - 4 stop_4 - 5 stop_5 - 6 stop_6 - 7 stop_7 - 8 stop_8 - 9 stop_9 = 0
stop_1 + stop_2 + stop_3 + stop_4 + stop_5 + stop_6 + stop_7 + stop_8 + stop_9 = 1

\ Dependency Constraints
start_START + start_latency - n1_START <= 0
start_START + start_latency - n2_START <= 0
start_START + start_latency - n3_START <= 0
start_START + start_latency - n4_START <= 0
n1_START + n1_latency - p1_START <= 0
n2_START + n2_latency - p2_START <= 0
n3_START + n3_latency - p3_START <= 0
n4_START + n4_latency - p4_START <= 0
p1_START + p1_latency - stop_START <= 0
p2_START + p2_latency - stop_START <= 0
p3_START + p3_latency - stop_START <= 0
p4_START + p4_latency - stop_START <= 0

\ Mapping Constraints
nop_start=1
start_latency - 0 nop_start = 0
mpy1_n1+mpy2_n1=1
n1_latency - 1 mpy1_n1 - 2 mpy2_n1 = 0
mpy1_n2+mpy2_n2=1
n2_latency - 1 mpy1_n2 - 2 mpy2_n2 = 0
mpy1_n3+mpy2_n3=1
n3_latency - 1 mpy1_n3 - 2 mpy2_n3 = 0
mpy1_n4+mpy2_n4=1
n4_latency - 1 mpy1_n4 - 2 mpy2_n4 = 0
alu_p1=1
p1_latency - 1 alu_p1 = 0
alu_p2=1
p2_latency - 1 alu_p2 = 0
alu_p3=1
p3_latency - 1 alu_p3 = 0
alu_p4=1
p4_latency - 1 alu_p4 = 0
nop_stop=1
stop_latency - 0 nop_stop = 0

mpy1_1_1 - n1_1 - n2_1 - n3_1 - n4_1 = 0

\ Resource Concurrency
mpy1_1_1 + mpy1_2_1 <= 2  
mpy1_1_2 + mpy1_2_2 <= 2  
mpy1_1_3 + mpy1_2_3 <= 2  
mpy1_1_4 + mpy1_2_4 <= 2  
mpy1_1_5 + mpy1_2_5 <= 2  
mpy1_1_6 + mpy1_2_6 <= 2  
mpy1_1_7 + mpy1_2_7 <= 2  
mpy1_1_8 + mpy1_2_8 <= 2  

mpy2_1_1 <= 1  
mpy2_1_2 <= 1  
mpy2_1_3 <= 1  
mpy2_1_4 <= 1  
mpy2_1_5 <= 1  
mpy2_1_6 <= 1  
mpy2_1_7 <= 1  
mpy2_1_8 <= 1  

\ 	 Resource Concurrency Constraint for Resource mpy1
n1_1 + n2_1 + n3_1 + n4_1 <= 3
n1_2 + n2_2 + n3_2 + n4_2 <= 3
n1_3 + n2_3 + n3_3 + n4_3 <= 3
n1_4 + n2_4 + n3_4 + n4_4 <= 3
n1_5 + n2_5 + n3_5 + n4_5 <= 3
n1_6 + n2_6 + n3_6 + n4_6 <= 3
n1_7 + n2_7 + n3_7 + n4_7 <= 3
n1_8 + n2_8 + n3_8 + n4_8 <= 3

mpy1_n1

\ 	 Resource Concurrency Constraint for Resource mpy2
\n1_1 + n1_2 + n2_1 + n2_2 + n3_1 + n3_2 + n4_1 + n4_2 <= 1
\n1_2 + n1_3 + n2_2 + n2_3 + n3_2 + n3_3 + n4_2 + n4_3 <= 1
\n1_3 + n1_4 + n2_3 + n2_4 + n3_3 + n3_4 + n4_3 + n4_4 <= 1
\n1_4 + n1_5 + n2_4 + n2_5 + n3_4 + n3_5 + n4_4 + n4_5 <= 1
\n1_5 + n1_6 + n2_5 + n2_6 + n3_5 + n3_6 + n4_5 + n4_6 <= 1
\n1_6 + n1_7 + n2_6 + n2_7 + n3_6 + n3_7 + n4_6 + n4_7 <= 1
\n1_7 + n1_8 + n2_7 + n2_8 + n3_7 + n3_8 + n4_7 + n4_8 <= 1

\ 	 Resource Concurrency Constraint for Resource alu
p1_1 + p2_1 + p3_1 + p4_1 <= 1
p1_2 + p2_2 + p3_2 + p4_2 <= 1
p1_3 + p2_3 + p3_3 + p4_3 <= 1
p1_4 + p2_4 + p3_4 + p4_4 <= 1
p1_5 + p2_5 + p3_5 + p4_5 <= 1
p1_6 + p2_6 + p3_6 + p4_6 <= 1
p1_7 + p2_7 + p3_7 + p4_7 <= 1
p1_8 + p2_8 + p3_8 + p4_8 <= 1

\ 	 Resource Concurrency Constraint for Resource nop
 <= 2
 <= 2
 <= 2
 <= 2
 <= 2
 <= 2
 <= 2
 <= 2
 <= 2


\Bounds on Decisions Variables
Bounds
0 <=                 n3_8 <= 1
0 <=                 n3_9 <= 1
0 <=                 n3_1 <= 1
0 <=                 n3_2 <= 1
0 <=                 n3_3 <= 1
0 <=                 n3_4 <= 1
0 <=                 n3_5 <= 1
0 <=                 n3_6 <= 1
0 <=                 n3_7 <= 1
0 <=                 n1_8 <= 1
0 <=                 n1_9 <= 1
0 <=                 n1_6 <= 1
0 <=                 n1_7 <= 1
0 <=                 n1_4 <= 1
0 <=                 n1_5 <= 1
0 <=                 n1_2 <= 1
0 <=                 n1_3 <= 1
0 <=                 n1_1 <= 1
0 <=              mpy2_n4 <= 1
0 <=              mpy1_n4 <= 1
0 <=              mpy1_n1 <= 1
0 <=              mpy2_n1 <= 1
0 <=              mpy2_n2 <= 1
0 <=              mpy1_n2 <= 1
0 <=                 n4_9 <= 1
0 <=                 n4_8 <= 1
0 <=                 n4_3 <= 1
0 <=                 n4_2 <= 1
0 <=                 n4_1 <= 1
0 <=                 n4_7 <= 1
0 <=                 n4_6 <= 1
0 <=                 n4_5 <= 1
0 <=                 n4_4 <= 1
0 <=               alu_p1 <= 1
0 <=               alu_p3 <= 1
0 <=               alu_p2 <= 1
0 <=               alu_p4 <= 1
0 <=                 n2_1 <= 1
0 <=                 n2_3 <= 1
0 <=                 n2_2 <= 1
0 <=                 n2_5 <= 1
0 <=                 n2_4 <= 1
0 <=                 n2_7 <= 1
0 <=                 n2_6 <= 1
0 <=                 n2_9 <= 1
0 <=                 n2_8 <= 1
0 <=                 p2_9 <= 1
0 <=                 p2_8 <= 1
0 <=                 p2_7 <= 1
0 <=                 p2_6 <= 1
0 <=                 p2_5 <= 1
0 <=                 p2_4 <= 1
0 <=                 p2_3 <= 1
0 <=                 p2_2 <= 1
0 <=                 p2_1 <= 1
0 <=                 p4_9 <= 1
0 <=                 p4_8 <= 1
0 <=                 p4_5 <= 1
0 <=                 p4_4 <= 1
0 <=                 p4_7 <= 1
0 <=                 p4_6 <= 1
0 <=                 p4_1 <= 1
0 <=                 p4_3 <= 1
0 <=                 p4_2 <= 1
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
0 <=              mpy1_n3 <= 1
0 <=              mpy2_n3 <= 1
0 <=               stop_3 <= 1
0 <=               stop_2 <= 1
0 <=               stop_1 <= 1
0 <=               stop_7 <= 1
0 <=               stop_6 <= 1
0 <=               stop_5 <= 1
0 <=               stop_4 <= 1
0 <=               stop_9 <= 1
0 <=               stop_8 <= 1
0 <=                 p1_1 <= 1
0 <=                 p1_2 <= 1
0 <=                 p1_3 <= 1
0 <=                 p1_4 <= 1
0 <=                 p1_5 <= 1
0 <=                 p1_6 <= 1
0 <=                 p1_7 <= 1
0 <=                 p1_8 <= 1
0 <=                 p1_9 <= 1
0 <=            nop_start <= 1
0 <=                 p3_6 <= 1
0 <=                 p3_7 <= 1
0 <=                 p3_4 <= 1
0 <=                 p3_5 <= 1
0 <=                 p3_2 <= 1
0 <=                 p3_3 <= 1
0 <=                 p3_1 <= 1
0 <=                 p3_8 <= 1
0 <=                 p3_9 <= 1
0 <=             p1_START <= 100
0 <=          start_START <= 100
0 <=             p2_START <= 100
0 <=           p4_latency <= 100
0 <=           n4_latency <= 100
0 <=           p2_latency <= 100
0 <=             n2_START <= 100
0 <=             n1_START <= 100
0 <=         stop_latency <= 100
0 <=           p1_latency <= 100
0 <=             p4_START <= 100
0 <=           n1_latency <= 100
0 <=           n3_latency <= 100
0 <=             p3_START <= 100
0 <=             n3_START <= 100
0 <=           n2_latency <= 100
0 <=        start_latency <= 100
0 <=             n4_START <= 100
0 <=           p3_latency <= 100
0 <=           stop_START <= 100
General
	n3_8
	n3_9
	n3_1
	n3_2
	n3_3
	n3_4
	n3_5
	n3_6
	n3_7
	n1_8
	n1_9
	n1_6
	n1_7
	n1_4
	n1_5
	n1_2
	n1_3
	n1_1
	mpy2_n4
	mpy1_n4
	mpy1_n1
	mpy2_n1
	mpy2_n2
	mpy1_n2
	n4_9
	n4_8
	n4_3
	n4_2
	n4_1
	n4_7
	n4_6
	n4_5
	n4_4
	alu_p1
	alu_p3
	alu_p2
	alu_p4
	n2_1
	n2_3
	n2_2
	n2_5
	n2_4
	n2_7
	n2_6
	n2_9
	n2_8
	p2_9
	p2_8
	p2_7
	p2_6
	p2_5
	p2_4
	p2_3
	p2_2
	p2_1
	p4_9
	p4_8
	p4_5
	p4_4
	p4_7
	p4_6
	p4_1
	p4_3
	p4_2
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
	mpy1_n3
	mpy2_n3
	stop_3
	stop_2
	stop_1
	stop_7
	stop_6
	stop_5
	stop_4
	stop_9
	stop_8
	p1_1
	p1_2
	p1_3
	p1_4
	p1_5
	p1_6
	p1_7
	p1_8
	p1_9
	nop_start
	p3_6
	p3_7
	p3_4
	p3_5
	p3_2
	p3_3
	p3_1
	p3_8
	p3_9
End
