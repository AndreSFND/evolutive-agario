flags = -lglut -lGLU -lGL -Wall

all: build

run: build
	./main

build: Bolinha.o main.o
	@g++ -o main Bolinha.o main.o $(flags)

Bolinha.o: Bolinha.h Bolinha.cpp
	@g++ -c Bolinha.h Bolinha.cpp

main.o: main.cpp
	@g++ -c main.cpp

clean:
	@rm main *.o *.gch
