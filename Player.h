#pragma once
#include <string>
#include <vector>
#include "Item.h"

// This class represents the user in the game
// The user can create their own name
// The user has health, attack power, and defense attributes
// The player can collect items and has an inventory
// Items may provide benefits or enhancements to the player's stats

class Player {
    private:
        std::string firstName;               // Name of the player
		std::string lastName;                // Last name of the player
		std::string age;                     // Age of the player
		std::string description;             // Description of the player
        int health;                      // Health points of the player
        int attackPower;                 // Attack power of the player
        int defense;                     // Defense points of the player
        std::vector<Item> inventory;    // Inventory of items the player has

    public:

        // Default constructor
        Player();

        // Parameterized constructor
        Player(std::string firstName, std::string lastName, std::string age, std::string description, int health, int attackPower, int defense);

        // Getters
        std::string getFirstName();      // Get the player's first name
		std::string getLastName();       // Get the player's last name
		std::string getAge();			// Get the player's age
		std::string getDescription();		// Get the player's description
        int getHealth();            // Get the player's health
        int getAttackPower();      // Get the player's attack power
        int getDefense();           // Get the player's defense

        // Setters
        void setFirstName(std::string name);         // Set the player's name
		void setLastName(std::string name);          // Set the player's last name
		void setAge(std::string age);               // Set the player's age
		void setDescription(std::string description); // Set the player's description
        void setHealth(int health);              // Set the player's health
        void setAttackPower(int attackPower);    // Set the player's attack power
        void setDefense(int defense);            // Set the player's defense

        // Inventory management
        std::vector<Item> getInventory();       // Get the player's inventory
        void addItem(Item item);                 // Add an item to the inventory
        bool hasItem(std::string itemName);      // Check if the inventory contains an item

		// Damage handling
		void takeDamage(int damage);            // Reduce the player's health by the damage amount
    };