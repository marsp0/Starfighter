output: main.o Game.o GameState.o Plane.o Bullet.o
	g++ -std=c++14 main.o Game.o GameState.o Plane.o Bullet.o -o output -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -std=c++14 -c main.cpp 

Game.o: Game.cpp Game.hpp
	g++ -std=c++14 -c Game.cpp 

GameState.o: GameState.cpp GameState.hpp
	g++ -std=c++14 -c GameState.cpp

Plane.o: Plane.cpp Plane.hpp
	g++ -std=c++14 -c Plane.cpp

Bullet.o: Bullet.cpp Bullet.hpp
	g++ -std=c++14 -c Bullet.cpp

clean:
	rm *.o output