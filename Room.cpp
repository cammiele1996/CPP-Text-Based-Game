#include "Room.h"
#include <algorithm>
#include <iostream>

using namespace std;

// Initializes the room with a name and description. All exits default to nullptr.
Room::Room(string name, string description) {
    this->name = name;
    this->description = description;
    this->north = nullptr;
    this->south = nullptr;
    this->east = nullptr;
    this->west = nullptr;
    this->isLocked = false;
}

// --- Getters ---

string          Room::getName() const { return name; }
string          Room::getDescription() const { return description; }
vector<Item>    Room::getItems() const { return items; }
vector<Enemy*>  Room::getEnemies() const { return enemies; }
vector<NPC>     Room::getNPCs() const { return npcs; }
Room* Room::getNorth() const { return north; }
Room* Room::getSouth() const { return south; }
Room* Room::getEast() const { return east; }
Room* Room::getWest() const { return west; }
bool            Room::isRoomLocked() const { return isLocked; }

// --- Setters ---

void Room::setNorth(Room* room) { north = room; }
void Room::setSouth(Room* room) { south = room; }
void Room::setEast(Room* room) { east = room; }
void Room::setWest(Room* room) { west = room; }
void Room::setLocked(bool locked) { isLocked = locked; }

// --- Item Management ---

void Room::addItem(const Item& item) {
    items.push_back(item);
}

// Removes the first item matching by name
void Room::removeItem(const Item& item) {
    for (auto it = items.begin(); it != items.end(); it++) {
        if (it->getName() == item.getName()) {
            items.erase(it);
            break;
        }
    }
}

// --- Enemy Management ---

void Room::addEnemy(Enemy* enemy) {
    enemies.push_back(enemy);
}

// Removes a specific enemy by pointer match
void Room::removeEnemy(Enemy* enemy) {
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
        if (*it == enemy) {
            enemies.erase(it);
            break;
        }
    }
}

// Deletes all enemy objects and clears the vector — used in test resets and room cleanup
void Room::clearEnemies() {
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}

// --- NPC Management ---

void Room::addNPC(const NPC& npc) {
    npcs.push_back(npc);
}

// Prints dialogue for the named NPC. Case-sensitive — matching handled in Game::talkToNPC().
void Room::talkToNPC(const std::string& name) const {
    for (const auto& npc : npcs) {
        if (npc.getName() == name) {
            cout << npc.getDialogue() << endl;
            return;
        }
    }
    cout << "NPC not found." << endl;
}