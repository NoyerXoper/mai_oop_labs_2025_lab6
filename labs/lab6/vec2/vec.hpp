#pragma once

#include <ostream>
#include <type_traits>

namespace vec {
namespace {
template <class T>
concept Scalar = std::is_arithmetic_v<T>;
}

template <Scalar T>
struct Vec {
    T x;
    T y;

    Vec(T x, T y);

    Vec& operator+=(const Vec& other) noexcept;
    Vec& operator-=(const Vec& other) noexcept;

    Vec operator+(const Vec& other) const noexcept;
    Vec operator-(const Vec& other) const noexcept;

    double DistanceToOther(const Vec& other) const noexcept;
};
template <Scalar T>
std::ostream& operator<<(std::ostream& out, const Vec<T>& vec);
template <Scalar T>
bool operator==(const Vec<T>& first, const Vec<T>& second) noexcept;
}  // namespace vec

#include "vec.ipp"
