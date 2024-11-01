//
// Created by Can on 11/1/2024.
//

#ifndef SPHERE_H
#define SPHERE_H


#include "hittable.h"
#include "vec3.h"

namespace ryt{


using namespace ryt;

class sphere : public hittable {
    public:
        sphere(const point3& center , double radius)
                :
                center_(center),
                radius_(radius)
        {}
        virtual bool hit(const ray& r , interval ray_t, hitRecord& rec) const override{
            vec3 oc = center_ - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius_* radius_;

            auto discriminant = h*h - a*c;
            if (discriminant < 0)
                return false;

            auto sqrtd = std::sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range.
            auto root = (h - sqrtd) / a;
            if (!ray_t.surounds(root)) {
                root = (h + sqrtd) / a;
                if (!ray_t.surounds(root))
                    return false;
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center_) / radius_;
            rec.set_face_normal(r, outward_normal);

            //rec.normal = (rec.p - center_) / radius_;

            return true;
        }
    private:
        point3  center_;
        double  radius_;
    };


}


#endif //RAYTRACER_SPHERE_H
