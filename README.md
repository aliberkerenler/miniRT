*This project has been created as part of the 42 curriculum by aerenler, ualkan.*

# miniRT

A minimal ray tracing engine written in C, capable of rendering 3D scenes with spheres, planes, and cylinders using ambient and diffuse lighting.

---

## Description

**miniRT** is a lightweight ray tracer that renders 3D scenes defined in `.rt` configuration files. The project demonstrates fundamental concepts of computer graphics including:

- **Ray-object intersection** algorithms for spheres, planes, and cylinders
- **Lighting model** with ambient and diffuse lighting components
- **Shadow casting** for realistic scene rendering
- **Camera positioning** with configurable field of view

The renderer supports multiple objects in a scene, handles object intersections correctly, and produces images with proper lighting and shadows.

### Features

- ✅ Sphere, plane, and cylinder primitives
- ✅ Ambient and point light sources
- ✅ Configurable camera position, orientation, and FOV
- ✅ Shadow rendering
- ✅ Ambient and diffuse lighting
- ✅ Scene configuration via `.rt` files
- ✅ Window management (resize, minimize, close)
- ✅ Keyboard controls (ESC to exit)

---

## Instructions

### Prerequisites

- **Operating System:** Linux (X11)
- **Compiler:** GCC or Clang with C99 support
- **Libraries:** X11, Xext, math library

On Debian/Ubuntu, install dependencies:
```bash
sudo apt-get install libx11-dev libxext-dev
```

### Compilation

Clone the repository and compile:
```bash
git clone <repository-url> miniRT
cd miniRT
make
```

The `make` command will:
1. Compile the libft library
2. Compile the minilibx-linux library
3. Build the `miniRT` executable

Other make targets:
```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild everything
```

### Execution

Run miniRT with a scene file:
```bash
./miniRT eval_scenes/<scene_file>.rt
```

Example:
```bash
./miniRT eval_scenes/01_basic_sphere.rt
```

### Controls

| Key | Action |
|-----|--------|
| `ESC` | Exit the program |
| Window close button | Exit the program |

---

## Scene File Format

Scene files use the `.rt` extension and contain element definitions:

### Required Elements (exactly one each)

| Element | Format | Description |
|---------|--------|-------------|
| Ambient | `A <ratio> <R,G,B>` | Ambient lighting (ratio: 0.0-1.0) |
| Camera | `C <x,y,z> <dx,dy,dz> <fov>` | Camera position, direction, FOV (0-180) |
| Light | `L <x,y,z> <brightness> <R,G,B>` | Point light (brightness: 0.0-1.0) |

### Objects (any number)

| Object | Format | Description |
|--------|--------|-------------|
| Sphere | `sp <x,y,z> <diameter> <R,G,B>` | Sphere at position with diameter |
| Plane | `pl <x,y,z> <nx,ny,nz> <R,G,B>` | Infinite plane with normal vector |
| Cylinder | `cy <x,y,z> <ax,ay,az> <diameter> <height> <R,G,B>` | Cylinder with axis direction |

### Example Scene

```
A 0.2 255,255,255
C 0,0,20 0,0,-1 70
L -10,10,15 0.7 255,255,255

sp 0,0,0 10 255,0,0
pl 0,-5,0 0,1,0 0,255,0
cy 5,0,-5 0,1,0 3 10 0,0,255
```

---

## Project Structure

```
miniRT/
├── include/                    # Header files
│   ├── minirt.h                # Main definitions and structs
│   ├── parser.h                # Parser function prototypes
│   ├── render.h                # Rendering structures and functions
│   ├── vec3.h                  # Vector mathematics
│   └── project.h               # Project-wide type definitions
├── src/                        # Source files
│   ├── main.c                  # Entry point and event hooks
│   ├── error.c                 # Error handling and cleanup
│   ├── mlx_utils.c             # MiniLibX initialization
│   ├── parser/                 # Scene file parsing
│   │   ├── parser.c            # File reading and validation
│   │   ├── parser_elements.c   # Line tokenization and dispatch
│   │   ├── parser_scene.c      # Ambient, camera, light parsing
│   │   ├── parser_light.c      # Light element parsing
│   │   ├── parser_objects.c    # Sphere parsing
│   │   ├── parser_plane.c      # Plane parsing
│   │   ├── parser_cylinder.c   # Cylinder parsing
│   │   ├── parser_utils.c      # ft_atof and utility helpers
│   │   ├── parser_validate.c   # Input format validation
│   │   ├── parser_validate2.c  # Safe parsing (vector, color)
│   │   ├── parser_validate3.c  # Value and token validators
│   │   ├── parser_validate4.c  # Duplicate and count checks
│   │   └── get_next_line.c     # File line reader
│   ├── render/                 # Rendering pipeline
│   │   ├── render.c            # Main rendering loop
│   │   ├── camera.c            # Camera ray generation
│   │   ├── ray.c               # Ray constructor and utilities
│   │   ├── intersect.c         # Closest hit detection
│   │   └── lighting.c          # Ambient/diffuse lighting and shadows
│   ├── geometry/               # Ray-object intersections
│   │   ├── hit_sphere.c        # Ray-sphere intersection
│   │   ├── hit_plane.c         # Ray-plane intersection
│   │   ├── hit_cylinder.c      # Ray-cylinder intersection
│   │   └── cylinder_utils.c    # Cylinder math helpers
│   └── math/                   # Vector and color math
│       ├── vec3_create.c       # Vector constructors
│       ├── vec3_operations.c   # Vector arithmetic (+, -, *, /)
│       ├── vec3_properties.c   # Length, dot, cross, normalize
│       └── color.c             # Color operations
├── eval_scenes/                # Evaluation scene files (.rt)
├── libft/                      # Custom C library
├── minilibx-linux/             # Graphics library (X11)
├── Makefile
└── README.md
```

---

### Evaluation Scenes

The `eval_scenes/` directory contains test files mapped to each evaluation sheet section:

| Eval Section | File | Description |
|---|---|---|
| **Basic Shapes** | `01_basic_sphere.rt` | Sphere at {0,0,0}, camera facing it |
| | `02_basic_plane.rt` | Plane with normal facing camera |
| | `03_basic_cylinder.rt` | Cylinder along y axis, camera facing it |
| **Translation** | `04_trans_spheres.rt` | Two spheres, one translated along camera direction |
| **Rotation** | `05_rot_cylinder.rt` | Cylinder rotated 90° around z axis (y → x axis) |
| **Multi-objects** | `06_multi_intersect.rt` | Intersecting sphere and cylinder at origin |
| | `07_multi_same.rt` | Multiple objects of same type (2 spheres, 2 cylinders, 1 plane) |
| **Camera position** | `08_cam_x.rt` | Camera along x axis pointing to origin |
| | `09_cam_y.rt` | Camera along y axis pointing to origin |
| | `10_cam_z.rt` | Camera along z axis pointing to origin |
| | `11_cam_rand.rt` | Camera at random off-axis position |
| **Brightness 1/2** | `12_light_side.rt` | Sphere at origin, light from the side |
| | `13_light_trans.rt` | Translated sphere, light from the side |
| **Brightness 2/2** | `14_shadow_basic.rt` | Sphere shadow cast on plane |
| | `15_shadow_complex.rt` | Complex scene with multiple objects and shadows |
| **Extra** | `16_shadow_overlap.rt` | Multiple overlapping object shadows |
| | `17_multi_shadow_overlap.rt` | Sphere enclosing other objects |
| **Bonus** | `eclipse.rt` | Solar eclipse simulation with shadow casting |

---

## Resources

### Documentation & References

- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) - Peter Shirley's excellent introduction to ray tracing
- [Lineer Algebra](https://youtube.com/playlist?list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab&si=tVKeAuZbzJjFQBcX) - Essence of linear algebra 3Blue1Brown

### AI Usage

AI assistance was used in this project for:

- **Bug detection:** Finding logical issues such as missing NULL checks, resource leaks, and formula inconsistencies
- **Error handling:** Generating comprehensive error test cases and validation logic
- **Documentation:** Creating this README and inline comments
- **Scene files:** Generating test scene configurations for evaluation criteria

All AI-generated code was reviewed, tested, and modified as needed to ensure correctness and compliance with project requirements.

---

## License

This project is part of the 42 school curriculum. All rights reserved.
