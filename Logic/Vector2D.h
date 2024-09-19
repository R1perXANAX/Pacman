
#ifndef PACMANFINAL_VECTOR2D_H
#define PACMANFINAL_VECTOR2D_H
#include <cmath>
#include <cstdint>

#define PI 3.14159265358979323846
#define DEG2RAD(angle) ((angle) * PI / 180.0f)
#define RAD2DEG(angle) ((angle) * 180.0f / PI)

template <class Num_T>
class Vector2 {
public:
    Vector2();
    Vector2(Num_T x, Num_T y);
    Vector2(const Vector2& other);
    Vector2(Num_T value);

    ~Vector2() {
    }

public:
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator*(Num_T value) const;
    float operator*(const Vector2& other) const;

    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    Vector2& operator*=(Num_T value);

    bool operator==(const Vector2& other) const;
    bool operator!=(const Vector2& other) const;

    operator Vector2<int32_t>() const;
    operator Vector2<uint32_t>() const;
    operator Vector2<float>() const;

public:
    float DistanceTo(const Vector2& other) const;
    float DistanceTo(Num_T x, Num_T y) const;

public:
    Num_T x;
    Num_T y;
};

template <class Num_T>
Vector2<Num_T>::Vector2() {
    x = static_cast<Num_T>(0);
    y = static_cast<Num_T>(0);
}

template <class Num_T>
Vector2<Num_T>::Vector2(Num_T x, Num_T y) {
    this->x = x;
    this->y = y;
}

template <class Num_T>
Vector2<Num_T>::Vector2(const Vector2& other) {
    x = static_cast<Num_T>(other.x);
    y = static_cast<Num_T>(other.y);
}

template <class Num_T>
Vector2<Num_T>::Vector2(Num_T value) {
    x = value;
    y = value;
}

template <class Num_T>
Vector2<Num_T> Vector2<Num_T>::operator+(const Vector2& other) const {
    return {x + other.x, y + other.y};
}

template <class Num_T>
Vector2<Num_T> Vector2<Num_T>::operator-(const Vector2& other) const {
    return {x - other.x, y - other.y};
}

template <class Num_T>
Vector2<Num_T> Vector2<Num_T>::operator*(Num_T value) const {
    return {x * value, y * value};
}

template <class Num_T>
float Vector2<Num_T>::operator*(const Vector2& other) const {
    return x * other.x + y * other.y;
}

template <class Num_T>
Vector2<Num_T>& Vector2<Num_T>::operator+=(const Vector2& other) {
    return *this = *this + other;
}

template <class Num_T>
Vector2<Num_T>& Vector2<Num_T>::operator-=(const Vector2& other) {
    return *this = *this - other;
}

template <class Num_T>
Vector2<Num_T>& Vector2<Num_T>::operator*=(Num_T value) {
    return *this = *this * value;
}

template <class Num_T>
bool Vector2<Num_T>::operator==(const Vector2<Num_T>& other) const {
    return x == other.x && y == other.y;
}

template <class Num_T>
bool Vector2<Num_T>::operator!=(const Vector2<Num_T>& other) const {
    return !(*this == other);
}

template <class Num_T>
Vector2<Num_T>::operator Vector2<int32_t>() const {
    return {static_cast<int32_t>(this->x), static_cast<int32_t>(this->y)};
}

template <class Num_T>
Vector2<Num_T>::operator Vector2<uint32_t>() const {
    return {static_cast<uint32_t>(this->x), static_cast<uint32_t>(this->y)};
}

template <class Num_T>
Vector2<Num_T>::operator Vector2<float>() const {
    return {static_cast<float>(this->x), static_cast<float>(this->y)};
}


template <class Num_T>
float Vector2<Num_T>::DistanceTo(const Vector2& other) const {
    return DistanceTo(other.x, other.y);
}

template <class Num_T>
float Vector2<Num_T>::DistanceTo(Num_T x, Num_T y) const {
    return sqrtf(powf(this->x - x, 2.0f) + powf(this->y - y, 2.0f));
}


typedef Vector2<int32_t> Vector2i;
typedef Vector2<uint32_t> Vector2u;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
#endif //PACMANFINAL_VECTOR2D_H
