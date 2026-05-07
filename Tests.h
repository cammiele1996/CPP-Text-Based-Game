#pragma once
#include "Enemy.h"
#include "Game.h"
#include "Item.h"
#include "Player.h"
#include "Room.h"
#include "Utils.h"
#include <string>
#include <iostream>

// Dev testing suite. Accessed via the RUN_TESTS flag in main.cpp.
// Tests class is a friend of Game — it has direct access to private members.
// All tests are isolated from the main game loop and do not affect save state.

class Tests {

private:
    bool holder; // Placeholder — reserved for future test state tracking

public:

    // Entry point — displays the Test Tavern menu and routes to selected test
    void runTests(Game& game);

    // Verifies room setup: names, descriptions, connections, items, NPCs, and enemy spawns
    void testRoomSetup(Game& game);

    // Interactive combat test — pick an enemy, set difficulty, run a fight
    void testCombat(Game& game);

    // Prompts for difficulty selection and sets game.difficulty
    void difficultyMenu(Game& game);

    // Applies difficulty stat scaling to enemies in game.currentRoom
    void setDifficulty(Game& game);
};