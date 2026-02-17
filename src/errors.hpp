#pragma once

#include <cstdint>
#include <expected>
namespace icm20948
{
    enum class ICMErrorT : uint8_t
    {
        i2c_write_failed,
        i2c_read_failed
    };

    template <typename T>
    using ErrorT = std::expected<T, ICMErrorT>;
} // namespace icm20948
