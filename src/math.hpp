#pragma once

#include "errors.hpp"
#include <array>
#include <cassert>
#include <concepts>
#include <cstdint>
#include <expected>
#include <iterator>
#include <ranges>
#include <sys/cdefs.h>
#include <type_traits>
#include <utility>

namespace icm20948
{

    template <typename T>
        requires(std::integral<T> || std::floating_point<T>)
    struct Vec3
    {
        constexpr Vec3() = default;

        constexpr Vec3(T x, T y, T z)
            : x(x)
            , y(y)
            , z(z)
        {
        }

        template <typename U>
            requires(std::integral<U> || std::floating_point<U>)
        constexpr Vec3(const Vec3<U>& other)
            : x(static_cast<T>(other.x))
            , y(static_cast<T>(other.y))
            , z(static_cast<T>(other.z))
        {
        }

        auto operator/(float const f) const -> Vec3<float>
        {
            return Vec3<float>{ static_cast<float>(x) / f, static_cast<float>(y) / f, static_cast<float>(z) / f };
        }

        auto operator*(float const f) const -> Vec3<float>
        {
            return Vec3<float>{ static_cast<float>(x) * f, static_cast<float>(y) * f, static_cast<float>(z) * f };
        }

        template <typename U>
            requires(std::integral<U> || std::floating_point<U>)
        auto operator*(const Vec3<U>& other) const
        {
            using R = std::common_type_t<T, U>;

            return Vec3<R>{ static_cast<R>(x) * static_cast<R>(other.x),
                            static_cast<R>(y) * static_cast<R>(other.y),
                            static_cast<R>(z) * static_cast<R>(other.z) };
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

        auto operator=(Vec3<T> const& v) -> Vec3<T>&
        {
            x = v.x;
            y = v.y;
            z = v.z;
            return *this;
        }

        constexpr auto operator[](const uint8_t idx) -> T& { return (idx == 0) ? x : (idx == 1 ? y : z); }
        constexpr auto operator[](const uint8_t idx) const -> const T& { return (idx == 0) ? x : (idx == 1 ? y : z); }

        T x, y, z;
    };

    template <typename T>
        requires(std::integral<T> || std::floating_point<T>)
    struct Mat3
    {
        constexpr Mat3() = default;

        constexpr explicit Mat3(const std::array<std::array<T, 3>, 3>& mat)
            : m(mat)
        {
        }

        constexpr Mat3(const Vec3<T>& col_1, const Vec3<T>& col_2, const Vec3<T>& col_3)
            : m{ { { col_1.x, col_2.x, col_3.x }, { col_1.y, col_2.y, col_3.y }, { col_1.z, col_2.z, col_3.z } } }
        {
        }

        template <typename U>
            requires(std::integral<U> || std::floating_point<U>)
        auto operator*(const Vec3<U>& v) const
        {
            using R = std::common_type_t<T, U>;
            auto range = std::views::iota(uint8_t{ 0 }, uint8_t{ 3 });
            auto out = Vec3<R>{};
            for (auto idx_r : range)
            {
                for (auto idx_c : range)
                {
                    out[idx_r] += static_cast<R>(m[idx_r][idx_c]) * static_cast<R>(v[idx_c]);
                }
            }
            return out;
        }

        std::array<std::array<T, 3>, 3> m{ {} }; // m[row][col]
    };
} // namespace icm20948
