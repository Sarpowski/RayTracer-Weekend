cmake_minimum_required(VERSION 3.28)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(RayTracer src/main.cpp
        src/headers/vec3.h
        src/headers/ray.h
        src/headers/color.h
        src/headers/hittable.h
        src/headers/sphere.h
        src/headers/hittableList.h
        src/headers/rytUtillity.h
        src/headers/interval.h)
