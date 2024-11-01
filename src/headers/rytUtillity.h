//
// Created by Can on 11/2/2024.
//

#ifndef RYTUTILLITY_H
#define RYTUTILLITY_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

//constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

//Utility functions
inline double degreeToRadiant(double degrees){
    return (pi * degrees) / 180;
}

// Common Headers
#include "color.h"
#include "ray.h"
#include "vec3.h"


#endif //RAYTRACER_RYTUTILLITY_H
