SRC_FILES=main.c myprint.c

all: main

main: $(SRC_FILES)
	gcc -pedantic -Wall -Wextra -Wvla -std=c99 -g -o $@ $(SRC_FILES)

clean:
	rm -f main

run: main
	# Running our main function from file main.c
	./main
