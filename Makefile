main: bin/main

bin/main: src/main.o src/rng.o
	g++ -o bin/main src/main.o src/rng.o -O3 -Wall

src/main.o: include/rng.h src/main.cpp
	g++ -o src/main.o src/main.cpp -Iinclude -c -O3 -Wall

test: bin/test
	bin/test

bin/test: test/main.o src/rng.o
	g++ -o bin/test test/main.o src/rng.o -lgtest -lgtest_main -lpthread -O3 -Wall

test/main.o: include/rng.h test/main.cpp
	g++ -o test/main.o test/main.cpp -Iinclude -c -O3 -Wall

src/rng.o: include/rng.h src/rng.cpp
	g++ -o src/rng.o src/rng.cpp -Iinclude -c -O3 -Wall

clean:
	$(RM) bin/* test/*.o src/*.o
