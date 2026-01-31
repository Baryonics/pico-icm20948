#pragma once
#include "core/register_base.hpp"
#include "hardware/i2c.h"

namespace icm20948
{
    class I2C
    {
        i2c_inst_t i2c_;

      public:
        I2C() = default;
        I2C(i2c_inst_t i2c)
            : i2c_(i2c) {};

        template <typename RegType>
            requires(registers::reg_type<RegType>)
        void write(RegType reg)
        {
            i2c_write_blocking(&i2c_, reg.address, &reg.bits, sizeof(reg.bits), true);
        }

        template <typename RegType>
            requires(registers::reg_type<RegType>)
        RegType read()
        {
            RegType reg{};
            i2c_read_blocking(&i2c_, reg.address, &reg.bits, sizeof(reg.bits), true);
            return reg;
        }
    };
} // namespace icm20948
