CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -O0 

BINS := count-words base addresses menu_map

all: $(BINS)

count-words: count-words.o
	$(CC) $(CFLAGS) $^ -o $@

base: base.o
	$(CC) $(CFLAGS) $^ -o $@

addresses: addresses.o
	$(CC) $(CFLAGS) $^ -o $@

menu_map: menu_map.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run-%: %
	./$<

clean:
	rm -f *.o $(BINS)

.PHONY: all clean run-%

