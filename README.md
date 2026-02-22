*This project has been created as part of the 42 curriculum by aerenler and ualkan.*

# miniRT

A minimal ray tracing engine written in C, capable of rendering 3D scenes with spheres, planes, and cylinders using the Phong reflection model.

![Ray Tracing Example](https://upload.wikimedia.org/wikipedia/commons/thumb/8/83/Ray_trace_diagram.svg/300px-Ray_trace_diagram.svg.png)

---

## Description

**miniRT** is a lightweight ray tracer that renders 3D scenes defined in `.rt` configuration files. The project demonstrates fundamental concepts of computer graphics including:

- **Ray-object intersection** algorithms for spheres, planes, and cylinders
- **Phong lighting model** with ambient, diffuse lighting components
- **Shadow casting** for realistic scene rendering
- **Camera positioning** with configurable field of view

The renderer supports multiple objects in a scene, handles object intersections correctly, and produces images with proper lighting and shadows.

### Features

- ✅ Sphere, plane, and cylinder primitives
- ✅ Ambient and point light sources
- ✅ Configurable camera position, orientation, and FOV
- ✅ Shadow rendering
- ✅ Phong diffuse lighting
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
./miniRT scenes/<scene_file>.rt
```

Example:
```bash
./miniRT scenes/eval_sphere.rt
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
├── include/          # Header files
│   ├── minirt.h      # Main definitions and structs
│   ├── parser.h      # Parser function prototypes
│   ├── render.h      # Rendering structures and functions
│   ├── vec3.h        # Vector mathematics
│   └── project.h     # Project-wide type definitions
├── src/                    # Source files
│   ├── main.c              # Entry point and event hooks
│   ├── error.c             # Error handling and cleanup
│   ├── mlx_utils.c         # MiniLibX initialization
│   ├── parser.c            # Scene file reading and validation
│   ├── parser_elements.c   # Line tokenization and dispatch
│   ├── parser_scene.c      # Ambient, camera, light parsing
│   ├── parser_objects.c    # Sphere and cylinder parsing
│   ├── parser_plane.c      # Plane parsing
│   ├── parser_utils.c      # Vector and color parsing
│   ├── parser_utils2.c     # ft_atof and utility helpers
│   ├── get_next_line.c     # File line reader
│   ├── render.c            # Main rendering loop
│   ├── camera.c            # Camera ray generation
│   ├── ray.c               # Ray constructor and utilities
│   ├── intersect.c         # Closest hit detection
│   ├── hit_sphere.c        # Ray-sphere intersection
│   ├── hit_plane.c         # Ray-plane intersection
│   ├── hit_cylinder.c      # Ray-cylinder intersection
│   ├── cylinder_utils.c    # Cylinder math helpers
│   ├── lighting.c          # Phong lighting and shadows
│   ├── color.c             # Color operations
│   ├── vec3_create.c       # Vector constructors
│   ├── vec3_operations.c   # Vector arithmetic (+, -, *, /)
│   └── vec3_properties.c   # Vector length, dot, cross, normalize
├── scenes/           # Example scene files
├── libft/            # Custom C library
├── minilibx-linux/   # Graphics library
├── Makefile
└── README.md
```

---

## Testing

### Error Handling Tests

Run the error handling test suite:
```bash
./test_errors.sh
```

This tests 32 different error scenarios including:
- Invalid file extensions
- Missing required elements
- Duplicate elements
- Invalid value ranges
- Malformed input

### Evaluation Scenes

The `scenes/` directory contains test files for each evaluation criterion:

| File | Test |
|------|------|
| `eval_sphere.rt` | Basic sphere rendering |
| `eval_plane.rt` | Basic plane rendering |
| `eval_cylinder.rt` | Basic cylinder rendering |
| `eval_translation.rt` | Object translation |
| `eval_rotation.rt` | Cylinder rotation |
| `eval_multi_*.rt` | Multiple objects |
| `eval_cam_*.rt` | Camera positioning |
| `eval_brightness*.rt` | Lighting tests |
| `eval_shadow*.rt` | Shadow rendering |

---

## Resources

### Documentation & References

- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) - Peter Shirley's excellent introduction to ray tracing
- [Scratchapixel](https://www.scratchapixel.com/) - Comprehensive computer graphics tutorials
- [Ray-Sphere Intersection](https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection) - Mathematical foundation
- [Phong Reflection Model](https://en.wikipedia.org/wiki/Phong_reflection_model) - Lighting model explanation
- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Graphics library reference

### AI Usage

AI assistance (GitHub Copilot with Claude) was used in this project for:

- **Code refactoring:** Splitting large functions to comply with 42 norm (25 lines max, 5 functions per file)
- **Error handling:** Generating comprehensive error test cases and validation logic
- **Documentation:** Creating this README and inline comments
- **Debugging:** Identifying duplicate functions and unused code
- **Scene files:** Generating test scene configurations for evaluation criteria

All AI-generated code was reviewed, tested, and modified as needed to ensure correctness and compliance with project requirements.

---

## License

This project is part of the 42 school curriculum. All rights reserved.
