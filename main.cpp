#include "Game.h"
#include "Tests.h"

// Flip to true to launch the Test Tavern instead of the main game loop.
// Set to false before shipping or pushing a playable build.
#define RUN_TESTS true

// Signal handling for Mac/Linux — suppresses terminal resize interrupts.
// Uncomment when running on Mac to prevent the input loop from breaking on fullscreen.
// #include <signal.h>

int main() {
    Game  game;
    Tests tests;

    if (RUN_TESTS) {
        tests.runTests(game);
        return 0;
    }

    // Uncomment on Mac:
    // signal(SIGWINCH, SIG_IGN);

    game.run();
    return 0;
}