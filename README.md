# tetris
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
