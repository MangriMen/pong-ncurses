# Pong (terminal)

A simple terminal-based Pong clone written in C using ncurses.

**Features:**
- Two-player gameplay with paddles, ball physics, and scoring.
- Terminal UI via ncurses.
- Configurable builds: `debug` and `release`.

**Requirements:**
- `gcc` (C99 compatible).
- GNU Make.
- ncurses library (`libncursesw`).

**Build & Run:**
```powershell
make              # Build (default)
make debug        # Debug build
make release      # Release build
./bin/pong        # Run
```

**Controls:**
- **Player 1:** `a` (up), `z` (down)
- **Player 2:** `k` (up), `m` (down)
- **Quit:** `q` | **Skip/Advance:** space

**License:**
MIT. See `LICENSE` for details.
