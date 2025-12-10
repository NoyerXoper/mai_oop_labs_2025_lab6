#include <cmath>

#include "vec.hpp"

namespace vec {
template <Scalar T>
Vec<T>::Vec(T x, T y)
    : x(x)
    , y(y) {}

template <Scalar T>
Vec<T>& Vec<T>::operator+=(const Vec<T>& other) noexcept {
    x += other.x;
    y += other.y;
    return *this;
}

template <Scalar T>
Vec<T>& Vec<T>::operator-=(const Vec<T>& other) noexcept {
    x -= other.x;
    y -= other.y;
    return *this;
}

template <Scalar T>
Vec<T> Vec<T>::operator+(const Vec<T>& other) const noexcept {
    Vec<T> temp = *this;
    return temp += other;
}

template <Scalar T>
Vec<T> Vec<T>::operator-(const Vec<T>& other) const noexcept {
    Vec<T> temp = *this;
    return temp -= other;
}

template <Scalar T>
double Vec<T>::DistanceToOther(const Vec<T>& other) const noexcept {
    T dx = x - other.x;
    T dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

template <Scalar T>
bool operator==(const Vec<T>& first, const Vec<T>& second) noexcept {
    return first.x == second.x && first.y == second.y;
}

template <Scalar T>
std::ostream& operator<<(std::ostream& out, const Vec<T>& vec) {
    out << '(' << vec.x << "; " << vec.y << ')';
    return out;
}
}  // namespace vec