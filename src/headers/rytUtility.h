//
// Created by Can on 11/2/2024.
//

#ifndef RYTUTILLITY_H
#define RYTUTILLITY_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility functions
inline double degreeToRadiant(double degrees){
    return (pi * degrees) / 180;
}
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline double random_double(double min, double max){
    return min + (max-min)*random_double();

}



// Common Headers
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif //RAYTRACER_RYTUTILLITY_H
