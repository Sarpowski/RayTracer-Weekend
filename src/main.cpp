//#include <iostream>
//#include <fstream>
//#include "headers/vec3.h"
//#include "headers/ray.h"
//
//bool hitSphere(const vec3& center, float radius, const ray& r){
//    vec3 oc = r.origin() - center;
//    float a = dot(r.direction(),r.direction());
//    float b = 2.0 * dot(oc, r.direction());
//    float c = dot(oc,oc)- radius * radius;
//    float discriminant = b*b - 4*a*c;
//    if (discriminant > 0){
//        return -1.0;
//    }
//    else{
//        return(-b - sqrt(discriminant)) /(2.0*a);
//    }
//}
//vec3 color(const Ray& r){
//    float t = hitSphere(vec3(0,0,-1), 0.5,r);
//    if(t > 0.0){
//        vec3 N = unit_vector(r.ponintAtParameter(t) - vec3(0,0,-1));
//        return 0.5*vec3(N.x()+1 , N.y()+1,N.z()+1);
//    }
//    vec3 unit_direction = unit_vector(r.direction());
//    t = 0.5*(unit_direction.y() + 1.0);
//    return (1.0-t) * vec3(1.0,1.0,1.0) + t * vec3(0.5,0.7,1.0);
//}
//
//int main()
//{
//    std::ofstream outputFile;
//    outputFile.open("testVec.ppm");
//    int nx = 200;
//    int ny = 100;
//    outputFile << "P3\n" << nx << " " << ny << "\n255\n";
//    vec3 lowerLeftCorner(-2.0,-1.0,-1.0);
//    vec3 horizontal(4.0,0.0,0.0);
//    vec3 vertical(0.0,2.0,0.0);
//    vec3 origin(0.0,0.0,0.0);
//    for (int i = ny - 1; i>= 0 ; i--) {
//        for (int j = 0; j < nx; j++) {
//            float u = static_cast<float>(i)/static_cast<float>(nx);
//            float v = static_cast<float>(j)/static_cast<float>(ny);
//            Ray r(origin,lowerLeftCorner + u*horizontal + v*vertical);
//            vec3 col = color(r);
//            int ir = static_cast<int>(255.99*col[0]);
//            int ig = static_cast<int>(255.99*col[1]);
//            int ib = static_cast<int>(255.99*col[2]);
//            outputFile << ir << " " << ig << " " << ib << "\n";
//        }
//
//
//    }
//    outputFile.close();
//    return 0;
//}

#include "headers/rytUtillity.h"


#include <iostream>
#include <fstream>
#include "headers/hittable.h"
#include "headers/hittableList.h"
#include "headers/sphere.h"



using namespace ryt;


color ray_color(const ray& r , const hittable& world) {
    hitRecord rec;
    if(world.hit(r,0,infinity, rec)){
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {





    // Image
    std::ofstream outputFile;
    outputFile.open("testVec.ppm");
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    //world
    hittableList world;
    world.add(std::make_shared<sphere>(point3(0,0,-1),0.5));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1),100));


    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                               - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Render
    outputFile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r, world);
            write_color(outputFile, pixel_color);
        }
    }



    std::clog << "\rDone.                 \n";

}