#include "Game.h"
#include <signal.h>

int main() {
	Game game;      // Create an instance of the Game class to manage the game logic and state
    signal(SIGWINCH, SIG_IGN);
	game.run();     // Call the run method to start the main game loop and begin the adventure
	return 0;       // Return 0 to indicate that the program has ended successfully
}
