output: main.o Game.o GameState.o Plane.o Bullet.o Enemy.o Healthbar.o
	g++ -std=c++14 main.o Game.o GameState.o Plane.o Bullet.o Enemy.o Healthbar.o -o output -lsfml-graphics -lsfml-window -lsfml-system

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

Enemy.o: Enemy.cpp Enemy.hpp
	g++ -std=c++14 -c Enemy.cpp

Healthbar.o: Healthbar.cpp Healthbar.hpp
	g++ -std=c++14 -c Healthbar.cpp

clean:
	rm *.o output