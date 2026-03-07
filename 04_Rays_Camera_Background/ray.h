#pragma once
#include "../03_vector/vec3.h"

template<typename T>
class ray{
public:
    using Point3 = point3<T>;
    using Vec3   = vec3<T>;

    ray() = default;
    ray(const Point3& origin, const Vec3& direction) : orig(origin), dir(direction){}
    
    ~ray() = default;
    ray& operator=(const ray& other) = default;

    const Point3& origin() const{
        return orig;
    }

    const Vec3& direction() const{
        return dir;
    }

    Point3 at(T t) const {
        return orig + t*dir;
    }

private:
    Point3 orig;
    Vec3 dir;
};
