#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include "Enemy.h"
#include "NPC.h"

// Represents a room in the game world.
// Rooms hold items, enemies, and NPCs, and connect to adjacent rooms via cardinal directions.
// The secret Forest <-> Dungeon tunnel is handled in Game::move(), not as a room connection.

class Room {
private:
    std::string name;
    std::string description;
    std::vector<Item> items;
    std::vector<Enemy*> enemies; // Pointers — enemies are heap-allocated and owned by the room
    std::vector<NPC> npcs;
    Room* north = nullptr;
    Room* south = nullptr;
    Room* east = nullptr;
    Room* west = nullptr;
    bool isLocked = false;

public:

    // Constructor
    Room(std::string name, std::string description);

    // Getters
    std::string getName() const;
    std::string getDescription() const;
    std::vector<Item> getItems() const;
    std::vector<Enemy*> getEnemies() const; // Returns a copy — use clearEnemies() or removeEnemy() to modify
    std::vector<NPC> getNPCs() const;
    Room* getNorth() const;
    Room* getSouth() const;
    Room* getEast() const;
    Room* getWest() const;
    bool isRoomLocked() const;

    // Setters — room connections
    void setNorth(Room* room);
    void setSouth(Room* room);
    void setEast(Room* room);
    void setWest(Room* room);
    void setLocked(bool locked);

    // Item management
    void addItem(const Item& item);
    void removeItem(const Item& item); // Matches by name

    // Enemy management
    void addEnemy(Enemy* enemy);
    void removeEnemy(Enemy* enemy);    // Removes a specific enemy by pointer
    void clearEnemies();               // Deletes and removes all enemies — used in test resets

    // NPC management
    void addNPC(const NPC& npc);
    void talkToNPC(const std::string& name) const; // Prints dialogue for a named NPC
};