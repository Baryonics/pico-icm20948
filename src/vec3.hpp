#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>

namespace icm20948
{

    template <typename T>
        requires(std::integral<T> || std::floating_point<T>)
    struct Vec3
    {
        Vec3() = default;
        Vec3(T x, T y, T z)
            : x(x)
            , y(y)
            , z(z)
        {
        }

        template <typename U>
            requires(std::integral<U> || std::floating_point<U>)
        Vec3(const Vec3<U>& other)
            : x(static_cast<T>(other.x))
            , y(static_cast<T>(other.y))
            , z(static_cast<T>(other.z))
        {
        }

        Vec3<float> operator/(float const f) const
        {
            return Vec3<float>{ static_cast<float>(x) / f, static_cast<float>(y) / f, static_cast<float>(z) / f };
        }

        template <typename U>
            requires(std::integral<U> || std::floating_point<U>)
        auto operator+(const Vec3<U>& other) const
        {
            using R = std::common_type_t<T, U>;
            return Vec3<R>{ static_cast<R>(x) + static_cast<R>(other.x),
                            static_cast<R>(y) + static_cast<R>(other.y),
                            static_cast<R>(z) + static_cast<R>(other.z) };
        }

        template <typename U>
            requires(std::integral<U> || std::floating_point<U>)
        auto operator-(const Vec3<U>& other) const
        {
            using R = std::common_type_t<T, U>;
            return Vec3<R>{ static_cast<R>(x) - static_cast<R>(other.x),
                            static_cast<R>(y) - static_cast<R>(other.y),
                            static_cast<R>(z) - static_cast<R>(other.z) };
        }

        Vec3<T>& operator=(Vec3<T> const& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
            return *this;
        }

        T x, y, z;
    };

} // namespace icm20948
