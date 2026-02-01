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
        I2C i2c_instance_;
        ICM20948(i2c_inst_t* i2c_instance);

        uint8_t who_am_i();

        void enable_magnetometer();

        uint16_t get_temp();
    };
} // namespace icm20948
