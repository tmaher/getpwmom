CC = cc

ask_mom: ask_mom.o getpwmom.o
	$(CC) -o ask_mom $^

clean:
	$(RM) -f ask_mom *.o

all: ask_mom

test: all
	./ask_mom

