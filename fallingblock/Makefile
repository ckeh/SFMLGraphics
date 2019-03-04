LINK=-lsfml-graphics -lsfml-window -lsfml-system
INCLUDE=-I/usr/include/
LIB=-L/usr/lib/
SRC=src/
COMP=comp/

all: game

line.o: 
	g++ -c $(SRC)line.cpp -o $(COMP)line.o

main.o: 
	g++ -c $(SRC)main.cpp -o $(COMP)main.o

game: line.o main.o
	@echo "** Building the game"
	g++ -o game $(COMP)* $(LINK)

clean:
	@echo "** Removing object files and executable..."
	rm -f game
	rm -f $(COMP)*
