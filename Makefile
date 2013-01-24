CC = cc

ask_mom: ask_mom.o getpwmom.o
	$(CC) -o ask_mom $^

clean:
	$(RM) -f ask_mom *.o

test_dep: ask_mom

test: test_dep
	./ask_mom

lib/libgetpwmom.so: getpwmom.o
	mkdir -p lib
	$(CC) -fPIC -shared -Wl,-soname,libgetpwmom.so.1 -o lib/libgetpwmom.so.1 $^

all: lib/libgetpwmom.so

