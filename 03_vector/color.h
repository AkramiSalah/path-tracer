#pragma once

#include "vec3.h"
#include <iostream>
#include <algorithm>



template<typename T>
static constexpr T SCALE_FACTOR = static_cast<T>(255.999);

template<typename T>
using color = vec3<T>;

template<typename T>
void write_color(std::ostream& out, const color<T>& pixel_color){
    auto r = std::clamp(pixel_color.x(), vec3<T>::ZERO, vec3<T>::ONE);
    auto g = std::clamp(pixel_color.y(), vec3<T>::ZERO, vec3<T>::ONE);
    auto b = std::clamp(pixel_color.z(), vec3<T>::ZERO, vec3<T>::ONE);

    int rbyte = static_cast<int>(SCALE_FACTOR<T> * r);
    int gbyte = static_cast<int>(SCALE_FACTOR<T> * g);
    int bbyte = static_cast<int>(SCALE_FACTOR<T> * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
