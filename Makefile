CC= cc
CFLAGS= -Wall -Wextra -g
LDFLAGS=
LIBS= -lm

PROG= wham
ALL_O= args.o common.o main.o message.o pmf.o

$(PROG): $(ALL_O)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROG) $(ALL_O) $(LIBS)

check: $(PROG)
	./$(PROG) -v -p 6.28 -i butane.dat > butane.out
	diff butane.out butane.ref

clean:
	rm -f *.core *.o butane.out $(PROG)

.PHONY: check clean
