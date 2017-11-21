output: main.o Game.o GameState.o Plane.o Bullet.o Enemy.o Healthbar.o Scoreboard.o Button.o MenuState.o HighscoreState.o
	g++ -std=c++14 main.o Game.o GameState.o Plane.o Bullet.o Enemy.o Healthbar.o Scoreboard.o Button.o MenuState.o HighscoreState.o -o output -lsfml-graphics -lsfml-window -lsfml-system

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

Scoreboard.o: Scoreboard.cpp Scoreboard.hpp
	g++ -std=c++14 -c Scoreboard.cpp

MenuState.o: MenuState.cpp MenuState.hpp
	g++ -std=c++14 -c MenuState.cpp

Button.o: Button.cpp Button.hpp
	g++ -std=c++14 -c Button.cpp

HighscoreState.o: HighscoreState.cpp HighscoreState.hpp
	g++ -std=c++14 -c HighscoreState.cpp

clean:
	rm *.o output