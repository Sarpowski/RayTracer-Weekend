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

#include "headers/rytUtility.h"


#include <iostream>
#include <fstream>
#include "headers/hittable.h"
#include "headers/hittableList.h"
#include "headers/sphere.h"
#include "headers/camera.h"



using namespace ryt;

int main() {
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    //World
    hittableList world;
    world.add(std::make_shared<sphere>(point3(0,0,-1),0.5));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1),100));


    //Camera
    camera cam(image_width, aspect_ratio);
    cam.image_width = 400;
    cam.aspect_ratio = 16.0 /9.0;
    cam.samplesPerPixel = 100;
    cam.render(world);



    std::clog << "\rDone.                 \n";

}