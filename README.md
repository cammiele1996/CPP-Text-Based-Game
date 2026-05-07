# Dragon Slayer — C++ Text-Based RPG (WIP)

I'm a Computer Science major in an accelerated BS program, building this alongside coursework to solidify my C++ skills. If you stumble across this, feel free to read the code and leave feedback.

---

## Story

You wake up in a tavern with no memory. You were hired to slay a dragon — and got blackout drunk the night before, knowing you'd probably die anyway. Through exploration, NPC interactions, and quests, you piece together your identity, gather the gear you need, and face the dragon in its lair.

---

## Features

- **Full OOP architecture** — Player, Room, Enemy, NPC, Item, and Game classes
- **Turn-based combat** — Stab, slash, block, use potion, or run each round
- **Dynamic enemy spawning** — Enemy types and locations are randomized each playthrough
- **Difficulty scaling** — Easy, Medium, and Hard affect enemy count, stats, and potion cooldown
- **Exploration system** — Visited room tracking, unknown exits, and a secret tunnel
- **Risk system** — Searching or taking items with enemies present triggers a risk check
- **Character creation** — Custom name, age, and description at the start of each run
- **Dev test suite** — Isolated `Tests` class with a Test Tavern menu for combat and room setup testing

---

## World Map

```
          [Dragon's Lair]
                |
          [Mountain Pass]
                |
[Dungeon] - [Castle] - [Kitchen]
                |
[Forest] - [Town Square] - [Blacksmith]
                |
             [Tavern] ← start
                |
[Church] - [Windmill] - [Road Out of Town]
```

> There is a secret tunnel connecting the Forest and the Dungeon. Find it yourself.

---

## Enemies

| Enemy | HP | Attack | Defense |
|---|---|---|---|
| Young Goblin | 30 | 5 | 2 |
| Elder Goblin | 50 | 8 | 5 |
| Skeleton Warrior | 50 | 8 | 3 |
| Thief | 40 | 7 | 4 |
| Orc | 60 | 10 | 5 |
| Troll | 80 | 12 | 8 |

*Base stats. HP and attack scale ×1.25 on medium, ×1.5 on hard. Defense +3 on hard. Spawn counts also increase.*

---

## Combat

Each round the player chooses one of five actions:

| Action | Description |
|---|---|
| `stab` | Always deals full attack power — no defense reduction. You hit first, enemy counterattacks. |
| `slash` | Enemy attacks first, you retaliate for `(attackPower × 1.5) - defense`. High risk, high reward. |
| `block` | Reduces incoming damage — 75% on easy, 50% on medium, 30% on hard |
| `use potion` | Heals 40 HP on a cooldown (3 / 5 / 7 turns by difficulty) |
| `run` | 50/50 chance to escape. Failure keeps you in the fight |

---

## Commands

| Command | Description |
|---|---|
| `go north/south/east/west` | Move in a direction |
| `search` | Search the current room |
| `take (item)` | Pick up an item |
| `talk to (name)` | Talk to an NPC |
| `fight (enemy)` | Engage a specific enemy in combat |
| `inventory` | View your inventory |
| `status` | View your stats |
| `help` | List all commands |
| `quit` | Quit the game |

---

## File Structure

```
main.cpp       — Entry point + RUN_TESTS toggle
Game.h/.cpp    — Core game loop, input, world management, and combat
Player.h/.cpp  — Player stats, inventory, and character data
Enemy.h/.cpp   — Enemy attributes, damage handling, and stat scaling
Item.h/.cpp    — Item definitions (boss-required and quest-required flags)
NPC.h/.cpp     — NPC dialogue and interaction
Room.h/.cpp    — Room connections, contents, and state
Utils.h        — Display utilities (borders, wrapping, screen clear, two-sided layout)
Tests.h/.cpp   — Dev test suite (Test Tavern — combat and room setup tests)
```

---

## Status

- [x] Full map and room connections
- [x] Movement and visited room tracking
- [x] Character creation and difficulty selection
- [x] Dynamic enemy spawning with difficulty scaling
- [x] Search, take, inventory, status, help
- [x] NPC dialogue system (basic)
- [x] Secret tunnel with death trap
- [x] Risk check system
- [x] Turn-based combat (stab, slash, block, potion, run)
- [x] Dev test suite (Test Tavern)
- [ ] Quest-state aware NPC dialogue
- [ ] Win and lose conditions
- [ ] Enemy move pools and status effects
- [ ] Checkpoints and save/load system
- [ ] Training Arena game mode
- [ ] ImGui GUI with Blender room backgrounds

---

## Roadmap

### ✅ Phase 0 — Foundation *(complete)*
- [x] Project architecture — Player, Room, Enemy, NPC, Item, Game classes
- [x] Full world map with all room connections
- [x] Movement system with visited room tracking and unknown exits
- [x] Character creation — first name, last name, age, description
- [x] Search — reveals items, NPCs, enemies, and exits per room
- [x] Inventory and status display
- [x] Help screen and invalid command handling
- [x] Secret tunnel (Forest ↔ Dungeon) with torch death trap
- [x] `riskCheck()` — 80/20 chance to slip past enemies when searching or taking
- [x] `take <item>` command with risk check integration
- [x] `talk to <name>` with `talkedTo` set for quest state tracking
- [x] `findRoom()`, `getYesNo()` helpers
- [x] `Utils.h` — clearScreen, printBorder, printDivider, printCentered, printWrapped, printTwoSided, displayError, pause
- [x] Dynamic enemy spawning — 5 enemy types, randomized per room each run
- [x] Spawn helpers — spawnGoblins, spawnSkeleton, spawnThief, spawnOrc, spawnTroll
- [x] Difficulty selection — Easy / Medium / Hard with stat scaling and spawn count scaling
- [x] Road Out of Town — flavor text changes based on quest state, quit prompt
- [x] Turn-based combat — stab, slash, block, use potion, run
- [x] `combatStatus()` — live HP display during combat
- [x] Combat death checks — enemy and player
- [x] Stab/slash damage rebalance — stab guaranteed, slash high risk/high reward
- [x] Dev test suite — Test Tavern with combat and room setup tests
- [x] GitHub repository with README, roadmap, and changelog
- [x] Full comment and formatting pass across all source files

### Phase 1 — Core Game Loop *(current)*
- [ ] Tiered enemy spawning — restrict heavy enemies to deep rooms
- [ ] Gear stat system — items modify player stats on pickup
- [ ] `checkLose()` — death handling and lose screen
- [ ] Mountain Pass / Lair death gate — instant death without shield
- [ ] `checkWin()` — triggers after dragon dies
- [ ] Win and lose screens

### Phase 2 — Quest Chain and Story
- [ ] Quest-state aware NPC dialogue — all key NPCs react to player progress
- [ ] Torch quest — Guard rewards torch after condition is met
- [ ] Blacksmith quest — deliver Eldrium Ore, receive Dragon Lance
- [ ] Suit of Armor — appears in Castle after dungeon is cleared
- [ ] Chaos NPCs — Drunk NPC, Apprentice, Tavern Patrons, Priest, Miller with mixed/false info
- [ ] Decoy items in Church and Windmill
- [ ] Secret tunnel discovery prompt fully implemented
- [ ] Road Out of Town tied to quest state

### Phase 3 — Combat Depth
- [ ] Enemy move pools — each enemy type has its own attack set
- [ ] Status effects — stun, weakened, pickpocketed
- [ ] Enemy phases — behavior shifts below 50% HP
- [ ] Dragon boss fight — dragonfire mechanic, shield requirement, Lance bonus damage, phases
- [ ] Run chance scaling by difficulty
- [ ] Checkpoints and save/load system
- [ ] Training Arena game mode

### Phase 4 — Random NPC Spawning
- [ ] Chaos NPCs spawn randomly each run like enemies
- [ ] Player must read dialogue carefully to separate real info from false

### Phase 5 — Polish and Balance
- [ ] Full balance pass — enemy stats, player progression, difficulty curve
- [ ] Inventory shows stat bonuses from gear
- [ ] Status screen shows base vs equipped stats
- [ ] Comprehensive debug pass — input handling, memory leaks, edge cases

### Phase 6 — ImGui Frontend
- [ ] ImGui GUI replacing terminal output
- [ ] Blender renders as room backgrounds
- [ ] Combat, inventory, and status UI panels

---

## Changelog

### v0.2
- Rebalanced combat — stab now deals guaranteed full attack power with no defense reduction
- Fixed slash formula to apply the 1.5× multiplier before defense reduction
- Fixed enemies dealing damage on the turn they die

### v0.1
- Initial build — core game loop, movement, combat, enemy spawning, difficulty scaling, dev test suite

---

## Built With

- C++
- Visual Studio 2022 / Xcode

---

*Personal project — built for learning, designed to be fun.*
