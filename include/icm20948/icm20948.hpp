#pragma once

#include "i2c.hpp"
// #include "registers/userbank1.hpp"
// #include "registers/userbank2.hpp"
// #include "registers/userbank3.hpp"
#include <cstdint>
#include <hardware/i2c.h>

namespace icm20948
{
    struct ICM20948
    {
        ICM20948(i2c_inst_t* i2c_instance);

        I2C i2c_instance_;

        void enable_magnetometer();
    };
} // namespace icm20948
