//
// Created by Can on 11/2/2024.
//

#ifndef RAYTRACER_HITTABLELIST_H
#define RAYTRACER_HITTABLELIST_H

#include "hittable.h"


#include <memory>
#include <vector>

namespace ryt{



    class hittableList : public hittable{
    public:
        std::vector<std::shared_ptr<hittable>> objects;
        hittableList() {}
        hittableList(std::shared_ptr<hittable> object){add(object);}

        void clear() { objects.clear(); }
        void add(std::shared_ptr<hittable> object){
            objects.push_back(object);
        }
        bool hit(const ray& r, interval ray_t, hitRecord& rec) const override{
            hitRecord tempRec;
            bool hitAnything = false;
            auto closestSoFar = ray_t.max_;

            for(const auto& object : objects){
                if(object->hit(r,interval(ray_t.min_, closestSoFar), tempRec)){
                    hitAnything = true;
                    closestSoFar = tempRec.t;
                    rec = tempRec;
                }
            }
            return  hitAnything;
        }

    };


}







#endif //RAYTRACER_HITTABLELIST_H
