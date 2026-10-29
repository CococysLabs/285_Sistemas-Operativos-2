.PHONY: all clean test

all: reemplazo toca

reemplazo: reemplazo.c
	$(CC) -Wall -Wextra -O2 -std=c11 $< -o $@

toca: toca.c
	$(CC) -Wall -Wextra -O2 -std=c11 $< -o $@

test: all
	@./reemplazo | grep -F 'FIFO=10  LRU=9  OPT=7'

clean:
	rm -f reemplazo toca
