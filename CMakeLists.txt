set(CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 3.10)
project(DVA338_RayTracer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external_dependencies/libbmp
)

# === Libraries ===

# External library (libbmp)
add_library(libbmp
    external_dependencies/libbmp/libbmp.cpp
)

# Core logic (geometry, materials, rays, etc.)
add_library(Core
    src/Image.cpp
    src/Light.cpp
    src/Material.cpp
    src/Object.cpp
    src/Ray.cpp

    src/Scene.cpp
    src/Sphere.cpp
    src/Triangle.cpp
    src/Plane.cpp
)

target_link_libraries(Core libbmp)

# RayTracer logic (maybe main rendering loop or integrator)
add_library(RayTracer
    src/RayTracer.cpp
)

target_link_libraries(RayTracer Core)

# === Executable ===
add_executable(RayTraceRunner
    src/Main.cpp
)

target_link_libraries(RayTraceRunner RayTracer)

# === Optional custom target ===
add_custom_target(run
    COMMAND RayTraceRunner
    DEPENDS RayTraceRunner
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
