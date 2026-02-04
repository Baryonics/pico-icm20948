#pragma once

#include "registers/userbank2.hpp"
#include <cstdint>

namespace icm20948::data
{
    struct RawData
    {
        int16_t x;
        int16_t y;
        int16_t z;
    };

    struct RawAccData : RawData
    {
    };

    struct RawGyroData : RawData
    {
    };

    struct RawTempData
    {
        int16_t temp;
    };

    struct RawMagData
    {
    };

    struct ComposedRawData
    {
        RawAccData acc{};
        RawGyroData gyro{};
        RawTempData temp{};
        RawMagData mag{};
    };

    constexpr uint8_t RAW_COMPOSED_SIZE = sizeof(data::ComposedRawData);
} // namespace icm20948::data
