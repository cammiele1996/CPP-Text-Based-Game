#pragma once
#include <vector>
#include <string>
#include <set>
#include "Room.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"

// Core game class — manages the game loop, world state, player input, and combat.
// All game logic runs through here. setup() builds the world; run() drives the main loop.

class Tests; // Forward declaration — Tests is a friend class for dev testing

class Game {
private:
    Player player;
    Room* currentRoom = nullptr;
    bool gameOver = false;
    std::string difficulty;              // "easy", "medium", or "hard" — set before setup()

    std::vector<Enemy*> enemies;         // Global enemy list (currently unused — rooms own enemies)
    std::vector<Room*> rooms;            // Master room list — used by findRoom()
    std::set<std::string> talkedTo;      // Tracks which NPCs the player has spoken to
    std::set<std::string> questsComplete;// Tracks completed quests for quest-state dialogue (TODO)
    std::set<std::string> visitedRooms;  // Tracks visited rooms — controls unknown exit display

public:

    // --- Core Loop ---
    void run();             // Entry point — character creation, difficulty, then game loop
    void setup();           // Builds rooms, places items/NPCs/enemies. Call after difficulty is set.
    void processInput(std::string input); // Routes player commands to the correct function

    // --- Display ---
    void displayRoom();     // Shows current room name, description, and prompt
    void displayInventory();
    void displayStatus();
    void displayHelp();
    void combatStatus(Enemy* target); // Shows HP comparison and action menu during combat

    // --- Actions ---
    void move(std::string direction);   // Handles movement + special cases (tunnel, road)
    void search();                      // Reveals items, NPCs, enemies, and exits
    void take(std::string itemName);    // Picks up a named item if present
    void fight(std::string input);      // Initiates turn-based combat with a named enemy
    void talkToNPC(std::string name);   // Displays NPC dialogue and logs to talkedTo

    // --- Helpers ---
    bool riskCheck();                   // 80/20 chance to slip past enemies — death on failure
    bool getYesNo();                    // Loops until player enters yes or no
    Room* findRoom(std::string name);   // Returns a room pointer by name, or nullptr

    // --- Win / Lose ---
    bool checkWin();   // TODO: player in Dragon's Lair with all required items
    bool checkLose();  // TODO: player health <= 0

    // --- Enemy Spawning ---
    void spawnEncounter(Room* room); // Rolls a random encounter type and places it in the room
    void spawnGoblins(Room* room);   // Elder + Young Goblin pair
    void spawnSkeleton(Room* room);
    void spawnThief(Room* room);
    void spawnTroll(Room* room);
    void spawnOrc(Room* room);

    friend class Tests; // Grants Tests direct access to private members for dev testing
};