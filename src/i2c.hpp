#pragma once
#include "errors.hpp"
#include "hardware/i2c.h"
#include "registers/register_base.hpp"
#include "registers/userbank0.hpp"
#include <cstdint>
#include <cstring>
#include <expected>
#include <pico/error.h>
#include <pico/stdio.h>
#include <span>

namespace icm20948
{
    class I2C
    {
        i2c_inst_t* i2c_{};
        registers::UserBank current_ub_ = registers::UserBank::UB0;
        constexpr static uint8_t address = 0b1101000;

        ErrorT<void> select_user_bank(const registers::UserBank& ub)
        {
            if (current_ub_ == ub)
            {
                return {};
            }
            auto bank_sel = registers::REG_BANK_SEL{};
            bank_sel.set_field(bank_sel.USER_BANK, ub);
            uint8_t buffer[2U] = { bank_sel.address, bank_sel.bits };
            if (auto r = i2c_write_blocking(i2c_, address, buffer, 2U, false); r < 0U)
            {
                return std::unexpected(ICMErrorT::i2c_write_failed);
            }
            current_ub_ = ub;
            return {};
        }

      public:
        I2C() = default;
        I2C(i2c_inst_t* i2c)
            : i2c_(i2c) {};

        template <typename RegType>
            requires(registers::reg_type<RegType>)
        ErrorT<void> single_write(const RegType& reg)
        {
            uint8_t buffer[1 + sizeof(reg.bits)]{};
            buffer[0] = RegType::address;
            memcpy(&buffer[1], &reg.bits, sizeof(reg.bits));
            if (auto r = select_user_bank(RegType::user_bank); !r)
            {
                return std::unexpected(r.error());
            }
            if (auto r = i2c_write_blocking(i2c_, address, buffer, sizeof(buffer), false); r < 0)
            {
                return std::unexpected(ICMErrorT::i2c_write_failed);
            }
            return {};
        }

        template <typename... RegTypes>
            requires(registers::reg_type<RegTypes> && ...)
        ErrorT<void> write(const RegTypes&... regs)
        {
            ErrorT<void> res{};

            auto try_one = [&](auto const& r) -> bool
            {
                res = single_write(r);
                return res.has_value();
            };

            (try_one(regs) && ...);

            return res;
        }

        template <typename RegType>
            requires(registers::reg_type<RegType>)
        ErrorT<RegType> read()
        {
            uint8_t reg_addr = RegType::address;
            RegType reg{};
            if (auto r = select_user_bank(RegType::user_bank); !r)
            {
                return std::unexpected(r.error());
            }
            if (auto r = i2c_write_blocking(i2c_, address, &reg_addr, 1, true); r < 0)
            {
                return std::unexpected(ICMErrorT::i2c_write_failed);
            }
            uint8_t buffer[sizeof(reg.bits)]{};
            if (auto r = i2c_read_blocking(i2c_, address, buffer, sizeof(reg.bits), false); r < 0)
            {
                return std::unexpected(ICMErrorT::i2c_read_failed);
            }
            memcpy(&reg.bits, buffer, sizeof(reg.bits));
            return reg;
        }

        template <typename T>
            requires(registers::reg_type<T>)
        ErrorT<void> block_read(std::span<uint8_t> dst)
        {
            if (auto r = select_user_bank(T::user_bank); !r)
            {
                return std::unexpected(r.error());
            }
            if (auto r = i2c_write_blocking(i2c_, address, &T::address, 1, true); r < 0)
            {
                return std::unexpected(ICMErrorT::i2c_write_failed);
            }
            if (auto r = i2c_read_blocking(i2c_, address, dst.data(), dst.size(), false); r < 0)
            {
                return std::unexpected(ICMErrorT::i2c_read_failed);
            }
            return {};
        }
    };
} // namespace icm20948
