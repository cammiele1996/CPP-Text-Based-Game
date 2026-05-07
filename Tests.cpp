#include "Tests.h"
#include <iostream>

using namespace std;

// Prompts for difficulty selection and sets game.difficulty.
// Called before testRoomSetup() and testCombat() to ensure proper enemy scaling.
void Tests::difficultyMenu(Game& game) {
    clearScreen();
    printBorder();
    printCentered("Difficulty Selection");
    printBorder();
    cout << " - 1 - Easy" << endl;
    cout << " - 2 - Medium" << endl;
    cout << " - 3 - Hard" << endl;
    printDivider();
    cout << "> ";

    int difficultyChoice;
    cin >> difficultyChoice;

    switch (difficultyChoice) {
    case 1:  game.difficulty = "easy";   break;
    case 2:  game.difficulty = "medium"; break;
    case 3:  game.difficulty = "hard";   break;
    default:
        cout << "Invalid selection. Defaulting to Easy." << endl;
        game.difficulty = "easy";
        break;
    }
}

// Applies difficulty stat scaling to all enemies currently in game.currentRoom.
// Mirrors the scaling logic in Game::spawnEncounter() for use in manual test spawns.
void Tests::setDifficulty(Game& game) {
    for (Enemy* enemy : game.currentRoom->getEnemies()) {
        if (game.difficulty == "medium") {
            enemy->setHealth(static_cast<int>(enemy->getHealth() * 1.25));
            enemy->setAttackPower(static_cast<int>(enemy->getAttackPower() * 1.25));
        }
        else if (game.difficulty == "hard") {
            enemy->setHealth(static_cast<int>(enemy->getHealth() * 1.5));
            enemy->setAttackPower(static_cast<int>(enemy->getAttackPower() * 1.5));
            enemy->setDefense(enemy->getDefense() + 3);
        }
    }
}

// Main test menu — loops until the program exits.
// Add new test cases here as they are implemented.
void Tests::runTests(Game& game) {
    while (true) {
        clearScreen();
        printBorder();
        printCentered("Test Tavern");
        printBorder();
        printCentered("Which test would you like to run?");
        printDivider();
        cout << endl << " - 1 - Room Setup - Test static and dynamic room configurations" << endl << endl;
        cout << " - 2 - Combat - Test player and enemy interactions" << endl << endl;
        printDivider();
        cout << "> ";

        int testToRun;
        cin >> testToRun;
        cin.ignore(); // Clear leftover newline from cin >> before any getline calls
        printDivider();

        switch (testToRun) {
        case 1:
            difficultyMenu(game);
            testRoomSetup(game);
            break;
        case 2:
            testCombat(game);
            break;
        case 3:
        case 4:
        case 5:
            // Reserved for future tests
            break;
        default:
            cout << "Invalid selection. Please choose a valid test number." << endl;
            break;
        }
    }
}

// Interactive combat test. Resets player stats each round.
// Select an enemy type, set difficulty, then fight.
// Loops until the player chooses to stop.
void Tests::testCombat(Game& game) {
    game.currentRoom = new Room("Combat Guild", "A testing room.");

    while (true) {

        // Reset player stats at the start of each combat round
        game.player.setHealth(100);
        game.player.setAttackPower(10);
        game.player.setDefense(5);

        clearScreen();
        printBorder();
        printCentered(game.currentRoom->getName());
        printBorder();
        cout << endl;
        cout << " -1- Skeleton Warrior" << endl;
        cout << " -2- Thief" << endl;
        cout << " -3- Orc" << endl;
        cout << " -4- Troll" << endl;
        cout << " -5- Elder Goblin" << endl;
        cout << " -6- Young Goblin" << endl;
        cout << " -7- Sir Arden The Strong (Boss Test)" << endl;
        printDivider();
        cout << "> ";

        int enemyType;
        cin >> enemyType;
        cin.ignore();

        // Clear previous enemy and spawn selected type
        switch (enemyType) {
        case 1: game.currentRoom->clearEnemies(); game.spawnSkeleton(game.currentRoom); break;
        case 2: game.currentRoom->clearEnemies(); game.spawnThief(game.currentRoom);    break;
        case 3: game.currentRoom->clearEnemies(); game.spawnOrc(game.currentRoom);      break;
        case 4: game.currentRoom->clearEnemies(); game.spawnTroll(game.currentRoom);    break;
        case 5: game.currentRoom->clearEnemies();
            game.currentRoom->addEnemy(new Enemy("Elder Goblin",
                "A gnarled, battle-scarred goblin with milky eyes and a chipped blade, slower than it once was but no less dangerous.",
                50, 50, 8, 5));
            break;
        case 6: game.currentRoom->clearEnemies();
            game.currentRoom->addEnemy(new Enemy("Young Goblin",
                "A small, skittish goblin with wide eyes and a crudely sharpened stick — more scared than scary.",
                30, 30, 5, 2));
            break;
        case 7: game.currentRoom->clearEnemies();
            game.currentRoom->addEnemy(new Enemy("Sir Arden The Strong",
                "A legendary knight clad in shining armor.",
                150, 150, 20, 10));
            break;
        default: break;
        }

        // Run the fight if an enemy was successfully spawned
        if (!game.currentRoom->getEnemies().empty()) {
            difficultyMenu(game);
            setDifficulty(game);
            game.fight(game.currentRoom->getEnemies()[0]->getName());
        }

        cout << "Run another combat test? (yes/no): ";
        if (!game.getYesNo()) break;
    }
}

// Runs game.setup() and prints a full dump of every room's state:
// name, description, items (with flags), NPCs, enemies, exits, and lock status.
// Loops until the player chooses to stop.
void Tests::testRoomSetup(Game& game) {
    while (true) {
        clearScreen();
        game.setup(); // Reinitializes the world — rooms.clear() at top of setup() prevents duplication

        printBorder();
        cout << endl;
        printCentered("Room Setup Test");
        cout << endl;
        printBorder();

        for (Room* room : game.rooms) {
            cout << "Room: " << room->getName() << endl;
            cout << "Description: " << room->getDescription() << endl;

            cout << "Items: ";
            for (const auto& item : room->getItems()) {
                cout << item.getName() << " ";
                if (item.getIsRequired())        cout << "(Required), ";
                if (item.getIsRequiredForQuest()) cout << "(Quest Item), ";
            }
            cout << endl;

            cout << "NPCs: ";
            for (const auto& npc : room->getNPCs()) {
                cout << npc.getName() << ", ";
            }
            cout << endl;

            cout << "Enemies: ";
            for (Enemy* enemy : room->getEnemies()) {
                cout << enemy->getName() << ", ";
            }
            cout << endl;

            cout << "Exits: "
                << (room->getNorth() ? "North " : "")
                << (room->getSouth() ? "South " : "")
                << (room->getEast() ? "East " : "")
                << (room->getWest() ? "West " : "")
                << endl;

            cout << "Locked: " << (room->isRoomLocked() ? "Yes" : "No") << endl;
            printDivider();
        }

        cin.ignore();
        cout << "Rerun test? (yes/no): ";
        if (!game.getYesNo()) {
            printDivider();
            cout << endl << endl << endl << endl;
            break;
        }
        else {
            printDivider();
            cout << endl << endl << endl << endl;
        }
    }
}