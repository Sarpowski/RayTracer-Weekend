#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "interval.h"
#include <iostream>

namespace ryt{
    using namespace ryt;
    using color = vec3;

    void writeColor(std::ostream& out, const color& pixel_color) {
        auto r = pixel_color.x();
        auto g = pixel_color.y();
        auto b = pixel_color.z();
        static const interval intensity (0.000,0.999);
        // Translate the [0,1] component values to the byte range [0,255].
        int rbyte = int(255.999 * intensity.clamp(r));
        int gbyte = int(255.999 * intensity.clamp(g));
        int bbyte = int(255.999 * intensity.clamp(b));

        // Write out the pixel color components.
        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
    }

}

#endif