all: pipe.c
	gcc pipe.c

clean:
	rm a.out

run: all
	./a.out
