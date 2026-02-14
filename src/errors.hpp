#pragma once

#include <cstdint>
namespace icm20948
{
    enum class ICMErrorT : uint8_t
    {
        i2c_write_failed,
        i2c_read_failed
    };
}
