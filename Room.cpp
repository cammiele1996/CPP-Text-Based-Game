#include "Room.h"
#include <algorithm>
#include <iostream>

using namespace std;

// Initialize the room
Room::Room(string name, string description) {
    this->name = name;
    this->description = description;
    this->north = nullptr;
    this->south = nullptr;
    this->east = nullptr;
    this->west = nullptr;
    this->isLocked = false;
}

// Getters

// Returns the name of the room
string Room::getName() const {
    return name;
}

// Returns the description of the room
string Room::getDescription() const {
    return description;
}

// Returns the items in the room
vector<Item> Room::getItems() const {
    return items;
}

// Returns the enemies in the room
vector<Enemy*> Room::getEnemies() const {
    return enemies;
}

// Returns the north exit of the room
Room* Room::getNorth() const {
    return north;
}

// Returns the south exit of the room
Room* Room::getSouth() const {
    return south;
}

// Returns the east exit of the room
Room* Room::getEast() const {
    return east;
}

// Returns the west exit of the room
Room* Room::getWest() const {
    return west;
}

// Returns whether the room is locked
bool Room::isRoomLocked() const {
    return isLocked;
}

// Setters

// Sets the north exit of the room
void Room::setNorth(Room* room) {
    north = room;
}

// Sets the south exit of the room
void Room::setSouth(Room* room) {
    south = room;
}

// Sets the east exit of the room
void Room::setEast(Room* room) {
    east = room;
}

// Sets the west exit of the room
void Room::setWest(Room* room) {
    west = room;
}

// Sets whether the room is locked
void Room::setLocked(bool locked) {
    isLocked = locked;
}

// Adds an item to the room
void Room::addItem(const Item& item) {
    items.push_back(item);
}

// Removes an item from the room
void Room::removeItem(const Item& item) {
    for (auto it = items.begin(); it != items.end(); it++) {
        if (it->getName() == item.getName()) {
            items.erase(it);
            break;
        }
    }
}

// Adds an enemy to the room
void Room::addEnemy(Enemy* enemy) {
    enemies.push_back(enemy);
}

// Removes an enemy from the room
void Room::removeEnemy(Enemy* enemy) {
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
        if (*it == enemy) {
            enemies.erase(it);
            break;
        }
    }
}

void Room::addNPC(const NPC& npc) {
    npcs.push_back(npc);
}

std::vector<NPC> Room::getNPCs() const {
    return npcs;
}

void Room::talkToNPC(const std::string& name) const {
    for (const auto& npc : npcs) {
        if (npc.getName() == name) {
            cout << npc.getDialogue() << endl;
            return;
        }
    }
    cout << "NPC not found." << endl;
}
