"Maybe when i grow up, i'll be John Carmack" said most of earlier generation, has become one of the most possible dream to achieve, to mimic one of the first and original first person shooter to be created, which was created using the raycaster technology.
Today, i am creating a mediocre demo, capable to show you the priniciples of the raycaster, enjoy

## Overview

This project implements a raycasting engine in C, similar to techniques used in classic games like Wolfenstein 3D. Raycasting is a rendering technique that creates a 3D perspective from a 2D map by casting rays from the player's viewpoint and calculating distances to walls.

Key features:
- Fast and efficient rendering in pure C
- Used one of the most basic graphic Clib (mlx)
- Textured walls and sprites
- Player movement and collision detection
- Doors Which can be open and closed using keycards
- Configurable resolution and rendering parameters
- Working minimap (not optimal for big maps)

## Requirements

- GCC or compatible C compiler
- Standard C libraries
- Uniprocessor system at minimum
- Make

## Installation

Clone the repository and build using make:

```bash
git clone https://github.com/iliassovic2003/3D_Raycaster.git
cd 3D_Raycaster
make
```

## Usage

Run the executable:

```bash
./Cub3D maps/<choose any map you want>
```

### Controls

- `W` - Move forward
- `S` - Move backward
- `A` - Strafe left
- `D` - Strafe right
- `←` - Rotate camera left
- `→` - Rotate camera right
- `M` - Toogle minimap
- `F` - Open or Close a Doors
- Mouse rotation Left-Right
- `ESC` - Exit application

## Configuration

Edit the `<mapName>.map` file to modify settings such as:
- Textures used based on Directions
- Floor and ceiling colors
- Player and keys spawns
- Maps design

## How it Works

The raycasting algorithm works by:
1. Cast rays from the player to mimic the field of view
2. The numbers of rays is made sure to send a ray for each width pixel in the middle
3. Using the "DDA" Algorithm, calculating a ray direction
2. Finding where that ray intersects with walls in the 2D map
3. Computing the perpendicular distance to correct for fisheye effect
4. Determining wall height based on distance
5. Applying textures and shading
6. Creating the vertical stripe using the ray

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
