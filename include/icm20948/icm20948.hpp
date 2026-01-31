#pragma once

#include "../src/core/registers.hpp"
#include "core/i2c.hpp"
#include <cstdint>
#include <hardware/i2c.h>

namespace icm20948
{
    struct ICM20948
    {
        ICM20948(i2c_inst_t* i2c_instance)
            : i2c_instance_(i2c_instance) {};

        I2C i2c_instance_;

        registers::USER_CTRL usr_ctrl{};
        registers::PWR_MGMT_1 pwr_mgmt_1{};

        void write();

        uint8_t test_read();
        uint8_t read_int_status();
    };
} // namespace icm20948
