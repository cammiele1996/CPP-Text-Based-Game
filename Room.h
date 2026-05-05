#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "Enemy.h"
#include "NPC.h"

// This class represents a room in the game
// It contains information about the room's name, description, items, enemies, and connections to other rooms
// Players move through the rooms by interacting with these connections

class Room {

    private:
        std::string name;              // The name of the room
        std::string description;       // A description of the room
        std::vector<Item> items;       // Items present in the room
        std::vector<Enemy*> enemies;   // Enemies present in the room
        std::vector<NPC> npcs;
        Room* north;                   // Pointer to the room to the north
        Room* south;                   // Pointer to the room to the south
        Room* east;                    // Pointer to the room to the east
        Room* west;                    // Pointer to the room to the west
        bool isLocked;                 // Indicates if the room is locked

    public:

        // Constructor
        Room(std::string name, std::string description);

        // Getters
        std::string getName() const;                // Get the name of the room
        std::string getDescription() const;         // Get the description of the room
        std::vector<Item> getItems() const;         // Get the items in the room
        std::vector<Enemy*> getEnemies() const;     // Get the enemies in the room
        Room* getNorth() const;                     // Get the room to the north
        Room* getSouth() const;                     // Get the room to the south
        Room* getEast() const;                      // Get the room to the east
        Room* getWest() const;                      // Get the room to the west
        bool isRoomLocked() const;                  // Check if the room is locked

        // Setters
        void setNorth(Room* room);                  // Set the room to the north
        void setSouth(Room* room);                  // Set the room to the south
        void setEast(Room* room);                   // Set the room to the east
        void setWest(Room* room);                   // Set the room to the west
        void setLocked(bool locked);                // Set the locked status of the room
        void addItem(const Item& item);             // Add an item to the room
        void removeItem(const Item& item);          // Remove an item from the room
        void addEnemy(Enemy* enemy);                // Add an enemy to the room
        void removeEnemy(Enemy* enemy);             // Remove an enemy from the room
        void addNPC(const NPC& npc);                 // Add an NPC to the room
        std::vector<NPC> getNPCs() const;           // Get all NPCs in the room
        void talkToNPC(const std::string& name) const; // Talk to a specific NPC
};