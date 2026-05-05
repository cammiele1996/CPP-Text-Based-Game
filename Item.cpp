#include "Item.h"

using namespace std;

// Default constructor
Item::Item() {
    this->name = "";
    this->description = "";
    this->isRequired = false;
}

// Initializes item with name, description, and required status
Item::Item(string name, string description, bool isRequired) {
    this->name = name;
    this->description = description;
    this->isRequired = isRequired;
}

// Returns the item name
string Item::getName() const {
    return name;
}

// Returns the item description
string Item::getDescription() const {
    return description;
}

// Returns true if the item is required for the final boss
bool Item::getIsRequired() const {
    return isRequired;
}
