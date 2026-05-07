#include "Player.h"

using namespace std;

// Default constructor — base stats, empty character info
Player::Player() {
    this->firstName = "";
    this->lastName = "";
    this->age = "";
    this->description = "";
    this->health = 100;
    this->attackPower = 10;
    this->defense = 5;
}

// Parameterized constructor
Player::Player(string firstName, string lastName, string age, string description,
    int health, int attackPower, int defense) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
    this->description = description;
    this->health = health;
    this->attackPower = attackPower;
    this->defense = defense;
}

// --- Getters ---

string Player::getFirstName() { return firstName; }
string Player::getLastName() { return lastName; }
string Player::getAge() { return age; }
string Player::getDescription() { return description; }
int    Player::getHealth() { return health; }
int    Player::getAttackPower() { return attackPower; }
int    Player::getDefense() { return defense; }

// --- Setters ---

void Player::setFirstName(string name) { this->firstName = name; }
void Player::setLastName(string name) { this->lastName = name; }
void Player::setAge(string age) { this->age = age; }
void Player::setDescription(string description) { this->description = description; }
void Player::setHealth(int health) { this->health = health; }
void Player::setAttackPower(int attackPower) { this->attackPower = attackPower; }
void Player::setDefense(int defense) { this->defense = defense; }

// --- Inventory ---

std::vector<Item> Player::getInventory() { return inventory; }

void Player::addItem(Item item) {
    inventory.push_back(item);
}

// Returns true if an item with the given name exists in the inventory
bool Player::hasItem(string itemName) {
    for (const auto& item : inventory) {
        if (item.getName() == itemName) return true;
    }
    return false;
}

// --- Combat ---

// Subtracts damage from current health. Health can go negative — caller checks for death.
void Player::takeDamage(int damage) {
    health -= damage;
}