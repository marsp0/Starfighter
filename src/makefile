output: main.o Game.o GameState.o Plane.o Bullet.o Enemy.o Healthbar.o Scoreboard.o Button.o MenuState.o HighscoreState.o Grid.o Cell.o
	g++ -std=c++14 -g main.o Game.o GameState.o Plane.o Bullet.o Enemy.o Healthbar.o Scoreboard.o Button.o MenuState.o HighscoreState.o Grid.o Cell.o -o output -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -std=c++14 -c -g main.cpp 

Game.o: Game.cpp Game.hpp
	g++ -std=c++14 -c -g Game.cpp 

GameState.o: GameState.cpp GameState.hpp
	g++ -std=c++14 -c -g GameState.cpp

Plane.o: Plane.cpp Plane.hpp
	g++ -std=c++14 -c -g Plane.cpp

Bullet.o: Bullet.cpp Bullet.hpp
	g++ -std=c++14 -c -g Bullet.cpp

Enemy.o: Enemy.cpp Enemy.hpp
	g++ -std=c++14 -c -g Enemy.cpp

Healthbar.o: Healthbar.cpp Healthbar.hpp
	g++ -std=c++14 -c -g Healthbar.cpp

Scoreboard.o: Scoreboard.cpp Scoreboard.hpp
	g++ -std=c++14 -c -g Scoreboard.cpp

MenuState.o: MenuState.cpp MenuState.hpp
	g++ -std=c++14 -c -g MenuState.cpp

Button.o: Button.cpp Button.hpp
	g++ -std=c++14 -c -g Button.cpp

HighscoreState.o: HighscoreState.cpp HighscoreState.hpp
	g++ -std=c++14 -c -g HighscoreState.cpp

Grid.o: Grid.cpp Grid.hpp
	g++ -std=c++14 -c -g Grid.cpp

Cell.o: Cell.cpp Cell.hpp
	g++ -std=c++14 -c -g Cell.cpp

clean:
	rm *.o output