noclean: compile link

build: compile link clean

compile:
	g++ -c *.cpp
	g++ -c ./game/*.cpp
	g++ -c ./gui/*.cpp
	g++ -c ./utils/*.cpp
	g++ -c ./map/*.cpp
	g++ -c ./enemies/*.cpp
	g++ -c ./towers/*.cpp

link:
	g++ *.o -o towerdefense -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o

wrun:
	towerdefense.exe

lrun:
	./towerdefense
