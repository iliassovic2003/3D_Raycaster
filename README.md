# 3D Raycaster - A Tribute to Classic FPS Games

"Maybe when I grow up, I'll be John Carmack," said many in the earlier generation. Mimicking one of the first and original first-person shooters—created using raycaster technology—was once just a dream. But today, this dream is achievable. This project is my humble attempt to dive into the art of raycasting and introduce you to its principles with a working demo. Enjoy the experience!

---

## 🚀 Overview

This project implements a raycasting engine in C, inspired by the techniques used in classic games like **Wolfenstein 3D**. Raycasting is a rendering technique that creates a 3D perspective from a 2D map by simulating rays.

### Key Features:
- Fast and efficient rendering using pure C.
- Utilizes the lightweight MiniLibX graphics library.
- Support for textured walls, sprites, and floor/ceiling effects.
- Player movement, collision detection, and interactable doors.
- Configurable resolution and rendering parameters.
- Functional **minimap** for navigation (limited for large maps).

---

## 🛠️ Requirements

To build and run the project, you'll need the following:
- A compatible C compiler (e.g., GCC).
- Standard C libraries.
- A uniprocessor system (minimum requirements).
- `Make` for building executables.

### For Linux:
Ensure you have the following dependencies installed:
- `xorg`, `libxext-dev`, `libbsd-dev` for MiniLibX.

---

## 🧩 Installation

Clone the repository and build the project using `make`:

```bash
# Clone the repository
git clone https://github.com/iliassovic2003/3D_Raycaster.git

# Navigate to the project directory
cd 3D_Raycaster

# Build the project
make
```

---

## 🕹️ Usage

To run the application, use the following command:

```bash
./Cub3D maps/<choose_any_map>
```

### Controls:
- **W**: Move forward
- **S**: Move backward
- **A**: Strafe left
- **D**: Strafe right
- **←/→**: Rotate camera
- **M**: Toggle minimap
- **F**: Open/close doors
- **ESC**: Exit the application
- **Mouse Left/Right Movement**: Camera rotation

---

## ⚙️ Configuration

You can modify gameplay settings using the `<mapName>.map` files:
- Set textures for walls and items based on direction.
- Define floor and ceiling colors.
- Customize player and keycard spawn locations.
- Create new map layouts for custom experiences!

---

## 🔬 How It Works

The raycasting engine follows these steps:
1. **Raycasting**: Cast rays from the player's perspective across the field of view. Each ray represents a column of pixels on the screen.
2. **DDA Algorithm**: Calculate intersections of each ray with walls based on direction.
3. **Distance Calculation**: Compute perpendicular distances to correct for the fisheye effect.
4. **Height Calculation**: Determine the height of walls and objects based on their distance.
5. **Texture Mapping**: Apply textures to walls, floors, and ceilings.
6. **Rendering**: Render the scene column by column for fast 3D visualization.

---

## 📂 Contributing

Contributions are welcome! Here’s how you can help improve this project:
- Report bugs using the **Issues** tab.
- Suggest new features or enhancements.
- Submit a Pull Request with your changes.

---

## 🪪 License

This project is licensed under the **MIT License**. For more details, please refer to the [LICENSE](LICENSE) file.

---

## 📜 Acknowledgments

- Special thanks to **MiniLibX** for providing a lightweight graphics framework.
- Classic raycasting techniques inspired by games like **Wolfenstein 3D**.
- Group project done with @maywanel
