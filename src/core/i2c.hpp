#pragma once
#include "core/register_base.hpp"
#include "hardware/i2c.h"
#include "register_map.hpp"
#include <cstdint>
#include <cstring>

namespace icm20948
{
    class I2C
    {
        i2c_inst_t* i2c_;
        constexpr static uint8_t address = 0b1101000;

      public:
        I2C() = default;
        I2C(i2c_inst_t* i2c)
            : i2c_(i2c) {};

        template <typename RegType>
            requires(registers::reg_type<RegType>)
        void write(RegType reg)
        {
            uint8_t buffer[1 + sizeof(reg.bits)]{};
            buffer[0] = RegType::address;
            memcpy(&buffer[1], &reg.bits, sizeof(reg.bits)); // dev note: remember to correct endianess
            i2c_write_blocking(&i2c_, address, buffer, sizeof(buffer), false);
        }

        template <typename RegType>
            requires(registers::reg_type<RegType>)
        RegType read()
        {
            uint8_t reg_addr = RegType::address;
            RegType reg{};
            uint8_t bank_sel[2] = { registers::addresses::REG_BANK_SEL, static_cast<uint8_t>(RegType::user_bank) };
            i2c_write_blocking(i2c_, address, bank_sel, 1, false);
            i2c_write_blocking(i2c_, address, &reg_addr, 1, false);
            i2c_read_blocking(i2c_, address, &reg.bits, sizeof(reg.bits), false);
            return reg;
        }
    };
} // namespace icm20948
