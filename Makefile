main: bin/main

bin/main: src/main.o src/rng.o
	g++ -o bin/main src/main.o src/rng.o -Wall

src/main.o: src/main.cpp
	g++ -o src/main.o src/main.cpp -Iinclude -c -Wall

test: bin/test
	bin/test

bin/test: test/main.o src/rng.o
	g++ -o bin/test test/main.o src/rng.o -lgtest -lgtest_main -Wall

test/main.o: test/main.cpp
	g++ -o test/main.o test/main.cpp -Iinclude -c -Wall

src/rng.o: include/rng.h src/rng.cpp
	g++ -o src/rng.o src/rng.cpp -Iinclude -c -Wall

clean:
	$(RM) bin/* test/*.o src/*.o
