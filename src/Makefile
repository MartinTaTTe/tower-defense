all: compile link

test: compile link clean run

#test utan clean för victor
test2: compile link run

compile:
	g++ -c *.cpp
	g++ -c ./game/*.cpp
	g++ -c ./map/*.cpp
	g++ -c ./gui/*.cpp

link:
	g++ *.o -o main -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o

run:
	main.exe

ignored:
	g++ -c ./enemies/*.cpp
	g++ -c ./towers/*.cpp
	g++ -c ./utils/*.cpp
