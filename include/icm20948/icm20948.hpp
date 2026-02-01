#pragma once

#include "i2c.hpp"
#include "register_base.hpp"
// #include "registers/userbank1.hpp"
// #include "registers/userbank2.hpp"
// #include "registers/userbank3.hpp"
#include <bit>
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

        template <typename ValType>
            requires registers::reg_type<ValType>
        uint16_t get_value()
        {
            auto val_reg = i2c_instance_.read<ValType>();
            return std::byteswap(val_reg.bits);
        }

        uint16_t get_temp();

        uint16_t get_acc_x();
        uint16_t get_acc_y();
        uint16_t get_acc_z();

        uint16_t get_gyro_x();
        uint16_t get_gyro_y();
        uint16_t get_gyro_z();

        uint16_t get_mag_x();
        uint16_t get_mag_y();
        uint16_t get_mag_z();
    };
} // namespace icm20948
