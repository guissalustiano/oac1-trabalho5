FLAGS = -O2 -Wall -Wextra -Wno-unused-variable -std=c99 -fopenmp -lm

.PHONY : all
all : run

database.o: database.h database.c
	gcc -c database.c $(FLAGS) $(ARGS)

database_t.o: database_t.h database_t.c
	gcc -c database_t.c $(FLAGS) $(ARGS)

database_file.o: database_file.h database_file.c
	gcc -c database_file.c $(FLAGS) $(ARGS)

test: main.c database.o database_t.o database_file.o
	gcc -o test main.c database.o database_t.o database_file.o $(FLAGS)

run: test
	rm -rf db && mkdir -p db
	./test

reset:
	sed -i "s/#define ASSOCIATIVITY.*/#define ASSOCIATIVITY 2/" database.h; \

#$ make -s run_brenchmark | tee output.txt
run_brenchmark:
	for i in 1 2 4 8 16 32 64 128 256 512 1024 2048 4096; do \
		sed -i "s/#define ASSOCIATIVITY.*/#define ASSOCIATIVITY $$i/" database.h; \
		make run; \
	done

clean:
	rm -rf *.o test file.db db output.txt
