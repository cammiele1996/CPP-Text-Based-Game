#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

// Initializes the entire game world — rooms, connections, items, NPCs, and enemy spawns.
// Called after difficulty is set so spawn counts and stat scaling work correctly.
void Game::setup() {
	// Clear any existing game state in case of multiple runs (testing purposes).
    rooms.clear();
    visitedRooms.clear();

    srand(static_cast<unsigned int>(time(nullptr)));

    // --- Create Rooms ---
    Room* tavern       = new Room("Tavern",           "A lively tavern filled with the sounds of laughter and music.");
    Room* windmill     = new Room("Windmill",          "An old windmill on the outskirts of town, creaking in the wind.");
    Room* church       = new Room("Church",            "A small, peaceful church with stained glass windows and a quiet atmosphere.");
    Room* forest       = new Room("Forest",            "A dense, dim lit forest on the edge of town.");
    Room* blacksmith   = new Room("Blacksmith",        "A small blacksmith shop with a forge and various weapons on display.");
    Room* castle       = new Room("Castle",            "An imposing castle with towering walls and a large gate.");
    Room* kitchen      = new Room("Castle Kitchen",    "A bustling kitchen with the aroma of food and the clatter of pots and pans.");
    Room* dungeon      = new Room("Dungeon",           "A dark, damp dungeon filled with the stench of decay.");
    Room* townSquare   = new Room("Town Square",       "The heart of the village, where villagers gather and events take place.");
    Room* mountainPass = new Room("Mountain Pass",     "A treacherous path through the mountains, leading to the dragon's lair.");
    Room* lair         = new Room("Dragon's Lair",     "A cavernous lair filled with treasure and the fearsome dragon.");
    Room* road         = new Room("Road Out of Town",  "A dusty road leading out of the village and towards the unknown.");

    // --- Set Room Connections ---
    // Each room is linked to its neighbors via cardinal directions.
    // The secret Forest <-> Dungeon tunnel is handled separately in move().
    tavern->setNorth(townSquare);
    tavern->setSouth(windmill);

    windmill->setNorth(tavern);
    windmill->setEast(road);
    windmill->setWest(church);

    church->setEast(windmill);

    townSquare->setNorth(castle);
    townSquare->setSouth(tavern);
    townSquare->setEast(blacksmith);
    townSquare->setWest(forest);

    forest->setEast(townSquare);

    blacksmith->setWest(townSquare);

    dungeon->setEast(castle);

    castle->setNorth(mountainPass);
    castle->setSouth(townSquare);
    castle->setEast(kitchen);
    castle->setWest(dungeon);

    kitchen->setWest(castle);

    lair->setSouth(mountainPass);

    mountainPass->setNorth(lair);
    mountainPass->setSouth(castle);

    road->setWest(windmill);

    // --- Add Rooms to Master List ---
    // The rooms vector is used by findRoom() to locate rooms by name.
    rooms.push_back(townSquare);
    rooms.push_back(forest);
    rooms.push_back(blacksmith);
    rooms.push_back(tavern);
    rooms.push_back(kitchen);
    rooms.push_back(windmill);
    rooms.push_back(dungeon);
    rooms.push_back(church);
    rooms.push_back(mountainPass);
    rooms.push_back(lair);
    rooms.push_back(castle);
    rooms.push_back(road);

    // --- Set Starting Room ---
    currentRoom = tavern;
    visitedRooms.insert(currentRoom->getName());

    // --- Place Items ---
    // isRequired (3rd param) flags items needed to face the dragon.
    Item helmet("Helmet",                "A sturdy helmet that offers protection against head injuries.", true, false);
    Item shield("Anti-Dragonfire Shield","A shield designed to protect against dragon fire.",             true, false);
    Item ore   ("Eldrium Ore",           "A rare ore that is said to be able to harm dragons.",           false, true);

    forest->addItem(helmet);
    dungeon->addItem(shield);
    dungeon->addItem(ore);

    // --- Place NPCs ---
    // TODO: Replace static dialogue with quest-state aware dialogue system.
    NPC villageElder("Village Elder", "A wise old man.",          "The Eldrium Ore is in the dungeon. Speak to the guard at the Castle Gates first.");
    NPC blacksmithNPC("Blacksmith",   "A skilled blacksmith.",    "I need Eldrium Ore to forge the lance. Talk to the Village Elder.");
    NPC bartender("Tavern Keeper",    "A friendly tavern keeper.","Take this ale for courage. You are going to need it.");
    NPC guard("Castle Guard",         "A stern guard.",           "You will need a torch before entering the dungeon. Check by the gate.");

    townSquare->addNPC(villageElder);
    blacksmith->addNPC(blacksmithNPC);
    tavern->addNPC(bartender);
    castle->addNPC(guard);

    // --- Spawn Enemies ---
    // Forest and Dungeon always have an encounter. Roaming count scales with difficulty.
    spawnEncounter(forest);
    spawnEncounter(dungeon);

    vector<Room*> roamingRooms = { townSquare, castle, mountainPass, kitchen, windmill, church };
    int roamingCount = 0;
    if      (difficulty == "easy")   roamingCount = 2;
    else if (difficulty == "medium") roamingCount = 4;
    else if (difficulty == "hard")   roamingCount = 6;

    // Shuffle eligible rooms so roaming enemies land in random locations each run.
    const auto roamingSeed = static_cast<default_random_engine::result_type>(time(nullptr));
    shuffle(roamingRooms.begin(), roamingRooms.end(), default_random_engine(roamingSeed));
    for (int i = 0; i < roamingCount; i++) {
        spawnEncounter(roamingRooms[i]);
    }
}



// Displays the current room name, description, and input prompt.
void Game::displayRoom() {
    clearScreen();
    printBorder();
    printCentered(currentRoom->getName());
    printBorder();
    cout << endl;
    cout << currentRoom->getDescription() << endl;
    cout << endl << "What would you like to do?" << endl;
    cout << endl;
    printDivider();
}



// Handles all player movement. Checks for special cases first (secret tunnel, Road Out of Town)
// then falls through to standard directional movement.
void Game::move(string direction) {

    // --- Secret Tunnel: Forest -> Dungeon (north) ---
    // Not shown in search results. No torch = death.
    if (currentRoom->getName() == "Forest" && (direction == "north" || direction == "North")) {
        clearScreen();
        printBorder();
        printCentered("You push deeper into the trees...");
        printBorder();
        printWrapped("Your torch illuminates a narrow tunnel cut into the hillside. Someone made this. Recently.");
        printDivider();
        cout << "Do you follow it? (yes/no): ";
        if (!getYesNo()) {
            displayRoom();
            return;
        }
        if (!player.hasItem("Torch")) {
            clearScreen();
            printBorder();
            printCentered("Darkness.");
            printBorder();
            printWrapped("You follow the tunnel into pitch black. You hear something large moving in the dark. Then nothing.");
            printDivider();
            pause();
            gameOver = true;
            return;
        }
        currentRoom = findRoom("Dungeon");
        visitedRooms.insert(currentRoom->getName());
        displayRoom();
        return;
    }

    // --- Secret Tunnel: Dungeon -> Forest (south) ---
    // Return path through the same tunnel. No torch check on the way back.
    if (currentRoom->getName() == "Dungeon" && (direction == "south" || direction == "South")) {
        clearScreen();
        printBorder();
        printCentered("You notice a narrow tunnel in the south wall...");
        printBorder();
        printWrapped("It looks like it leads back into the forest. The same tunnel you came from, perhaps.");
        printDivider();
        cout << "Do you take it? (yes/no): ";
        if (!getYesNo()) {
            displayRoom();
            return;
        }
        currentRoom = findRoom("Forest");
        visitedRooms.insert(currentRoom->getName());
        displayRoom();
        return;
    }

    // --- Road Out of Town: Windmill -> East ---
    // Flavor text changes based on whether the player has spoken to the Village Elder.
    // Choosing to continue sets gameOver. Turning back returns to the Windmill.
    if (currentRoom->getName() == "Windmill" && direction == "east") {
        clearScreen();
        printBorder();
        printCentered("Road Out of Town");
        printBorder();
        if (talkedTo.count("Village Elder")) {
            printWrapped(
                "You know what's waiting for you up in those mountains. You've always known. "
                "And yet here you are, walking the other way. The Elder's words echo in your head. "
                "You could keep walking. Nobody would know. Except you..."
            );
        } else {
            printWrapped(
                "The road stretches out ahead of you into nothing. You don't know where you're going or why. "
                "Something in the back of your skull is screaming at you to turn around. "
                "On the other hand, your head is still pounding. Maybe leaving is the smart move."
            );
        }
        printDivider();
        cout << "Do you continue down the road and abandon your quest? (yes/no): ";
        if (getYesNo()) {
            gameOver = true;
        } else {
            clearScreen();
            printBorder();
            printCentered("You return to finish your quest.");
            printBorder();
            pause();
            currentRoom = findRoom("Windmill");
            visitedRooms.insert(currentRoom->getName());
            displayRoom();
        }
        return;
    }

    // --- Standard Movement ---
    // Maps direction string to the corresponding room pointer.
    Room* nextRoom = nullptr;
    if      (direction == "north" || direction == "North") nextRoom = currentRoom->getNorth();
    else if (direction == "south" || direction == "South") nextRoom = currentRoom->getSouth();
    else if (direction == "east"  || direction == "East")  nextRoom = currentRoom->getEast();
    else if (direction == "west"  || direction == "West")  nextRoom = currentRoom->getWest();

    if (nextRoom != nullptr) {
        currentRoom = nextRoom;
        visitedRooms.insert(currentRoom->getName());
        displayRoom();
    } else {
        clearScreen();
        printBorder();
        printCentered("Invalid Direction");
        printCentered("Hint: Try the 'search' command to see available exits.");
        printBorder();
        pause();
        displayRoom();
    }
}



// Checks if the player can safely search or take from a room with enemies present.
// Returns true if safe to proceed, false if the player declines or gets caught.
// 80% chance to slip past unnoticed, 20% chance of death.
bool Game::riskCheck() {
    if (currentRoom->getEnemies().empty()) return true;

    clearScreen();
    printBorder();
    printCentered("You see enemies in the room!");
    printBorder();
    cout << "Are you sure you would like to proceed? (yes/no): ";
    if (!getYesNo()) return false;

    clearScreen();
    printBorder();
    printCentered("You decide to proceed...");
    printBorder();
    pause();

    int risk = rand() % 100;
    if (risk > 20) {
        clearScreen();
        printBorder();
        printCentered("Success!");
        printCentered("You slipped past unnoticed.");
        printBorder();
        pause();
        return true;
    } else {
        clearScreen();
        printBorder();
        printCentered("You were caught by the enemies!");
        printCentered("You have been killed.");
        printBorder();
        pause();
        gameOver = true;
        return false;
    }
}



// Searches the current room and displays items, NPCs, enemies, and exits.
// Exits show the room name only if previously visited, otherwise "Unknown".
void Game::search() {
    clearScreen();
    printBorder();
    printCentered("Searching the " + currentRoom->getName());
    printBorder();
    pause();

    // Items
    clearScreen();
    printBorder();
    printCentered("Items in the " + currentRoom->getName());
    printBorder();
    for (const auto& item : currentRoom->getItems()) {
        cout << " - " << item.getName() << ": " << item.getDescription() << endl;
    }
    if (currentRoom->getItems().empty()) cout << "No items found in this room." << endl;
    printDivider();
    pause();

    // NPCs
    clearScreen();
    printBorder();
    printCentered("NPCs in the " + currentRoom->getName());
    printBorder();
    for (const auto& npc : currentRoom->getNPCs()) {
        cout << " - " << npc.getName() << ": " << npc.getDescription() << endl;
    }
    if (currentRoom->getNPCs().empty()) cout << "No NPCs found in this room." << endl;
    printDivider();
    pause();

    // Enemies
    clearScreen();
    printBorder();
    printCentered("Enemies in the " + currentRoom->getName());
    printBorder();
    for (const auto& enemy : currentRoom->getEnemies()) {
        cout << " - " << enemy->getName() << endl;
    }
    if (currentRoom->getEnemies().empty()) cout << "No enemies found in this room." << endl;
    printDivider();
    pause();

    // Exits — shows room name if visited, "Unknown" if not
    clearScreen();
    printBorder();
    printCentered("Exits from the " + currentRoom->getName());
    printBorder();
    if (currentRoom->getNorth()) {
        string dest = visitedRooms.count(currentRoom->getNorth()->getName()) ? currentRoom->getNorth()->getName() : "Unknown";
        cout << " - North (" << dest << ")" << endl;
    }
    if (currentRoom->getSouth()) {
        string dest = visitedRooms.count(currentRoom->getSouth()->getName()) ? currentRoom->getSouth()->getName() : "Unknown";
        cout << " - South (" << dest << ")" << endl;
    }
    if (currentRoom->getEast()) {
        string dest = visitedRooms.count(currentRoom->getEast()->getName()) ? currentRoom->getEast()->getName() : "Unknown";
        cout << " - East (" << dest << ")" << endl;
    }
    if (currentRoom->getWest()) {
        string dest = visitedRooms.count(currentRoom->getWest()->getName()) ? currentRoom->getWest()->getName() : "Unknown";
        cout << " - West (" << dest << ")" << endl;
    }
    printDivider();
    pause();
    displayRoom();
}



// Main entry point for the game. Handles character creation, difficulty selection,
// world setup, and the main input loop.
void Game::run() {

    // --- Welcome Screen + Character Creation ---
    clearScreen();
    printBorder();
    printCentered("Welcome to the Dragon Slayer Adventure Game");
    printBorder();
    printWrapped("Your main quest is to gather the necessary items and defeat the dragon in its lair. Explore the world, talk to NPCs, and find the items you need to succeed.");
    printWrapped("Be careful, as there are enemies lurking in some rooms. You can choose to risk searching or try to avoid them.");
    cout << endl;
    printWrapped("What is your name, brave adventurer?");
    printDivider();

    cout << "First Name: ";
    string playerFirstName;
    getline(cin, playerFirstName);
    player.setFirstName(playerFirstName);
    printDivider();

    cout << "Last Name: ";
    string playerLastName;
    getline(cin, playerLastName);
    player.setLastName(playerLastName);
    printDivider();

    cout << "Age: ";
    string playerAge;
    getline(cin, playerAge);
    player.setAge(playerAge);
    printDivider();

    cout << "Description (A few words about yourself): ";
    string playerDescription;
    getline(cin, playerDescription);
    player.setDescription(playerDescription);
    printDivider();
    pause();

    // --- Difficulty Selection ---
    // Loops until a valid difficulty is entered. Must be set before setup()
    // so enemy spawn counts and stat scaling work correctly.
    clearScreen();
    printBorder();
    printCentered("Select difficulty level (easy, medium, hard):");
    printBorder();
    string selectedDifficulty;
    cout << "> ";
    getline(cin, selectedDifficulty);
    transform(selectedDifficulty.begin(), selectedDifficulty.end(), selectedDifficulty.begin(), ::tolower);
    while (selectedDifficulty != "easy" && selectedDifficulty != "medium" && selectedDifficulty != "hard") {
        displayError();
        clearScreen();
        printBorder();
        printCentered("Select difficulty level (easy, medium, hard):");
        printBorder();
        cout << "> ";
        getline(cin, selectedDifficulty);
        transform(selectedDifficulty.begin(), selectedDifficulty.end(), selectedDifficulty.begin(), ::tolower);
    }

    clearScreen();
    printBorder();
    if (selectedDifficulty == "easy") {
        printCentered("You have selected EASY difficulty.");
        printCentered("Less powerful enemies and fewer encounters.");
        printCentered("A good choice for new players or a more relaxed experience.");
    } else if (selectedDifficulty == "medium") {
        printCentered("You have selected MEDIUM difficulty.");
        printCentered("Moderate enemies and a balanced number of encounters.");
        printCentered("A good choice for players looking for a standard challenge.");
    } else if (selectedDifficulty == "hard") {
        printCentered("You have selected HARD difficulty.");
        printCentered("Exceptionally powerful enemies and frequent encounters.");
        printCentered("A good choice for experienced players looking for a tough challenge.");
    }
    printBorder();

    difficulty = selectedDifficulty;
    setup();
    pause();

    // --- Main Game Loop ---
    displayRoom();
    while (!gameOver) {
        cout << "> ";
        string input;
        getline(cin, input);
        printDivider();
        cout << endl;
        processInput(input);
    }

    // --- End Game ---
    if (checkWin()) {
        cout << "Congratulations! You have defeated the dragon and completed your quest!" << endl;
    } else if (checkLose()) {
        cout << "Game Over! You have been defeated. Better luck next time!" << endl;
    }
}



// Parses player input and routes to the correct function.
// All input is lowercased before comparison.
void Game::processInput(string input) {
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    if (input == "help") {
        displayHelp();
        pause();
        displayRoom();
    } else if (input == "search") {
        search();
    } else if (input == "inventory") {
        displayInventory();
    } else if (input == "status") {
        displayStatus();
        pause();
        displayRoom();
    } else if (input.substr(0, 3) == "go ") {
        move(input.substr(3));
    } else if (input.substr(0, 6) == "fight ") {
        fight(input.substr(6));
    } else if (input == "quit") {
        gameOver = true;
    } else if (input.substr(0, 5) == "take ") {
        take(input.substr(5));
    } else if (input.substr(0, 8) == "talk to ") {
        talkToNPC(input.substr(8));
        pause();
        displayRoom();
    } else {
        displayError();
        displayRoom();
    }
}



// Takes item name as a parameter (passed from processInput via "take <item>").
// Runs a risk check if enemies are present before adding the item to inventory.
void Game::take(string itemName) {
    bool found = false;
    for (const auto& item : currentRoom->getItems()) {
        if (item.getName() == itemName) {
            found = true;
            if (!riskCheck()) return;
            player.addItem(item);
            currentRoom->removeItem(item);
            clearScreen();
            printBorder();
            printCentered("You have taken: " + item.getName());
            printBorder();
            pause();
        }
    }
    if (!found) {
        clearScreen();
        printBorder();
        printCentered("Item not found in this room.");
        printBorder();
        pause();
    }
    displayRoom();
}



// Turn-based combat. Player picks stab, slash, block, use potion, or run each turn.
// Stab: player hits first, then enemy counterattacks.
// Slash: enemy hits first, player hits for 1.5x damage.
// Block: enemy hits but damage is reduced based on difficulty.
// Use Potion: heals 40 HP on a cooldown that scales with difficulty.
// Run: 50/50 chance to escape. Failure keeps the player in the fight.
// On enemy death, it is removed from the room.
void Game::fight(string input) {

    // Find target enemy in current room (case-insensitive match)
    Enemy* target = nullptr;
    string inputLower = input;
    transform(inputLower.begin(), inputLower.end(), inputLower.begin(), ::tolower);

    for (const auto& enemy : currentRoom->getEnemies()) {
        string enemyLower = enemy->getName();
        transform(enemyLower.begin(), enemyLower.end(), enemyLower.begin(), ::tolower);
        if (enemyLower == inputLower) {
            target = enemy;
            break;
        }
    }

    if (target == nullptr) {
        clearScreen();
        printBorder();
        printCentered("Enemy not found in this room.");
        printBorder();
        pause();
        return;
    }

    // --- Combat Loop ---
    int potionCooldown = 0;
    while (target->getHealth() > 0 && player.getHealth() > 0) {

        combatStatus(target);
        cout << "> ";

        string action;
        getline(cin, action);
        transform(action.begin(), action.end(), action.begin(), ::tolower);
        printDivider();

        // Stab — player attacks first, then enemy counterattacks
        if (action == "stab") {
            int playerReduction = rand() % (target->getDefense() + 1);
            int playerDamage    = max(0, player.getAttackPower() - playerReduction);
            target->takeDamage(playerDamage);
            cout << endl << "You stabbed the " << target->getName() << " for " << playerDamage << " damage!" << endl;
            pause();

            combatStatus(target);

            int enemyReduction = rand() % (player.getDefense() + 1);
            int enemyDamage    = max(0, target->getAttackPower() - enemyReduction);
            player.takeDamage(enemyDamage);
            cout << target->getName() << " hit you for " << enemyDamage << " damage!" << endl;
            pause();
        }

        // Slash — enemy attacks first, then player hits for 1.5x damage
        else if (action == "slash") {
            int enemyReduction = rand() % (player.getDefense() + 1);
            int enemyDamage    = max(0, target->getAttackPower() - enemyReduction);
            player.takeDamage(enemyDamage);
            cout << target->getName() << " hit you for " << enemyDamage << " damage!" << endl;
            pause();

            combatStatus(target);

            int playerReduction = rand() % (target->getDefense() + 1);
            int playerDamage    = (int)(max(0, player.getAttackPower() - playerReduction) * 1.5);
            target->takeDamage(playerDamage);
            cout << "You slashed the " << target->getName() << " for " << playerDamage << " damage!" << endl;
            pause();
        }

        // Block — no player attack, incoming damage reduced based on difficulty
        else if (action == "block") {
            int enemyReduction = rand() % (player.getDefense() + 1);
            int enemyDamage    = max(0, target->getAttackPower() - enemyReduction);
            int initialDamage  = enemyDamage;

            if      (difficulty == "medium") enemyDamage = (int)(enemyDamage * 0.50);
            else if (difficulty == "hard")   enemyDamage = (int)(enemyDamage * 0.70);
            else                             enemyDamage = (int)(enemyDamage * 0.25);

            player.takeDamage(enemyDamage);
            cout << "The enemy hit you for " << initialDamage << ", your block reduced it to " << enemyDamage << "." << endl;
            pause();
        }

        // Use Potion — heals 40 HP, cooldown scales with difficulty
        else if (action == "use potion") {
            if (potionCooldown == 0) {
                if      (difficulty == "medium") potionCooldown = 5;
                else if (difficulty == "hard")   potionCooldown = 7;
                else                             potionCooldown = 3;
                player.setHealth(player.getHealth() + 40);
                cout << "You used a potion and healed 40 HP." << endl;
            } else {
                cout << "You can't use your potion for another " << potionCooldown << " turns." << endl;
            }
            pause();
        }

        // Run — 50/50 chance to escape, failure keeps the player in the fight
        else if (action == "run") {
            if (rand() % 2 == 0) {
                clearScreen();
                printBorder();
                printCentered("You failed to escape!");
                printBorder();
                pause();
            } else {
                clearScreen();
                printBorder();
                printCentered("You successfully fled!");
                printBorder();
                pause();
                break;
            }
        }

        // Tick down potion cooldown at the end of every turn
        if (potionCooldown > 0) potionCooldown--;

        // Check if enemy is dead — remove from room and end combat
        if (target->getHealth() <= 0) {
            currentRoom->removeEnemy(target);
            clearScreen();
            printBorder();
            printCentered("You defeated the " + target->getName() + "!");
            printBorder();
            pause();
        }

        if (player.getHealth() <=0) {
            clearScreen();
            printBorder();
            printCentered("You have been defeated by the " + target->getName() + "...");
            printBorder();
            pause();
            gameOver = true;
			//exit(0); // Temporary exit to avoid running end game checks and displaying the win message after death. TODO: Refactor end game handling so this isn't necessary.
		}
    }

    displayRoom();
}



// Displays the player's current inventory.
void Game::displayInventory() {
    clearScreen();
    printBorder();
    printCentered("Inventory");
    printBorder();
    for (const auto& item : player.getInventory()) {
        cout << " - " << item.getName() << ": " << item.getDescription() << endl;
    }
    if (player.getInventory().empty()) {
        cout << " - (empty): Your inventory is empty." << endl;
    }
    printDivider();
}



// Displays the player's current stats and character info.
void Game::displayStatus() {
    clearScreen();
    printBorder();
    printCentered("Player Status");
    printBorder();
    cout << " - Name: "         << player.getFirstName() << " " << player.getLastName() << endl;
    cout << " - Age: "          << player.getAge()         << endl;
    cout << " - Description: "  << player.getDescription() << endl;
    cout << " - Health: "       << player.getHealth()      << endl;
    cout << " - Attack Power: " << player.getAttackPower() << endl;
    cout << " - Defense: "      << player.getDefense()     << endl;
    printDivider();
}



// Displays all available commands.
void Game::displayHelp() {
    clearScreen();
    printBorder();
    printCentered("Help - Available Commands");
    printBorder();
    cout << " - help:                     Display this help message." << endl;
    cout << " - search:                   Search the room for items, NPCs, enemies, and exits." << endl;
    cout << " - inventory:                Display your current inventory." << endl;
    cout << " - status:                   Display your current stats." << endl;
    cout << " - go north/south/east/west: Move in the specified direction." << endl;
    cout << " - take (item):              Pick up an item in the room." << endl;
    cout << " - fight (enemy):            Initiate combat with an enemy." << endl;
    cout << " - talk to (name):           Talk to an NPC." << endl;
    cout << " - quit:                     Quit the game." << endl;
    printDivider();
}



// Win condition — player in Dragon's Lair with all required items. TODO.
bool Game::checkWin() {
    return false;
}



// Lose condition — player health at zero. TODO.
bool Game::checkLose() {
    return false;
}



// Finds a room by name from the master rooms vector. Returns nullptr if not found.
Room* Game::findRoom(string name) {
    for (Room* room : rooms) {
        if (room->getName() == name) return room;
    }
    return nullptr;
}



// Finds an NPC in the current room by name (case-insensitive) and displays their dialogue.
// Adds the NPC name to talkedTo for quest state tracking.
// TODO: Replace with quest-state aware dialogue system.
void Game::talkToNPC(string name) {
    string nameLower = name;
    transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);

    for (const auto& npc : currentRoom->getNPCs()) {
        string npcLower = npc.getName();
        transform(npcLower.begin(), npcLower.end(), npcLower.begin(), ::tolower);

        if (npcLower == nameLower) {
            clearScreen();
            printBorder();
            printCentered("Talking to " + npc.getName());
            printBorder();
            cout << npc.getDialogue() << endl;
            talkedTo.insert(npc.getName());
            printDivider();
            return;
        }
    }
    cout << "No NPC named " << name << " found in this room." << endl;
}



// Spawns a random enemy encounter in the given room.
// randNum picks the encounter type. randNum2 gives a 50/50 chance of a
// double goblin spawn on medium difficulty.
// After spawning, all enemies in the room have stats scaled to difficulty.
void Game::spawnEncounter(Room* room) {
    int randNum  = rand() % 5;
    int randNum2 = rand() % 2;

    switch (randNum) {
        case 0: // Goblins — 1 pair on easy, 50/50 double on medium, always double on hard
            spawnGoblins(room);
            if (difficulty == "medium" && randNum2 == 1) spawnGoblins(room);
            if (difficulty == "hard")                    spawnGoblins(room);
            break;

        case 1: // Skeleton — solo on easy/medium, double on hard
            spawnSkeleton(room);
            if (difficulty == "hard") spawnSkeleton(room);
            break;

        case 2: // Thieves — 3 on easy, 4 on medium, 5 on hard
            spawnThief(room);
            spawnThief(room);
            spawnThief(room);
            if (difficulty == "medium" || difficulty == "hard") spawnThief(room);
            if (difficulty == "hard")                           spawnThief(room);
            break;

        case 3: // Orc — always solo
            spawnOrc(room);
            break;

        case 4: // Troll — always solo
            spawnTroll(room);
            break;

        default:
            break;
    }

    // Scale all enemy stats in the room based on difficulty
    for (Enemy* enemy : room->getEnemies()) {
        if (difficulty == "medium") {
            enemy->setHealth(static_cast<int>(enemy->getHealth() * 1.25));
            enemy->setAttackPower(static_cast<int>(enemy->getAttackPower() * 1.25));
        } else if (difficulty == "hard") {
            enemy->setHealth(static_cast<int>(enemy->getHealth() * 1.5));
            enemy->setAttackPower(static_cast<int>(enemy->getAttackPower() * 1.5));
            enemy->setDefense(enemy->getDefense() + 3);
        }
    }
}



// --- Enemy Spawn Helpers ---
// Each function creates and adds one instance of that enemy type to the room.

void Game::spawnGoblins(Room* room) {
    room->addEnemy(new Enemy("Elder Goblin", "A gnarled, battle-scarred goblin with milky eyes and a chipped blade, slower than it once was but no less dangerous.", 50, 50, 8, 5));
    room->addEnemy(new Enemy("Young Goblin", "A small, skittish goblin with wide eyes and a crudely sharpened stick — more scared than scary.", 30, 30, 5, 2));
}

void Game::spawnSkeleton(Room* room) {
    room->addEnemy(new Enemy("Skeleton Warrior", "A rattling skeleton clad in rusted armor, wielding a broken sword. It moves with an eerie, unnatural grace.", 50, 50, 8, 3));
}

void Game::spawnThief(Room* room) {
    room->addEnemy(new Enemy("Thief", "A sneaky thief lurking in the shadows, looking for an opportunity to strike. It has a quick attack but low health.", 40, 40, 7, 4));
}

void Game::spawnOrc(Room* room) {
    room->addEnemy(new Enemy("Orc", "A brutish orc with green skin, wielding a large axe. It has high health and attack power.", 60, 60, 10, 5));
}

void Game::spawnTroll(Room* room) {
    room->addEnemy(new Enemy("Troll", "A hulking troll with mottled green skin, dripping saliva, and a foul stench. It has a powerful attack but is slow and vulnerable to fire.", 80, 80, 12, 8));
}



// --- Helpers ---

// Prompts for yes/no input and loops until a valid response is given.
bool Game::getYesNo() {
    string input;
    while (true) {
        getline(cin, input);
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "yes") return true;
        if (input == "no")  return false;
        cout << "Please enter yes or no: ";
    }
}

// Displays the current combat state — player HP vs enemy HP and available actions.
// Called at the start of each turn and between attacks to keep HP current.
void Game::combatStatus(Enemy* target) {
    clearScreen();
    printBorder();
    printCentered("Combat  :  " + target->getName());
    printBorder();
    printTwoSided("You", target->getName());
    printTwoSided(to_string(player.getHealth()) + " HP", to_string(target->getHealth()) + " HP");
    printDivider();
    printCentered("Stab | Slash | Block | Use Potion | Run");
    printDivider();
}

