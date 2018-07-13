CC = gcc
CFLAGS = $(CF) -g -Wall -Werror -Wpedantic -Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline
OUT = mastermind
DEPS = 
OBJ = mastermind.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	@rm -rf *.o

