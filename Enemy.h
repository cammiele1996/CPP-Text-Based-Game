#pragma once
#include <string>

// Represents an enemy in the game world.
// Enemies have stats that scale with difficulty and take damage during combat.

class Enemy {
private:
    std::string name;        // Display name
    std::string description; // Shown when the player searches or encounters the enemy
    int health;              // Current HP
    int maxHealth;           // Starting HP — used for phase checks (e.g. below 50%)
    int attackPower;         // Base damage per hit before defense reduction
    int defense;             // Max damage reduction per hit (random 0–defense each hit)

public:

    // Constructor — health and maxHealth should be set to the same value on creation
    Enemy(std::string name, std::string description, int health, int maxHealth, int attackPower, int defense);

    // Getters
    std::string getName();
    std::string getDescription();
    int getHealth();
    int getMaxHealth();
    int getAttackPower();
    int getDefense();
    void takeDamage(int damage); // Subtracts damage from current health

    // Setters
    void setName(std::string name);
    void setDescription(std::string description);
    void setHealth(int health);
    void setMaxHealth(int maxHealth);
    void setAttackPower(int attackPower);
    void setDefense(int defense);
};