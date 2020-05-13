all: lab26.out

lab26.out: lab26.o sort.o dequeue.o
	gcc lab26.o sort.o dequeue.o -o lab26.out

dequeue.o: dequeue.c
	gcc -c dequeue.c

sort.o: dequeue.o sort.c
	gcc -c sort.c

lab26.o: lab26.c
	gcc -c lab26.c

clean:
	rm -rf *.o lab26.out