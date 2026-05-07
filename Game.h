#pragma once
#include <vector>
#include "Room.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include <string>
#include <set>

// This class represents the main game logic and state management for the text - based adventure game.
// The Game class manages the player's interactions with the game world, including moving between rooms, 
// searching for items, fighting enemies, and tracking the player's progress towards winning or losing the game. 
// It also handles user input and displays relevant information to the player based on their actions and the current state of the game world.


class Game {
private:
	Player player;                          // The player character, represented by an instance of the Player class, which contains attributes such as health, attack power, defense, and inventory.
	Room* currentRoom = nullptr;            // A pointer to the current room the player is in, represented by an instance of the Room class, which contains information about the room's name, description, items, enemies, and connections to other rooms.
	bool gameOver = false;                  // A boolean flag indicating whether the game has ended, either by winning or losing. This flag is used to control the main game loop and determine when to display end game messages and exit the game.
	std::string difficulty;					// A string variable to store the selected difficulty level of the game, which may affect various aspects of the game such as enemy strength, item availability, and overall challenge for the player.
	std::vector<Enemy*> enemies;            // A vector of pointers to Enemy objects representing the enemies present in the game world. This allows the game to manage and interact with multiple enemies as the player explores different rooms and encounters various challenges.
	std::vector<Room*> rooms;               // A vector of pointers to Room objects representing all the rooms in the game world. This allows the game to manage and navigate between different rooms as the player moves through the game world.
	std::set<std::string> talkedTo;         // A set of strings to track which NPCs the player has talked to. This allows the game to manage dialogue interactions and ensure that the player receives appropriate responses from NPCs based on their previous interactions.
    std::set<std::string> questsComplete;   // A set of strings to track which quests the player has completed. This allows the game to manage quest progression and ensure that the player receives appropriate rewards and guidance based on their completed quests.
	std::set<std::string> visitedRooms;     // A set of strings to track which rooms the player has visited. This allows the game to manage room exploration and ensure that the player receives appropriate information and interactions based on their previous visits.

public:
    void run();                             // Call the main game loop
	void setup();                           // Set up the game world, including creating rooms, items, NPCs, and initializing the player's starting conditions
	void displayRoom();                     // Display the current room's name, description, items, NPCs, enemies, and available exits to the player
	void move(std::string direction);       // Move the player to a different room based on the input direction (north, south, east, west) and update the current room accordingly
	void search();                          // Allow the player to search the current room for items, NPCs, and enemies, and display the results of the search to the player
	void fight(std::string input);                           // Handle combat interactions between the player and enemies in the current room, including calculating damage, updating health, and determining the outcome of the fight
	bool checkWin();						// Check if the player has met the win condition for the game, such as defeating the dragon in the final boss room, and return true if the win condition is met, otherwise return false
	bool checkLose();						// Check if the player has met the lose condition for the game, such as having their health reduced to zero or being defeated by an enemy, and return true if the lose condition is met, otherwise return false
	void displayInventory();				// Display the player's current inventory, including the items they have collected and their descriptions, to the player
	void displayStatus();					// Display the player's current status, including their health, attack power, defense, and any active quests or completed quests, to the player
	void processInput(std::string input);	// Process the player's input command and execute the corresponding actions in the game, such as moving, searching, fighting, or interacting with NPCs based on the input provided
	void displayHelp();						// Display a list of available commands and their descriptions to the player to assist them in navigating the game and understanding how to interact with the game world
	bool riskCheck();						// Perform a risk check when the player chooses to search a room with enemies, determining whether the player successfully avoids the enemies or takes damage based on a random chance and the player's attributes, and return true if the player successfully avoids the enemies, otherwise return false if the player takes damage
	void take(std::string itemName);							// Handle the player's action to take an item from the current room, allowing them to add the item to their inventory and remove it from the room, while also checking for any conditions or requirements for taking the item, such as needing a specific item or having completed a certain quest before being able to take it
	bool getYesNo();						// Get a yes or no response from the player, validating the input and returning true for yes and false for no, to be used in various decision points in the game where the player needs to make a choice or confirm an action
	Room* findRoom(std::string name);				// Find a room by its name from the list of rooms in the game world and return a pointer to the Room object if found, otherwise return nullptr if no room with the specified name exists
	void talkToNPC(std::string name);				// Handle the player's action to talk to an NPC in the current room, allowing them to engage in dialogue with the NPC and receive information, quests, or rewards based on their interactions and the NPC's role in the game world
	void spawnEncounter(Room* room);				// Spawn a random encounter in the specified room, which may include enemies, NPCs, or events that the player can interact with, adding an element of unpredictability and challenge to the game as the player explores different rooms and encounters various situations
    void spawnGoblins(Room* room);
    void spawnSkeleton(Room* room);
    void spawnThief(Room* room);
    void spawnTroll(Room* room);
    void spawnOrc(Room* room);
    void combatStatus(Enemy*);
};
