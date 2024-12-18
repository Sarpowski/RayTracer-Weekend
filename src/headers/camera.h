#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include "hittable.h"
#include "color.h"

using namespace ryt;

class camera {
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samplesPerPixel = 10;
    camera(int width, double aspect)
    : image_width(width), aspect_ratio(aspect) {}

    void render(const hittable& world) {
        initialize();
        std::ofstream outputFile("testVec.ppm");
        outputFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; j++) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; i++) {
                color pixelColor(0,0,0);
                for (int sample = 0; sample < samplesPerPixel; sample++){
                    ray r = getRay(i,j);
                    pixelColor += rayColor(r, world);
                }

                writeColor(outputFile, pixelColor * pixelSamplesScale);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    int image_height;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    double pixelSamplesScale;
    void initialize() {
        image_height = int(image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;
        pixelSamplesScale = 1.0 / samplesPerPixel;

        center = point3(0, 0, 0);
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * aspect_ratio;

        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
    ray getRay(int i, int j){
        auto offset = sampleSquare();
        auto pixel_sample = pixel00_loc
                            + ((i + offset.x()) * pixel_delta_u)
                            + ((j + offset.y()) * pixel_delta_v);
        auto rayOrigin = center;
        auto rayDirection = pixel_sample - rayOrigin;
        return ray(rayOrigin, rayDirection);


    }
    color rayColor(const ray& r , const hittable& world) {
        hitRecord rec;
        if(world.hit(r, interval(0,infinity), rec)){
            vec3 direction = randomOnHemisphere(rec.normal);
            return 0.5 * rayColor(ray(rec.p,direction),world);
        }

        vec3 unit_direction = unitVector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
    vec3 sampleSquare(){
        return vec3(random_double() - 0.5, random_double()- .5,0);
    }
};

#endif //CAMERA_H
