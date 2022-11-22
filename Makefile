CC=gcc
cflags= -Wall -lm
out=lab3
outgame=game.h.gch
outyear=year.h.gch
outfun=functions.h.gch

all:
	$(CC) game.h -s
	$(CC) year.h -s
	$(CC) functions.h -s
	$(CC) lab3.c -o $(out) $(cflags)
clean:
	rm $(out)
fullclean:
	rm -f $(out) $(outgame) $(outyear) $(outfun)