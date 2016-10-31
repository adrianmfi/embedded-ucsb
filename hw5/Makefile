# Forrest Brewer 10/27/2009
# Modified by Adrian Fiorito 31/10/2016
CC  = gcc
RM = rm

# CFLAGS  = -g -c -Wall -o$@
CFLAGS  = -O -c -Wall  -o$@

qhsmtst: main.o qhsmelevator.o qepn.o
	$(CC) -ohsmelevator main.o qhsmelevator.o qepn.o

qhsmtst.o: qhsmelevator.c
	$(CC) $(CFLAGS) $<

main.o: main.c
	$(CC) $(CFLAGS) $<

qepn.o: qepn.c
	$(CC) $(CFLAGS) $<

clean:
	-$(RM) *.o hsmelevator



