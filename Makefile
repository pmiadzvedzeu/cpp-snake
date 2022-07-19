all: compile link

compile:
	g++ -c main.cpp
	g++ -c pixel.cpp
	g++ -c border_pixel.cpp
	g++ -c snake_pixel.cpp
	g++ -c food_pixel.cpp

link:
	g++ food_pixel.o snake_pixel.o border_pixel.o pixel.o main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f main *.o
	rm -f sfml-app