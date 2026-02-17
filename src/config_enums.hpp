#pragma once

#include <cstdint>

namespace icm20948
{
    enum class AccelRange : uint8_t
    {
        g2,
        g4,
        g8,
        g16
    };

    enum class GyroRange : uint8_t
    {
        dps250,
        dps500,
        dps1000,
        dps2000
    };

    enum class SlaveMode : uint8_t
    {
        read,
        write
    };

    enum class SlaveNum : uint8_t
    {
        svl0,
        slv1,
        slv2,
        slv3,
        slv4
    };
} // namespace icm20948
