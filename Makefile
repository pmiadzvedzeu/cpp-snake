all: compile link

compile:
	g++ -c main.cpp

link:
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f main *.o
	rm -f sfml-app