LIBS=-lsfml-graphics -lsfml-window -lsfml-system 

all: main.o
	@echo "** Building the game"
	g++ -o game main.o $(LIBS)

main.o:
	g++ -c main.cpp -o main.o

clean:
	@echo "** Removing object files and executable..."
	rm -f game
	rm -f main.o

