CFLAGS=-pedantic -Wall -std=c99 -O0
CFILES=./src/sim.c ./src/main.c


all:
	gcc $(CFLAGS) $(CFILES) -o cache-sim

direct:
	./cache-sim -l1size 1024 -l1assoc direct -l2size 2048 -l2assoc direct -l3size  4096 -l3assoc direct 128 fifo gcctrace.txt

assoc:
	./cache-sim -l1size 256 -l1assoc assoc -l2size 256 -l2assoc assoc -l3size 256 -l3assoc assoc 1024 fifo

assocn:
	./cache-sim -l1size 256 -l1assoc assoc:128 -l2size 256 -l2assoc assoc:128 -l3size 256 -l3assoc assoc:128 1024 fifo

clean:
	rm cache-sim
