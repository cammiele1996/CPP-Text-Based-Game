#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <random>


using namespace std;

void Game::setup() {
    
    srand(time(0));

    // Create rooms
	// Calls the Room constructor to create new Room objects with a name and description, and assigns them to pointers.
    Room* tavern = new Room("Tavern", "A lively tavern filled with the sounds of laughter and music.");
	Room* windmill = new Room("Windmill", "An old windmill on the outskirts of town, creaking in the wind.");
	Room* church = new Room("Church", "A small, peaceful church with stained glass windows and a quiet atmosphere.");
    Room* forest = new Room("Forest", "A dense, dim lit forest on the edge of town.");
    Room* blacksmith = new Room("Blacksmith", "A small blacksmith shop with a forge and various weapons on display.");
	Room* castle = new Room("Castle", "An imposing castle with towering walls and a large gate.");
	Room* kitchen = new Room("Castle Kitchen", "A bustling kitchen with the aroma of food and the clatter of pots and pans.");
    Room* dungeon = new Room("Dungeon", "A dark, damp dungeon filled with the stench of decay.");
	Room* townSquare = new Room("Town Square", "The heart of the village, where villagers gather and events take place.");
	Room* mountainPass = new Room("Mountain Pass", "A treacherous path through the mountains, leading to the dragon's lair.");
    Room* lair = new Room("Dragon's Lair", "A cavernous lair filled with treasure and the fearsome dragon.");
	Room* road = new Room("Road Out of Town", "A dusty road leading out of the village and towards the unknown.");



    // Set room connections
    // Tavern connections (Start)
	// The setNorth and setSouth functions are called on the tavern room to establish connections to the gates and village rooms respectively.
    tavern->setNorth(townSquare);
    tavern->setSouth(windmill);
    
	// Windmill connections
    windmill->setNorth(tavern);
	windmill->setEast(road);
    windmill->setWest(church);

	// Church connections
	church->setEast(windmill);

	// Town Square connections
    townSquare->setNorth(castle);
	townSquare->setSouth(tavern);
	townSquare->setEast(blacksmith);
	townSquare->setWest(forest);

    // Forest connections
    forest->setEast(townSquare);

    // Blacksmith connections
    blacksmith->setWest(townSquare);

    // Dungeon connections
    dungeon->setEast(castle);
    
	// Castle connections
	castle->setNorth(mountainPass);
	castle->setSouth(townSquare);
	castle->setEast(kitchen);
	castle->setWest(dungeon);

	// Kitchen connections
	kitchen->setWest(castle);

    // Lair connections
	// The setSouth function is called on the lair room to establish a connection back to the stairs room.
    lair->setSouth(mountainPass);

	// Mountain Pass connections
	mountainPass->setNorth(lair);
	mountainPass->setSouth(castle);

	// Road connections
	road->setWest(windmill);


    // Add rooms to rooms vector
	// Each of the created room pointers is added to the rooms vector using the push_back function, allowing for easy access and management of all rooms in the game.
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



    // Set starting room
    currentRoom = tavern;
    // Commit room to memory
	visitedRooms.insert(currentRoom->getName());

    // Set items in rooms

    // Helmet in Forest
	// An Item object named helmet is created with the name "Helmet", a description, and a boolean indicating that it is required for the final boss. 
    // This item is then added to the f`orest room using the addItem function.
    Item helmet("Helmet", "A sturdy helmet that offers protection against head injuries.", true);
    forest->addItem(helmet);


    // Anti-Dragonfire Shield and Eldrium Ore in Dungeon
	// Two Item objects named shield and ore are created with their respective names, descriptions, and boolean values indicating whether they are required for the final boss.
    Item shield("Anti-Dragonfire Shield", "A shield designed to protect against dragon fire.", true);
    Item ore("Eldrium Ore", "A rare ore that is said to be able to harm dragons.", false);
    dungeon->addItem(shield);
    dungeon->addItem(ore);



    // Set NPC dialogues
	// Dialogue strings are created for each NPC, providing information about the location of items and guidance for the player.
    string elderDialogue = "The Eldrium Ore is in the dungeon. Speak to the guard at the Castle Gates first.";
    string blacksmithDialogue = "I need Eldrium Ore to forge the lance. Talk to the Village Elder.";
    string bartenderDialogue = "Take this ale for courage. You are going to need it.";
    string guardDialogue = "You will need a torch before entering the dungeon. Check by the gate.";



	// Add NPCs to rooms
  
    // Village Elder NPC
	// NPC objects are created for each character, with their respective names, descriptions, and dialogue. 
    // These NPCs are then added to their corresponding rooms using the addNPC function.
    NPC villageElder("Village Elder", "A wise old man.", elderDialogue);
    townSquare->addNPC(villageElder);

    // Blacksmith NPC
    NPC blacksmithNPC("Blacksmith", "A skilled blacksmith.", blacksmithDialogue);
    blacksmith->addNPC(blacksmithNPC);

    // Bartender NPC  
    NPC bartender("Tavern Keeper", "A friendly tavern keeper.", bartenderDialogue);
    tavern->addNPC(bartender);
    
    // Castle Guard NPC
    NPC guard("Castle Guard", "A stern guard.", guardDialogue);
    castle->addNPC(guard);

	// Add enemies

    spawnEncounter(forest);     // Guarenteed spawns in the forest and dungeon
	spawnEncounter(dungeon);
    
	vector<Room*> roamingRooms = { townSquare, castle, mountainPass, kitchen, windmill, church, }; // Possible spawns in town square, castle, and mountain pass
    int roamingCount = 0;
    if (difficulty == "easy") {
        roamingCount = 2;
    } else if (difficulty == "medium") {
        roamingCount = 4;
    } else if (difficulty == "hard") {
        roamingCount = 6;
	}

    shuffle(roamingRooms.begin(), roamingRooms.end(), default_random_engine(time(0)));
    for (int i = 0; i < roamingCount; i++) {
        spawnEncounter(roamingRooms[i]);
    }

}



// Display current room information
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



// Move to a different room based on the direction input
void Game::move(string direction) {
    // Secret tunnel from Forest to Dungeon
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

	Room* nextRoom = nullptr;                                       // Initialize nextRoom to nullptr, which will be used to store the room in the direction the player wants to move
	if (direction == "North" || direction == "north") {             // Check if the input direction is "North" (case-insensitive)
		nextRoom = currentRoom->getNorth();                         // If the direction is north, set nextRoom to the room to the north of the current room
	} else if (direction == "South" || direction == "south") {      // Check if the input direction is "South" (case-insensitive)
        nextRoom = currentRoom->getSouth();                         // If the direction is south, set nextRoom to the room to the south of the current room
    } else if (direction == "East" || direction == "east") {        // Check if the input direction is "East" (case-insensitive)
        nextRoom = currentRoom->getEast();                          // If the direction is east, set nextRoom to the room to the east of the current room
    } else if (direction == "West" || direction == "west") {        // Check if the input direction is "West" (case-insensitive)
        nextRoom = currentRoom->getWest();                          // If the direction is west, set nextRoom to the room to the west of the current room
    }

	if (nextRoom != nullptr) {                      // Check if nextRoom is not nullptr, meaning there is a valid room in the direction the player wants to move
		currentRoom = nextRoom;                     // If there is a valid room, update currentRoom to nextRoom, effectively moving the player to the new room
		visitedRooms.insert(currentRoom->getName()); // Add the name of the new current room to the visitedRooms set to track that the player has visited this room
		displayRoom();                              // After moving to the new room, call displayRoom to show the name and description of the new current room

    } else {
        clearScreen();
        printBorder();
		printCentered("Invalid Direction");
		printCentered("Hint: Try the 'search' command to see available exits.");
        printBorder();
        pause();
        displayRoom();
                                                    //  so display a message indicating that the player cannot go that way
    }
}



// Perform a risk check when searching or taking from a room with enemies
bool Game::riskCheck() {
	if (currentRoom->getEnemies().empty()) {                                    // Check if there are no enemies in the current room by calling getEnemies() and checking if it is empty
        return true;
    }
    clearScreen();
    printBorder();
    printCentered("You see enemies in the room!");
    printBorder();
    cout << "Are you sure you would like to proceed? (yes/no): ";

    if (!getYesNo()) {                                                          // Call getYesNo to get a yes or no response from the player.
        return false;
    }
    clearScreen();
	printBorder();
	printCentered("You decide to proceed...");
    printBorder();
    pause();
    cout << endl;
    int risk = rand() % 100;                                                    // Generate a random number between 0 and 99
    if (risk > 20) {                                                            // 20% chance of success
        clearScreen();
        printBorder();
		printCentered("Success!");
		printCentered("You slipped past unnoticed");
		printBorder();
        pause();
        return true;
    }
	else {                                                                      // If the random number is 20 or less, it means the player has been caught by the enemies.
        clearScreen();
        printBorder();
        printCentered("You were caught by the enemies!");
        printCentered("You have been killed");
        printBorder();
        pause();
        gameOver = true;
        return false;
    }
}



// Search the current room for items, NPCs, enemies, and exits
void Game::search() {
    clearScreen();

	// Display search results
    printBorder();
	printCentered("Searching the " + currentRoom->getName());
	printBorder();
	pause();              // Pause the game to allow the player to read the search header before displaying the room information


    clearScreen();
    printBorder();

	// Items in the room
    printCentered("Items in the " + currentRoom->getName());
    printBorder();
    for (const auto& item : currentRoom->getItems()) {
        cout << " - " << item.getName() << ": " << item.getDescription() << endl;
    }
	if (currentRoom->getItems().empty()) {
        cout << "No items found in this room." << endl;
    }
    printDivider();
	pause();			  // Pause the game to allow the player to read the items in the room before displaying the NPCs and enemies


    clearScreen();
    printBorder();

	// NPCs in the room
	printCentered("NPCs in the " + currentRoom->getName());
    printBorder();
	for (const auto& npc : currentRoom->getNPCs()) {                            // Loop through each NPC in the current room using a range-based for loop
		cout << " - " << npc.getName() << ": " << npc.getDescription() << endl; // Display the name and description of each NPC in the room
    }
    if (currentRoom->getNPCs().empty()) {
        cout << "No NPCs found in this room." << endl;
	}
    printDivider();
    pause();

    clearScreen();
    printBorder();

	// Enemies in the room
	printCentered("Enemies in the " + currentRoom->getName());
    printBorder();
	for (const auto& enemy : currentRoom->getEnemies()) {   // Loop through each enemy in the current room using a range-based for loop
		cout << " - " << enemy->getName() << endl;          // Display the name of each enemy in the room. Note that enemy is a pointer, so we use the arrow operator (->) to access its getName() method.
    }
	if (currentRoom -> getEnemies().empty()) {
        cout << "No enemies found in this room." << endl;
    }
    printDivider();
    pause();

	clearScreen();
    printBorder();

    // Exits from the room
	printCentered("Exits from the " + currentRoom->getName());
    printBorder();
    if (currentRoom->getNorth() != nullptr) {
        string dest = visitedRooms.count(currentRoom->getNorth()->getName()) ? currentRoom->getNorth()->getName() : "Unknown";
        cout << " - North (" << dest << ")" << endl;
    }
    if (currentRoom->getSouth() != nullptr) {
        string dest = visitedRooms.count(currentRoom->getSouth()->getName()) ? currentRoom->getSouth()->getName() : "Unknown";
        cout << " - South (" << dest << ")" << endl;
    }
    if (currentRoom->getEast() != nullptr) {
        string dest = visitedRooms.count(currentRoom->getEast()->getName()) ? currentRoom->getEast()->getName() : "Unknown";
        cout << " - East (" << dest << ")" << endl;
    }
    if (currentRoom->getWest() != nullptr) {
        string dest = visitedRooms.count(currentRoom->getWest()->getName()) ? currentRoom->getWest()->getName() : "Unknown";
        cout << " - West (" << dest << ")" << endl;
    }
    printDivider();
    pause();
    displayRoom();
}



// Main game functionality
void Game::run() {

	// Display welcome message and instructions
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
	
	// Get player's first name
	string playerFirstName;              // Variable to store player's name
	getline(cin, playerFirstName);       // Read the player's name from input
	player.setFirstName(playerFirstName);     // Set the player's name in the Player class
    printDivider();
    // Save this statement for after
	// cout << "Type 'help' for a list of commands." << endl << endl;

	cout << "Last Name: ";

    // Get player's last name
	string playerLastName;               // Variable to store player's last name
	getline(cin, playerLastName);        // Read the player's last name from input
	player.setLastName(playerLastName);     // Set the player's last name in the Player class
    printDivider();

	cout << "Age: ";

	// Get player's age
	string playerAge;                    // Variable to store player's age
	getline(cin, playerAge);                    // Read the player's age from input
	player.setAge(playerAge);              // Set the player's age in the Player class
    printDivider();

	cout << "Description (A few words about yourself): ";

	// Get player's description
	string playerDescription;                    // Variable to store player's description
	getline(cin, playerDescription);        // Read the player's description from input
	player.setDescription(playerDescription);     // Set the player's description in the Player class
    printDivider();
    pause();

    clearScreen();
	printBorder();
	printCentered("Select difficulty level (easy, medium, hard): ");
    printBorder();
	// Get difficulty level
	string selectedDifficulty;
	cout << "> ";
	getline(cin, selectedDifficulty);
    transform(selectedDifficulty.begin(), selectedDifficulty.end(), selectedDifficulty.begin(), ::tolower);
	while (selectedDifficulty != "easy" && selectedDifficulty != "medium" && selectedDifficulty != "hard") {
        displayError();
        clearScreen();
		printBorder();
		printCentered("Select difficulty level (easy, medium, hard): ");
        printBorder();
		cout << "> ";
		getline(cin, selectedDifficulty);
        transform(selectedDifficulty.begin(), selectedDifficulty.end(), selectedDifficulty.begin(), ::tolower);
    }

    clearScreen();
    printBorder();
	if (selectedDifficulty == "easy") {
        printCentered("You have selected EASY difficulty.");
        printCentered("Less powerful enemies and less encounters.");
		printCentered("A good choice for new players or a more relaxed experience.");
    } else if (selectedDifficulty == "medium") {
        printCentered("You have selected MEDIUM difficulty.");
        printCentered("Moderate enemies and a balanced number of encounters.");
		printCentered("This is a good choice for players looking for a standard challenge.");
    } else if (selectedDifficulty == "hard") {
        printCentered("You have selected HARD difficulty.");
        printCentered("Exceptionally powerful enemies and frequent encounters.");
		printCentered("This is a good choice for experienced players looking for a tough challenge.");
    }
    printBorder();

	difficulty = selectedDifficulty;
    printDivider();
    setup();    // Call the setup function to initialize the game world, create rooms, items, NPCs, and set up the player's starting conditions.

    pause();

	// Main game loop
	displayRoom();              // Display the current room information at the start of the game loop
	while (!gameOver) {         // Continue the game loop until the gameOver flag is set to true, which indicates that the game has ended either by winning or losing
		cout << "> ";           // Display a prompt for the player to enter a command
		string input;           // Variable to store the player's input command
		getline(cin, input);    // Read the player's input command from the console
		printDivider();     	// Display a divider after the player's input for better readability
		cout << endl;           // Add an extra line after the divider for better readability
		processInput(input);    // Call the processInput function to handle the player's command and update the game state accordingly based on the input provided
	}

	// Display end game message based on win or lose condition
	if (checkWin()) {   // Call the checkWin function to determine if the player has met the win condition for the game
        cout << "Congratulations! You have defeated the dragon and completed your quest!" << endl;
	}
	else if (checkLose()) {   // Call the checkLose function to determine if the player has met the lose condition for the game
        cout << "Game Over! You have been defeated. Better luck next time!" << endl;
	}
}



// Process player input and execute corresponding actions
void Game::processInput(string input) {
	transform(input.begin(), input.end(), input.begin(), ::tolower); // Convert input to lowercase for case-insensitive comparison

	// Check the player's input against valid commands and call the corresponding functions to execute the desired actions in the game.
	// For example: if the input is "help", call the displayHelp function to show the list of available commands.
	if (input == "help") {
        displayHelp();
        pause();
		displayRoom(); // Redisplay the current room information after showing the help message
    } else if (input == "search") {
        search();
  //      pause();
		//displayRoom(); // Redisplay the current room information after showing the search results
    } else if (input == "inventory") {
        displayInventory();
    } else if (input == "status") {
        displayStatus();
        pause();
		displayRoom(); // Redisplay the current room information after showing the player's status
    } else if (input.substr(0, 3) == "go ") {
        move(input.substr(3));
    } else if (input == "fight") {
        fight();
    } else if (input == "quit") {
        gameOver = true;
	} else if (input == "take") {
        take();
     } else if (input.substr(0, 8) == "talk to ") {
		 talkToNPC(input.substr(8));
         pause();
		 displayRoom(); // Redisplay the current room information after talking to the NPC
    } else {
        displayError();
		displayRoom(); // Redisplay the current room information after showing the invalid command message
    }
}



// Get a yes or no response from the player
// Returns true or false respectively
bool Game::getYesNo() {
    string input;
    while (true) {
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input == "yes") return true;
        if (input == "no") return false;
        cout << "Please enter yes or no: ";
    }
}


// Handle taking an item from the current room
void Game::take() {
    string input;
	cout << "Which item would you like to take? (Enter the item name): " << endl;
	getline(cin, input); // Read the item name from input

    bool found = false;
    for (const auto& item : currentRoom->getItems()) {
		// Check if the input matches the name of any item in the current room (case-insensitive)
        if (item.getName() == input) {
			found = true; // If a matching item is found, set found to true

            if (!riskCheck()) { // Call riskCheck to determine if the player can safely take the item. 
                return;         // If riskCheck returns false, it means the player has chosen not to proceed or has been caught by enemies, so we return early from the take function without taking the item.
			}
            else {
                player.addItem(item); // If riskCheck returns true, it means the player can safely take the item, so we add the item to the player's inventory using the addItem function of the Player class.
                currentRoom->removeItem(item); // After adding the item to the player's inventory, we remove the item from the current room using the removeItem function of the Room class to reflect that the item has been taken by the player.
                clearScreen();
                printBorder();
				printCentered("You have taken the: " + item.getName()); // Display a message confirming that the player has taken the ite
                printBorder();
				pause(); // Pause the game to allow the player to read the confirmation message before redisplaying the current room information
            }
        }
    }
    if (!found) {
        cout << "Item not found in the room." << endl; // If no matching item is found after checking all items in the room, display a message indicating that the item was not found.
    }
    displayRoom();
}


// Display the player's current inventory of items
void Game::displayInventory() {
	cout << "Inventory:" << endl; // Display a header for the player's inventory
    for (const auto& item : player.getInventory()) {
        cout << " - " << item.getName() << ": " << item.getDescription() << endl; // Loop through each item in the player's inventory and display its name and description to the player.
	}
	if (player.getInventory().empty()) {
        cout << " - (empty): Your inventory is empty." << endl; // If the player's inventory is empty, display a message indicating that the inventory is empty.
    }

}



void Game::displayStatus() {
    clearScreen();
    printBorder();
	printCentered("Player Status");
	printBorder();
	cout << " - First Name: " << player.getFirstName() << endl; // Display the player's first name
	cout << " - Last Name: " << player.getLastName() << endl; // Display the player's last name
	cout << " - Age: " << player.getAge() << endl; // Display the player's age
	cout << " - Description: " << player.getDescription() << endl; // Display the player's description
	cout << " - Health: " << player.getHealth() << endl; // Display the player's health
	cout << " - Attack Power: " << player.getAttackPower() << endl; // Display the player's attack power
	cout << " - Defense: " << player.getDefense() << endl; // Display the player's defense
	printDivider();
}



void Game::displayHelp() {
    clearScreen();
	printBorder();
	printCentered("Help - Available Commands");
    printBorder();
	cout << " - help: Display this help message." << endl;
	cout << " - search: Search the current room for items, NPCs, enemies, and exits." << endl;
    cout << " - inventory: Display your current inventory of items." << endl;
	cout << " - status: Display your current health, attack power, and defense." << endl;
	cout << " - go north/south/east/west: Move in the specified direction." << endl;
	printDivider();
}



void Game::fight() {

}



bool Game::checkWin() {
    return false;
}



bool Game::checkLose() {
    return false;
}

Room* Game::findRoom(string name) {
    for (Room* room : rooms) {
        if (room->getName() == name) return room;
    }
    return nullptr;
}

void Game::talkToNPC(string name) {
    string nameLower = name;
    transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);

    for (const auto& npc : currentRoom->getNPCs()) {
        string npcLower = npc.getName();
        transform(npcLower.begin(), npcLower.end(), npcLower.begin(), ::tolower);

        if (npcLower == nameLower) {

			// TODO: Add more complex dialogue interactions based on previous conversations and quests
			// Check questsComplete and talkedTo sets to determine what dialogue to show

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

void Game::spawnEncounter(Room* room) {
	int randNum = rand() % 5;
    switch (randNum)
    {
        case 0:
            room->addEnemy(new Enemy("Elder Goblin", "A gnarled, battle-scarred goblin with milky eyes and a chipped blade, slower than it once was but no less dangerous.", 50, 8, 5));
            room->addEnemy(new Enemy("Young Goblin", "A small, skittish goblin with wide eyes and a crudely sharpened stick — more scared than scary.", 30, 5, 2));
		break;

        case 1:
            room->addEnemy(new Enemy("Skeleton Warrior", "A rattling skeleton clad in rusted armor, wielding a broken sword. It moves with an eerie, unnatural grace.", 50, 8, 3));
            break;

        case 2:
			room->addEnemy(new Enemy("Thief", "A sneaky thief lurking in the shadows, looking for an opportunity to strike. It has a quick attack but low health.", 40, 7, 4));
            break;

        case 3:
            room->addEnemy(new Enemy("Orc", "A brutish orc with green skin, wielding a large axe. It has high health and attack power.", 60, 10, 5));
            break;
        case 4:
			room->addEnemy(new Enemy("Troll", "A hulking troll with mottled green skin, dripping saliva, and a foul stench. It has a powerful attack but is slow and vulnerable to fire.", 80, 12, 8));
            break;
        default:
        break;
    }
    
    for (Enemy* enemy : room->getEnemies()) {
        if (difficulty == "medium") {
            enemy->setHealth(enemy->getHealth() * 1.25);
			enemy->setAttackPower(enemy->getAttackPower() * 1.25);
		}
        else if (difficulty == "hard") {
            enemy->setHealth(enemy->getHealth() * 1.5);
            enemy->setAttackPower(enemy->getAttackPower() * 1.5);
            enemy->setDefense(enemy->getDefense() + 3);
        }
	}
}


