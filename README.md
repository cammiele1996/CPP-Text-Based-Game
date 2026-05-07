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
| `stab` | You attack first, then the enemy counterattacks |
| `slash` | Enemy attacks first, you hit for 1.5× damage |
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

## Built With

- C++
- Visual Studio 2022 / Xcode

---

*Personal project — built for learning, designed to be fun.*
