#pragma once

#include "raw_data.hpp"
#include "userbank2.hpp"
namespace icm20948
{
    struct Accel
    {
        registers::ACCEL_CONFIG config{};
        registers::ACCEL_CONFIG_2 config2{};
        registers::ACCEL_INTEL_CTRL accel_intel_ctrl{};

        void update_from_raw(data::RawAccData& raw);
        void configure();
    };
} // namespace icm20948
