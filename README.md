*This project has been created as part of the 42 curriculum by [iliassovic2003](https://github.com/iliassovic2003), [maywanel](https://github.com/maywanel).*

<div align="center">

# 🎮 cub3D — My First RayCaster

**A 3D maze explorer built in C, inspired by the legendary Wolfenstein 3D**

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-Network-000000?style=for-the-badge&logo=42&logoColor=white)
![MiniLibX](https://img.shields.io/badge/MiniLibX-Graphics-orange?style=for-the-badge)
![Makefile](https://img.shields.io/badge/Makefile-Build-red?style=for-the-badge)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

> *"Maybe when I grow up, I'll be John Carmack"* — said everyone who first discovered Wolfenstein 3D.
> Now it's our turn to relive history and Mimic one of the first and original first-person shooters—created using raycaster technology—was once just a dream. But today, this dream is achievable. This project is my humble attempt to dive into the art of raycasting and introduce you to its principles with a working demo. Enjoy the experience!.

</div>

---

## 📖 Description

cub3D is a raycasting engine written from scratch in C, born from the techniques that defined the early FPS genre. Inspired by **Wolfenstein 3D** (Id Software, 1992) — the grandfather of Doom, Quake, and everything that came after — this project takes a 2D map and renders it as a navigable 3D world in real time.

No game engine. No shortcuts. Just math, rays, and pixels.

### ✨ Features

| Feature | Status |
|---|---|
| Directional wall textures (N / S / E / W) | ✅ |
| Configurable floor & ceiling colors | ✅ |
| WASD movement + arrow key camera rotation | ✅ |
| Mouse camera rotation | ✅ Bonus |
| Wall collision detection | ✅ Bonus |
| Interactive doors (open / close) | ✅ Bonus |
| Animated sprites | ✅ Bonus |
| Minimap system | ✅ Bonus |

---

## ⚙️ How It Works

The engine casts one ray per screen column from the player's point of view across the full field of view. For each ray:

1. **DDA Algorithm** — steps through the 2D map grid to find the first wall intersection
2. **Distance correction** — computes the perpendicular distance to fix the fisheye distortion
3. **Wall height** — derives the on-screen column height from the corrected distance
4. **Texture mapping** — samples the correct pixel from the wall texture based on hit position and facing direction
5. **Floor & ceiling** — fills remaining pixels with the configured colors
6. **Sprites & doors** — sorted by distance and rendered on top using a Z-buffer

The result is a smooth first-person perspective rendered column by column, 60 times per second.

---

## 🛠️ Requirements

**Linux only.**

```bash
sudo apt-get install xorg libxext-dev libbsd-dev gcc make
```

---

## 🧩 Installation

```bash
# Clone the repository
git clone https://github.com/iliassovic2003/3D_Raycaster.git
cd 3D_Raycaster

# Build Full Project
make

```

---

## 🕹️ Usage

```bash
./cub3D maps/<map_name>.cub
```

### Controls

| Key | Action |
|---|---|
| `W` `A` `S` `D` | Move forward / strafe left / move back / strafe right |
| `←` `→` | Rotate camera |
| Mouse | Rotate camera (bonus) |
| `F` | Open / close door |
| `M` | Toggle minimap |
| `TAB` | Change Keycards |
| `ESC` | Quit |

---

## 🗺️ Map Format

Maps use the `.cub` extension. Scene elements come first, map grid last.

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111
1000N01
1011001
1000001
1111111
```

| Character | Meaning |
|---|---|
| `1` | Wall |
| `0` | Empty floor |
| `N` `S` `E` `W` | Player spawn + initial orientation |
| ` ` (space) | Void (map must still be closed) |

The map must be entirely surrounded by walls — any open edge will return an error on launch.

---

## 📂 Project Structure

```
.
├── src/              # Core engine source files
├── src_bonus/        # Bonus features (minimap, doors, sprites, mouse)
├── textures/         # Wall and sprite XPM textures
├── maps/             # Sample .cub map files
├── libft/            # Custom C library
├── minilibx/         # MiniLibX graphics library
└── Makefile
```

---

## 📜 Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgd/raycasting.html) — the essential reference
- [DDA Algorithm explained](https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/)
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Wolfenstein 3D source code](https://github.com/id-Software/wolf3d) — the original, open-sourced by Id Software
- [On raycasting math](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)

---

## 👥 About

<div align="center">

Built with too many late cold nights.

[![iliassovic2003](https://img.shields.io/badge/iliassovic2003-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/iliassovic2003)
[![maywanel](https://img.shields.io/badge/maywanel-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/maywanel)

![raycasting](https://img.shields.io/topic/raycasting/raycasting?color=blueviolet&style=flat-square)
![wolfenstein](https://img.shields.io/badge/topic-wolfenstein3d-red?style=flat-square)
![graphics](https://img.shields.io/badge/topic-graphics-orange?style=flat-square)
![42school](https://img.shields.io/badge/topic-42school-black?style=flat-square)
![minilibx](https://img.shields.io/badge/topic-minilibx-blue?style=flat-square)
![game-engine](https://img.shields.io/badge/topic-game--engine-green?style=flat-square)
![c-programming](https://img.shields.io/badge/topic-c--programming-00599C?style=flat-square)
![dda-algorithm](https://img.shields.io/badge/topic-dda--algorithm-yellow?style=flat-square)

</div>