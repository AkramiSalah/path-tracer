#pragma once
#include "ray.h"

template<typename T>
class camera
{
public:
    using Point3 = point3<T>;
    using Vec3   = vec3<T>;
    using Ray    = ray<T>;

    static constexpr T ZERO = T();
    static constexpr T DEFAULT_ASCPECT_RATIO = T(16)/T(9);
    static constexpr int DEFAULT_IMAGE_WIDTH = 400;
    static constexpr Point3 DEFAULT_CENTER = Point3(ZERO, ZERO, ZERO);


    camera(T aspect_ratio, int image_width, const Point3& center) :
        aspect_ratio(aspect_ratio), center(center){
        int image_height = int (image_width / aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        T focal_length = T(1.0);
        T viewport_height = T(2.0);
        T viewport_width = viewport_height * (T(image_width) / T(image_height));

        auto viewport_u = Vec3(viewport_width, ZERO, ZERO);
        auto viewport_v = Vec3(ZERO, -viewport_height, ZERO);
        
        auto viewport_upper_left = this->center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        
        auto pixel_delta_u = viewport_u / image_width;
        auto pixel_delta_v = viewport_v / image_height;
        
        // we want the location to be at the center of the pixel.
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    camera() : camera(DEFAULT_ASCPECT_RATIO, DEFAULT_IMAGE_WIDTH, DEFAULT_CENTER){}

private:
    T aspect_ratio;
    Point3 center;
    Vec3 pixel_delta_u;
    Vec3 pixel_delta_v;
    Point3 pixel00_loc;
};

