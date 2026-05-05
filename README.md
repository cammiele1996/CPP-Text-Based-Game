# Dragon Slayer — C++ Text-Based RPG

A text-based adventure RPG built in C++ using object-oriented design principles.

---

## Story

You wake up in a tavern with no memory. You were hired to slay a dragon — and got blackout drunk the night before, knowing you'd probably die anyway. Through exploration, NPC interactions, and quests, you piece together your identity, gather the gear you need, and face the dragon in its lair.

---

## Features

- **Full OOP architecture** — Player, Room, Enemy, NPC, Item, and Game classes
- **Dynamic enemy spawning** — Enemy types and locations are randomized each playthrough
- **Difficulty scaling** — Easy, Medium, and Hard modes affect enemy count and stats
- **Exploration system** — Visited room tracking, unknown exits, and a secret tunnel
- **Quest chain** — NPC dialogue and item progression drive the story forward
- **Risk system** — Searching or taking items in rooms with enemies triggers a risk check
- **Character creation** — Custom name, age, and description at the start of each run

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

---

## Enemies

| Enemy | Health | Attack | Defense |
|---|---|---|---|
| Young Goblin | 30 | 5 | 2 |
| Elder Goblin | 50 | 8 | 5 |
| Skeleton Warrior | 50 | 8 | 3 |
| Thief | 40 | 7 | 4 |
| Orc | 60 | 10 | 5 |
| Troll | 80 | 12 | 8 |

*Stats scale with difficulty.*

---

## Commands

| Command | Description |
|---|---|
| `go north/south/east/west` | Move in a direction |
| `search` | Search the current room |
| `take` | Pick up an item |
| `talk to [name]` | Talk to an NPC |
| `fight` | Engage enemies in combat |
| `inventory` | View your inventory |
| `status` | View your stats |
| `help` | List all commands |
| `quit` | Quit the game |

---

## File Structure

```
main.cpp       — Entry point
Game.h/.cpp    — Core game loop, input processing, and world management
Player.h/.cpp  — Player stats, inventory, and character data
Enemy.h/.cpp   — Enemy attributes and damage handling
Item.h/.cpp    — Item definitions
NPC.h/.cpp     — NPC dialogue and interaction
Room.h/.cpp    — Room connections, contents, and state
Utils.h        — Display utilities (borders, wrapping, screen clear)
```

---

## Status

Work in progress. Currently implemented:

- [x] Full map and room connections
- [x] Movement and visited room tracking
- [x] Character creation and difficulty selection
- [x] Dynamic enemy spawning with difficulty scaling
- [x] Search, take, inventory, status, help
- [x] NPC dialogue system (basic)
- [x] Secret tunnel with death trap
- [x] Risk check system
- [ ] Turn-based combat
- [ ] Quest-state aware NPC dialogue
- [ ] Win and lose conditions
- [ ] ImGui GUI with Blender room backgrounds

---

## Built With

- C++
- Visual Studio 2022

---

*First year CS project — built for learning, designed to be fun.*
