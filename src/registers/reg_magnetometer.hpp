#pragma once
#include "register_base.hpp"
#include <cstdint>
#include <sys/types.h>

namespace icm20948::registers::mag::addresses
{
    inline constexpr uint8_t WIA2 = 0x01;
    inline constexpr uint8_t ST1 = 0x10;
    inline constexpr uint8_t HXL = 0x11;
    inline constexpr uint8_t HXH = 0x12;
    inline constexpr uint8_t HYL = 0x13;
    inline constexpr uint8_t HYH = 0x14;
    inline constexpr uint8_t HZL = 0x15;
    inline constexpr uint8_t HZH = 0x16;
    inline constexpr uint8_t ST2 = 0x18;
    inline constexpr uint8_t CNTL2 = 0x31;
    inline constexpr uint8_t CNTL3 = 0x32;
} // namespace icm20948::registers::mag::addresses

namespace icm20948::registers::mag
{
    struct WIA : RegBase<addresses::WIA2, UserBank::MAG, AccessT::r>
    {
        BitField<0, 7> DEVICE_ID{};
    };

    struct ST1 : RegBase<addresses::ST1, UserBank::MAG, AccessT::r>
    {
        Bit<1> DOR{};
        Bit<0> DRDY{};
    };

    struct HX : RegBase<addresses::HXH, UserBank::MAG, AccessT::r, uint16_t>
    {
        BitField<0, 15> VAL{};
    };

    struct HY : RegBase<addresses::HYH, UserBank::MAG, AccessT::r, uint16_t>
    {
        BitField<0, 15> VAL{};
    };

    struct HZ : RegBase<addresses::HZH, UserBank::MAG, AccessT::r, uint16_t>
    {
        BitField<0, 15> VAL{};
    };

    struct ST2 : RegBase<addresses::ST2, UserBank::MAG, AccessT::r>
    {
        Bit<3> HOFL{};
    };

    struct CNTRL2 : RegBase<addresses::CNTL2, UserBank::MAG, AccessT::rw>
    {
        enum class mode_select : uint8_t
        {
            power_down = 0b00000,
            single_measurement = 0b00001,
            continuous_measurement1 = 0b00010,
            continuous_mesaurement2 = 0b00100,
            continuous_mesaurement3 = 0b00110,
            continuous_mesaurement4 = 0b01000,
            self_test = 0b10000
        };

        BitField<0, 4> MODE{};
    };

    struct CNTRL3 : RegBase<addresses::CNTL3, UserBank::MAG, AccessT::rw>
    {
        Bit<0> SRST{};
    };
} // namespace icm20948::registers::mag
