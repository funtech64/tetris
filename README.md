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

- Classic Tetris gameplay
- All 7 standard pieces (I, O, T, S, Z, J, L)
- Line clearing with scoring
- Increasing difficulty levels
- NO external dependencies beyond standard C library
- Works on any Linux system with GCC

## Quick Start

```bash
git clone https://github.com/funtech64/Tetris.git
cd Tetris
make
./tetris
```

## Controls

- **A/D** - Move left/right
- **S** - Soft drop (move down faster)
- **W** - Rotate piece
- **Q** - Quit game

## Installation

To install system-wide:

```bash
make install
```

Then just run `tetris` from anywhere.

To uninstall:

```bash
make uninstall
```

## Compilation Requirements

- GCC (any recent version)
- Standard C library
- POSIX-compliant terminal

That's it. No ncurses, no pkg-config, no other dependencies.

## Tested On

- Ubuntu 20.04+ (including cloud instances)
- Debian 10+
- Any modern Linux distribution

## License

Public Domain - do whatever you want with it.

## Contributing

This is intentionally simple. If you want to add features, please keep the zero-dependency philosophy.

---

*Made with frustration and determination when bsdgames wouldn't install properly.*
