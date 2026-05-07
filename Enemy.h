#pragma once
#include <string>

// This class represents an enemy in the game world
// Enemies have unique names, descriptions, and attributes such as health and attack power.

class Enemy {
    private:
        std::string name;           // Name of the enemy
        std::string description;    // Description of the enemy
        int health;                 // Health points of the enemy
        int maxHealth;              // Tracks enemies max health
        int attackPower;            // Attack power of the enemy
		int defense;                // Defense points of the enemy

    public:

        // Constructor
        Enemy(std::string name, std::string description, int health, int maxHealth, int attackPower, int defense);

        // Getters
        std::string getName();          // Returns the name of the enemy
        std::string getDescription();   // Returns the description of the enemy
        int getHealth();                // Returns the health points of the enemy
        int getAttackPower();           // Returns the attack power of the enemy
        void takeDamage(int damage);    // Reduces the enemy's health by the damage amount
		int getDefense();              // Returns the defense points of the enemy
        int getMaxHealth();             // Returns enemy's max health

        // Setters
		void setName(std::string name);                 // Set the name of the enemy
        void setDescription(std::string description);   // Set the description of the enemy
        void setHealth(int health);                     // Set the health points of the enemy
		void setAttackPower(int attackPower);           // Set the attack power of the enemy
		void setDefense(int defense);                   // Set the defense points of the enemy
        void setMaxHealth(int maxHealth);                            // Set max health of the enemy
};
