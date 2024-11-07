//
// Created by Can on 11/2/2024.
//

#ifndef INTERVAL_H
#define INTERVAL_H

#include "rytUtility.h"

namespace ryt{

    class interval{
    public:
        double min_;
        double max_;
        interval() : min_(+infinity), max_(-infinity) {} // Default interval is empty
        interval(double min, double max)
        :
            min_(min),
            max_(max)
            {}

        double size() const {
            return max_ - min_;
        }
        bool contains(double x){
            return min_ <= x && x <= max_;
        }

        bool surounds(double x )const{
            return min_ < x && x < max_;
        }
        double clamp(double x) const{
            if (x < min_) return min_;
            if (x > max_) return max_;
            return x;

        }
        static const interval empty;
        static const interval universe;
    };
    const interval interval::empty = interval(+infinity, -infinity);
    const interval interval::universe = interval(-infinity, +infinity);
}


#endif //RAYTRACER_INTERVAL_H
