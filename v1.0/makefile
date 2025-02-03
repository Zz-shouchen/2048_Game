CC = g++
CCFLAGS = -g 
CCLIBS = -lncurses
mygame: main.o Gui.o Game.o Item.o
	$(CC) $(CCFLAGS) -o mygame main.o Gui.o Game.o Item.o $(CCLIBS)

Gui.o: Gui.h Gui.cc
	$(CC) $(CCFLAGS) -c -w -o Gui.o Gui.cc

Game.o: Game.h Game.cc
	$(CC) $(CCFLAGS) -c -o Game.o Game.cc

main.o: main.cc
	$(CC) $(CCFLAGS) -c -o main.o main.cc

Item.o: Item.cc Item.h
	$(CC) $(CCFLAGS) -c -o Item.o Item.cc

clean:
	rm -rf mygame *.o
