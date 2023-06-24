tp3: main.c tratastring.o algoritmos.o
	gcc -g main.c tratastring.o algoritmos.o -o tp3

tratastring.o: tratastring.c tratastring.h
	gcc -c tratastring.c

algoritmos.o: algoritmos.c algoritmos.h
	gcc -c algoritmos.c

clean:
	rm *.o 
	rm tp3
	rm *.out