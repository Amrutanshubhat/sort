src_files	= main.c $(wildcard src/*.c)
objects 	= $(src_files:.c=.o)
target		= out
cflags 		= clang -std=c2x -Wall -g -O0 -D_GNU_SOURCE 
includes	= -I./include

.PHONY: clean

run			: $(target)
			./$(target)

$(target)	: $(objects)
			$(cflags) -o $@ $^ $(includes)

%.o: %.c
	$(cflags) -c $< -o $@ $(includes)

clean:
	rm $(objects) $(target)
