all: Run
	./Run
	@make clean

Run: pycallbk.o
	gcc -lpython -lgit2 pycallbk.o -o Run

pycallbk.o: pycallbk.c
	gcc -c pycallbk.c

clean:
	@rm -rf *.o
