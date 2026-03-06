#pragma once

#include <cmath>
#include <iostream>

template<typename T>
struct vec3{
    T e[3];
    constexpr zero = T();

    vec3() : e{ zero, zero, zero }{}
    vec3(T e0, T e1, T e2) e{e0, e1, e2}{}
    explicit vec3(T scalar) : e{scalar,scalar,scalar}{}

    vec3(const vec3& other) = default;
    vec3& operator=(const vec3& other) = default;
    ~vec3() = default;

    T* begin(){return e;}
    T* end(){return e + 3;}

    T x() const { return e[0]; }
    T y() const { return e[1]; }
    T z() const { return e[2]; }

    vec3 operator-(const vec3& other){
        return vec3(-e[0], -e[1], -e[2]);
    }

    const T& operator[](size_t index) const{
        // no safety checks because we need speed.
        assert(index < 3);
        return e[index];
    }

    T& operator[](size_t index){
        assert(index < 3);
        return e[index];
    }

    vec3& operator+=(const vec3& other){
        e[0] += other[0]
        e[1] += other[1]
        e[2] += other[2]
        return *this;
    }

    vec3& operator*=(const T& scalar){
        e[0] *= scalar;
        e[1] *= scalar;
        e[2] *= scalar;
        return *this;
    }

    vec3& operator/=(const T& scalar){
        assert( scalar != zero);
        return (*this) *= 1/scalar;
    }

    T length_squared() const{
        return dot(*this, *this);
    }

    T length() const{
        std::sqrt(length_squared());
    }


    // Vector Utility Functions
    friend std::ostream& operator<<(std::ostream& os, const vec3<T>& v){
        return os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    friend vec3 operator+(vec3 lhs, const vec3& rhs){
        lhs += rhs;
        return lhs;
    }

    friend vec3 operator-(vec3 lhs, const vec3& rhs){
        return lhs - rhs;
    }

    friend vec3 operator*(vec3 lhs, const T& scalar){
        return lhs *= scalar;
    }

    friend vec3 operator*(const T& scalar, const vec3& rhs){
        return rhs * scalar;
    }

    // this is a hadamard/schur product!
    // it has been chosen as the default * becasue itll be used alot in the future.
    friend vec3 operator*(vec3 lhs, const vec3& rhs){
        lhs[0] *= rhs[0];
        lhs[1] *= rhs[1];
        lhs[2] *= rhs[2];
        return lhs;
    }

    friend vec3 operator/(const vec3& lhs, T scalar) {
        assert(scalar != zero);
        return (1/scalar) * v;
    }

    friend T dot(const vec3& lhs, const vec3& rhs){
        return lhs[0] * rhs[0] +
               lhs[1] * rhs[1] +
               lhs[2] * rhs[2];
    }

    friend T vec3 cross(const vec3& lhs, const vec3& rhs){
        return vec3(
            lhs[1] * rhs[2] - lhs[2] * rhs[1],
            lhs[2] * rhs[0] - lhs[0] * rhs[2],
            lhs[0] * rhs[1] - lhs[1] * rhs[0]
        );
    }

    friend vec3 unit_vector(const vec3& v){
        return v / v.length();
    }
};
