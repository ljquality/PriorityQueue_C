a.out:main.o PriQueue.o
	gcc -o a.out PriQueue.o main.o
PriQueue.o:PriQueue.c PriQueue.h
	gcc -g -c PriQueue.c
main.o:main.c
	gcc -g -c main.c
clean:
	rm main.o priQueue.o a.out