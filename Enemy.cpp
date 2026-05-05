#include "Enemy.h"

using namespace std;

// Initializes enemy with name, description, health, and attack power
Enemy::Enemy(std::string name, std::string description, int health, int attackPower, int defense) {
    this->name = name;
    this->description = description;
    this->health = health;
    this->attackPower = attackPower;
	this->defense = defense;
}

// Getters

// Returns the name of the enemy
string Enemy::getName() {
    return name;
}

// Returns the description of the enemy
string Enemy::getDescription() {
    return description;
}

// Returns the health points of the enemy
int Enemy::getHealth() {
    return health;
}

// Returns the attack power of the enemy
int Enemy::getAttackPower() {
    return attackPower;
}

// Returns the defense points of the enemy
int Enemy::getDefense() {
    return defense;
}

// Reduces the enemy's health by the damage amount
void Enemy::takeDamage(int damage) {
    health -= damage;
}

// Setters
void Enemy::setName(string name) {
    this->name = name;
}

void Enemy::setDescription(string description) {
    this->description = description;
}

void Enemy::setHealth(int health) {
    this->health = health;
}

void Enemy::setAttackPower(int attackPower) {
    this->attackPower = attackPower;
}

void Enemy::setDefense(int defense) {
    this->defense = defense;
}