all: clean a3

a3: a3.c
	gcc a3.c -o a3 -fopenmp -Wall -g -std=c99

clean:
	rm -f a3