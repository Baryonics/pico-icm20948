#pragma once

#include "math.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

namespace icm20948::calibration
{
    inline constexpr auto INT16_MAX_DIGITS = uint8_t{ 6 }; // -32,768 to 32,767
    inline constexpr auto INT32_MAX_DIGITS = uint8_t{ 10 };
    inline constexpr auto CALIB_MSG_SIZE = uint8_t{ 9 * INT16_MAX_DIGITS + INT32_MAX_DIGITS + 12 };

    struct CalibrationSample
    {
        Vec3<int16_t> acc_val{};
        Vec3<int16_t> gyro_val{};
        Vec3<int16_t> mag_val{};
    };

    struct Calibration
    {
        Vec3<float> accel_bias{};
        Vec3<float> accel_scale{ 1.0, 1.0, 1.0 };
        Vec3<float> gyro_bias{};
        Vec3<float> mag_hard_iron{};
        Mat3<float> mag_soft_iron{ UNIT_MAT };
    };
} // namespace icm20948::calibration
