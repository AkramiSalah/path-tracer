#pragma once

#include <cmath>
#include <iostream>
#include <cassert>

template<typename T>
struct vec3{
    static constexpr T ZERO = T();
    static constexpr T ONE = static_cast<T>(1);
    static constexpr size_t VECTOR_SIZE = 3;

    T e[VECTOR_SIZE];

    vec3() : e{ ZERO, ZERO, ZERO }{}
    vec3(T e0, T e1, T e2) : e{e0, e1, e2}{}
    explicit vec3(T scalar) : e{scalar,scalar,scalar}{}

    vec3(const vec3& other) = default;
    vec3& operator=(const vec3& other) = default;
    ~vec3() = default;

    T* begin(){return e;}
    T* end(){return e + VECTOR_SIZE;}

    T x() const { return e[0]; }
    T y() const { return e[1]; }
    T z() const { return e[2]; }

    vec3 operator-() const{
        return vec3(-e[0], -e[1], -e[2]);
    }

    const T& operator[](size_t index) const{
        assert(index < VECTOR_SIZE);
        return e[index];
    }

    T& operator[](size_t index){
        assert(index < VECTOR_SIZE);
        return e[index];
    }

    vec3& operator+=(const vec3& other){
        for (int i = 0; i < VECTOR_SIZE; ++i) e[i] += other.e[i];
        return *this;
    }

    vec3& operator-=(const vec3& other){
        for (int i = 0; i < VECTOR_SIZE; ++i) e[i] -= other.e[i];
        return *this;
    }

    vec3& operator*=(const T& scalar){
        for (int i = 0; i < VECTOR_SIZE; ++i) e[i] *= scalar;
        return *this;
    }

    vec3& operator/=(const T& scalar){
        assert( scalar != ZERO);
        return (*this) *= ONE/scalar;
    }

    T length_squared() const{
        return dot(*this, *this);
    }

    T length() const{
        return std::sqrt(length_squared());
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
        return lhs + (-rhs);
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
        for (int i = 0; i < VECTOR_SIZE; ++i) lhs[i] *= rhs[i];
        return lhs;
    }

    friend vec3 operator/(const vec3& v, T scalar) {
        return v /= scalar;
    }

    friend T dot(const vec3& lhs, const vec3& rhs){
        T res = ZERO;
        for (int i = 0; i < VECTOR_SIZE; ++i) res += lhs[i] * rhs[i];
        return res;
    }

    friend vec3 cross(const vec3& lhs, const vec3& rhs){
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
