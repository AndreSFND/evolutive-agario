flags = -lglut -lGLU -lGL -Wall

all: build

run: build
	./main

build: Comida.o Bolinha.o main.o
	@g++ -o main Comida.o Bolinha.o main.o $(flags)

Comida.o: Comida.h Comida.cpp
	@g++ -c Comida.h Comida.cpp

Bolinha.o: Bolinha.h Bolinha.cpp
	@g++ -c Bolinha.h Bolinha.cpp

main.o: main.cpp
	@g++ -c main.cpp

clean:
	@rm main *.o *.gch
