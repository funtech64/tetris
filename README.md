# tetris

⚠️ **STATUS: WORK IN PROGRESS** ⚠️  
*Game compiles and runs but controls are not yet responsive like BSD tetris. Looking for contributors to help fix the timing/input handling!*

## Known Issues

- ❌ Controls are sluggish compared to classic BSD tetris
- ✅ Game compiles and runs 
- ✅ All pieces and gameplay work
- ✅ No dependency hell

**Help wanted!** If you know how to make terminal input more responsive like the original BSD games, please contribute!

## Tetris
---

Ubuntu-BSD Tetris... FIXED!! My ###, just give me command-line classic TETRIS!!"
I had been working in git, got frustrated, missed my freeBSD tetris and Ubuntu's symlinks are all bad.

# Ubuntu-BSD Tetris

> *"Just give me command-line classic TETRIS"*

A simple, dependency-free Tetris game that actually compiles and runs without any sh...

## Why This Exists

Because trying to install bsdgames is a nightmare of broken symlinks, missing dependencies, and general frustration. This is a clean, simple Tetris implementation that just works. Prompting for a solution in Claude Sonnet, I actually made the thing F#-Bomb on the chat... 
Well, if it seems to think this is a great idea and it's public domain, so............... :-)

## Features

- Classic Tetris gameplay with smooth controls
- All 7 standard pieces (I, O, T, S, Z, J, L)
- Line clearing with scoring
- Increasing difficulty levels
- Arrow keys + WASD support
- Space bar for instant drop
- Clean NCurses interface

## Quick Start

```bash
# Install dependencies
sudo apt update
sudo apt install gcc libncurses-dev

# Get the game
git clone https://github.com/funtech64/Tetris.git
cd Tetris
make
./tetris

Controls

Arrow Keys or WASD - Move and rotate
Space Bar - Instant drop
Q or ESC - Quit game

Installation
To install system-wide:
bashmake install
Then just run tetris from anywhere.
To uninstall:
bashmake uninstall
Dependencies

GCC compiler
NCurses development library (libncurses-dev)

On Ubuntu/Debian:
bashsudo apt install gcc libncurses-dev
Tested On

Ubuntu 20.04+ (including cloud instances)
Debian 10+
Any modern Linux distribution with NCurses

License
Public Domain - do whatever you want with it.
Contributing
This is intentionally simple. If you want to add features, please keep the zero-external-dependency philosophy.

Created by funtech64 when bsdgames wouldn't install properly.
