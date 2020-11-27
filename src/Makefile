all: compile link

test: compile link run

compile:
	g++ -c *.cpp
	g++ -c ./game/*.cpp
	g++ -c ./map/*.cpp

link:
	g++ *.o -o main -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o

run:
	main.exe

hidden:
	g++ -c ./enemies/*.cpp
	g++ -c ./towers/*.cpp

