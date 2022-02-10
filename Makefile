#simplechain executable creation
all: simplechain.c
	gcc -g -Wall -o simplechain simplechain.c

clean:
	$(RM) myprog
