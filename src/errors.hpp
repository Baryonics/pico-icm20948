#pragma once

#include <cstdint>
#include <expected>

// arm-none-eabi-g++ does not contain expected::end_then() :(
#define TRY(expr)                               \
    do                                          \
    {                                           \
        if (auto _r = (expr); !_r)              \
            return std::unexpected(_r.error()); \
    } while (0)

namespace icm20948
{
    enum class ICMErrorT : uint8_t
    {
        i2c_write_failed,
        i2c_read_failed,
        i2c_mag_nack,
        ic2_mag_arb,
        i2c_mag_timeout
    };

    template <typename T>
    using ErrorT = std::expected<T, ICMErrorT>;
} // namespace icm20948
