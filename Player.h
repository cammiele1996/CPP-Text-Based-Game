#pragma once
#include <string>
#include <vector>
#include "Item.h"

// Represents the player character.
// Stats are set at default values and can be modified by items and difficulty.
// Character info (name, age, description) is entered at the start of each run.

class Player {
private:
    std::string firstName;
    std::string lastName;
    std::string age;
    std::string description;
    int health;       // Current HP — starts at 100
    int attackPower;  // Base damage before enemy defense reduction
    int defense;      // Max damage reduction per hit (random 0–defense each hit)
    std::vector<Item> inventory;

public:

    // Default constructor — sets base stats (100 HP, 10 ATK, 5 DEF)
    Player();

    // Parameterized constructor
    Player(std::string firstName, std::string lastName, std::string age,
        std::string description, int health, int attackPower, int defense);

    // Getters
    std::string getFirstName();
    std::string getLastName();
    std::string getAge();
    std::string getDescription();
    int getHealth();
    int getAttackPower();
    int getDefense();

    // Setters
    void setFirstName(std::string name);
    void setLastName(std::string name);
    void setAge(std::string age);
    void setDescription(std::string description);
    void setHealth(int health);
    void setAttackPower(int attackPower);
    void setDefense(int defense);

    // Inventory
    std::vector<Item> getInventory();
    void addItem(Item item);
    bool hasItem(std::string itemName); // Returns true if the item is in the inventory

    // Combat
    void takeDamage(int damage); // Subtracts damage from current health
};