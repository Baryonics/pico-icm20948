#pragma once

#include "math.hpp"
#include <array>
#include <cstddef>
#include <cstdint>

namespace icm20948::calibration
{
    constexpr inline Mat3<float> UNIT_MAT = { Vec3<float>{ 1, 0, 0 }, Vec3<float>{ 0, 1, 0 }, Vec3<float>{ 0, 0, 1 } };

    struct CalibrationSample
    {
        Vec3<float> acc_val{};
        Vec3<float> gyro_val{};
        Vec3<float> mag_val{};
        uint32_t time_stamp{};
    };

    struct Calibration
    {
        Vec3<float> accel_bias{};
        Vec3<float> accel_scale{ 1.0, 1.0, 1.0 };
        Vec3<float> gyro_bias{};
        Vec3<float> mag_hard_iron{};
        Mat3<float> mag_soft_iron{ UNIT_MAT };
    };
    constexpr size_t MSG_OFFSET{ 10 }; // Not sure. This is an estimate, needs further dev
    constexpr size_t MSG_SIZE = sizeof(CalibrationSample) + MSG_OFFSET;

    auto to_csv_line(const CalibrationSample& sample) -> std::array<char, MSG_SIZE>;

} // namespace icm20948::calibration
