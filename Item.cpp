#include "Item.h"

using namespace std;

// Default constructor — empty item, not required for anything
Item::Item() {
    this->name = "";
    this->description = "";
    this->isRequired = false;
    this->isRequiredForQuest = false;
}

// Full constructor
Item::Item(string name, string description, bool isRequired, bool isRequiredForQuest) {
    this->name = name;
    this->description = description;
    this->isRequired = isRequired;
    this->isRequiredForQuest = isRequiredForQuest;
}

// --- Getters ---

string Item::getName() const { return name; }
string Item::getDescription() const { return description; }
bool   Item::getIsRequired() const { return isRequired; }
bool   Item::getIsRequiredForQuest() const { return isRequiredForQuest; }

// --- Setters ---

void Item::setIsRequiredForQuest(bool isRequiredForQuest) {
    this->isRequiredForQuest = isRequiredForQuest;
}