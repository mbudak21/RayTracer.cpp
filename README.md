# RayTracer.cpp

This project is a C++ raytracer built with zero external dependencies. Every component, from vector linear algebra to geometric intersection algorithms, was implemented manually rather than using libraries. The engine supports global illumination features including recursive reflections, refractions (Snell's Law), and shadows. The pipeline uses multi-threading for performance and includes a custom material system with both Phong and Gouraud shading models.

## Usage

```
mkdir build && \
cd build && \
make && \
./RayTraceRunner && \
open DVA338_Raytracer_output.bmp
```

## Licenses Used

### GPL-3.0

[libbmp](https://github.com/marc-q/libbmp/tree/66bec6d7daf254e6dc07d55c9383fd68276a6a39) - used without modifications for exporting image to BMP format.
