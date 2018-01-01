# Lauren Sherman
# Makefile

seq: seq.o randomStagger.o
	gcc -o seq seq.o randomStagger.o
  
seq.o: seq.c randomStagger.h
	gcc -ansi -pedantic -Wall -g -c seq.c
  
randomStagger.o: randomStagger.c randomStagger.h
	gcc -ansi -pedantic -Wall -g -c randomStagger.c
  
para: para.o randomStagger.o
	gcc -o para para.o randomStagger.o
  
para.o: para.c randomStagger.h
	gcc -ansi -pedantic -Wall -g -c para.c

clean:
	\rm -f *.o seq para
