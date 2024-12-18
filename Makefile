objects 	= main.o insertion.o quicksort.o mergesort.o
target		= out
cflags 		= clang -std=c2x -Wall -g -O0 -D_GNU_SOURCE

.PHONY: clean

run			: $(target)
			./$(target)

$(target)	: $(objects)
			$(cflags) -o $@ $^ $(includes)

%.o: %.c
	$(cflags) -c $< -o $@ $(includes)

clean:
	rm $(objects) $(target)
