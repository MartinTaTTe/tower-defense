all: compile link

test: compile link clean run

#test utan clean för victor
test2: compile link run

compile:
	g++ -c *.cpp
	g++ -c ./game/app.cpp
	g++ -c ./game/state.cpp
	g++ -c ./game/menu_state.cpp
	g++ -c ./game/game_state.cpp
	g++ -c ./gui/*.cpp
	g++ -c ./utils/*.cpp
	g++ -c ./map/*.cpp

link:
	g++ *.o -o main -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o

run:
	main.exe

ignored:
	g++ -c ./game/*.cpp
	g++ -c ./enemies/*.cpp
	g++ -c ./towers/*.cpp
