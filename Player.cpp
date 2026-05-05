#include "Player.h"

using namespace std;

// Default Constructor
Player::Player() {
    this->firstName = "";
	this->lastName = "";
	this->age = "";
	this->description = "";
    this->health = 100;
    this->attackPower = 10;
    this->defense =5;
}

// Parameterized constructor
Player::Player(string firstName, string lastName, string age, string description, int health, int attackPower, int defense) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
    this->description = description;
    this->health = health;
    this->attackPower = attackPower;
    this->defense = defense;
}

// Getters

// Returns the players first name
string Player::getFirstName() {
    return firstName;
}

string Player::getLastName() {
    return lastName;
}

string Player::getAge() {
    return age;
}

string Player::getDescription() {
    return description;
}

// Returns the players health
int Player::getHealth() {
    return health;
}

// Returns the players attack power
int Player::getAttackPower() {
    return attackPower;
}   

// Returns the players defense
int Player::getDefense() {
    return defense;
}

// Setters

// Sets the players name
void Player::setFirstName(string name) {
    this->firstName = name;
}

void Player::setLastName(string name) {
    this->lastName = name;
}

void Player::setAge(string age) {
    this->age = age;
}

void Player::setDescription(string description) {
    this->description = description;
}

// Sets the players health
void Player::setHealth(int health) {
    this->health = health;
}

// Sets the players attack power
void Player::setAttackPower(int attackPower) {
    this->attackPower = attackPower;
}

// Sets the players defense
void Player::setDefense(int defense) {
    this->defense = defense;
}

// Returns the players inventory
std::vector<Item> Player::getInventory() {
    return inventory;
}

// Adds an item to the players inventory
void Player::addItem(Item item) {
    inventory.push_back(item);
}

void Player::takeDamage(int damage) {
    health -= damage;
}

// Checks if the players inventory contains an item
bool Player::hasItem(string itemName) {
    for (const auto& item : inventory) {
        if (item.getName() == itemName) {
            return true;
        }
    }
    return false;
}


