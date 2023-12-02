CC=gcc -g -Wall -Wextra
CFILES=$(wildcard src/*/*.c)
HFILES=$(wildcard src/*/include/*.h)
OBJFILES=$(CFILES:.c=.o)
OBJPATH=src/objects/
EXEFILE=bin/main
INPUTFILE=input/input.txt

all:$(OBJFILES)
	$(CC) $(OBJFILES) -o $(EXEFILE) -lm

%.o: %.c $(HFILES)%.h
	$(CC) -c $(CFILES) $< -o $@ -lm

vim:
	nvim $(CFILES) 

run:
	$(EXEFILE) $(INPUTFILE)

debug:
	gdb -q $(EXEFILE)

memcheck:
	valgrind $(EXEFILE) --leak-check=full --read-var-info

clean:
	rm $(OBJFILES)
	rm $(EXEFILE)
