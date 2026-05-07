#include "Enemy.h"

using namespace std;

// Initializes the enemy. health and maxHealth should match on creation.
Enemy::Enemy(std::string name, std::string description, int health, int maxHealth, int attackPower, int defense) {
    this->name = name;
    this->description = description;
    this->health = health;
    this->maxHealth = maxHealth;
    this->attackPower = attackPower;
    this->defense = defense;
}

// --- Getters ---

string Enemy::getName() { return name; }
string Enemy::getDescription() { return description; }
int    Enemy::getHealth() { return health; }
int    Enemy::getMaxHealth() { return maxHealth; }
int    Enemy::getAttackPower() { return attackPower; }
int    Enemy::getDefense() { return defense; }

// Subtracts damage from current health. Health can go negative — caller checks for death.
void Enemy::takeDamage(int damage) {
    health -= damage;
}

// --- Setters ---

void Enemy::setName(string name) { this->name = name; }
void Enemy::setDescription(string description) { this->description = description; }
void Enemy::setHealth(int health) { this->health = health; }
void Enemy::setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; }
void Enemy::setAttackPower(int attackPower) { this->attackPower = attackPower; }
void Enemy::setDefense(int defense) { this->defense = defense; }