# Vennimate

Screensaver-inspired animation that cycles through all 173 distinct arrangements of 4 circles in the
affine plane. For example, here are some of the arrangements:

<p align="center">
<img src="/assets/diagrams/example_arrangements.svg"/>
</p>

We cycle through arrangements in a random order, smoothly transitioning from each to the next.

## Background

There are 173 distinct ways of arranging 4 circles on a plane. Two circle arrangements are considered
distinct if one cannot be continuously deformed into the other, while:

 - keeping circles circular (changing radii is allowed),
 - preserving multiplicity of intersection points,
 - not allowing any circle to cross an intersection point, and
 - optionally reflecting about a line.

For more information about the problem, see sequence [A250001](https://oeis.org/A250001) in the OEIS.

## Compilation

Rendering uses OpenGL and GLUT. On Ubuntu, these can be installed with 

```bash
sudo apt-get install freeglut3-dev
```

The build process is orchestrated by GNU Make. You can run 

```bash
make all
```

to build, and 

```bash
make clean
```

to remove compilation artifacts & binaries.

## Controlling animation

The following keybindings are used to control the animation at runtime:

- `Right`: speed up transitions
- `Left`: slow down transitions
- `Up`: make transitions sharper
- `Down`: make transitions smoother
- `Space`: show/hide transition interpolation curve
- `o`: show/hide circle fill
- any other keypress exits the program

Many of the default settings (including foreground & background colors) can also be tweaked at
_compilation time_ by changing the constants defined near the top of `circles.c`.
