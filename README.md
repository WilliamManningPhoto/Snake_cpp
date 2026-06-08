# Snake

A classic Snake game built in C++ using SFML.

## How to play

- **WASD** to move
- Eat the red food to grow and score points
- Avoid hitting the walls or yourself

## Building

Requires SFML installed via MSYS2:

```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

Then compile:

```bash
g++ main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system
```
