#include "Game.hpp"
#include <ctime>

int main () {
    srand(time(NULL));
    Game game;
    game.Run();
    return 0;
}