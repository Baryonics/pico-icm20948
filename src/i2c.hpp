#pragma once
#include "hardware/i2c.h"
#include "registers/magnetometer.hpp"
#include "registers/register_base.hpp"
#include "registers/userbank0.hpp"
#include "registers/userbank1.hpp"
#include "registers/userbank2.hpp"
#include "registers/userbank3.hpp"
#include <cstdint>
#include <cstring>

namespace icm20948
{
    class I2C
    {
        i2c_inst_t* i2c_{};
        registers::UserBank current_ub_{};
        constexpr static uint8_t address = 0b1101000;

        void select_user_bank(registers::UserBank ub)
        {
            if (current_ub_ == ub)
            {
                return;
            }
            auto bank_sel = registers::REG_BANK_SEL{};
            bank_sel.set_field(bank_sel.USER_BANK, ub);

            uint8_t buffer[2] = { bank_sel.address, bank_sel.bits };
            i2c_write_blocking(i2c_, address, buffer, 2, false);
            current_ub_ = ub;
        }

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
            select_user_bank(RegType::user_bank);
            i2c_write_blocking(i2c_, address, buffer, sizeof(buffer), false);
        }

        template <typename RegType>
            requires(registers::reg_type<RegType>)
        RegType read()
        {
            uint8_t reg_addr = RegType::address;
            RegType reg{};
            select_user_bank(RegType::user_bank);
            i2c_write_blocking(i2c_, address, &reg_addr, 1, true);
            i2c_read_blocking(i2c_, address, &reg.bits, sizeof(reg.bits), false);
            return reg;
        }
    };
} // namespace icm20948
