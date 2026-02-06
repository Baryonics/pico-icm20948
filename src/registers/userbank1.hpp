#pragma once
#include "register_base.hpp"
#include <cstdint>

namespace icm20948::registers::addresses
{
    inline constexpr uint8_t SELF_TEST_X_GYRO = 0x02;
    inline constexpr uint8_t SELF_TEST_Y_GYRO = 0x03;
    inline constexpr uint8_t SELF_TEST_Z_GYRO = 0x04;
    inline constexpr uint8_t SELF_TEST_X_ACCEL = 0x0E;
    inline constexpr uint8_t SELF_TEST_Y_ACCEL = 0x0F;
    inline constexpr uint8_t SELF_TEST_Z_ACCEL = 0x10;
    inline constexpr uint8_t XA_OFFS_H = 0x14;
    inline constexpr uint8_t XA_OFFS_L = 0x15;
    inline constexpr uint8_t YA_OFFS_H = 0x17;
    inline constexpr uint8_t YA_OFFS_L = 0x18;
    inline constexpr uint8_t ZA_OFFS_H = 0x1A;
    inline constexpr uint8_t ZA_OFFS_L = 0x1B;
    inline constexpr uint8_t TIMEBASE_CORRECTION_PLL = 0x28;
} // namespace icm20948::registers::addresses

namespace icm20948::registers
{

    struct SELF_TEST_X_GYRO : RegBase<addresses::SELF_TEST_X_GYRO, UserBank::UB1, AccessT::rw>
    {
        static constexpr BitField<0, 7> XG_ST_DATA{};
    };

    struct SELF_TEST_Y_GYRO : RegBase<addresses::SELF_TEST_Y_GYRO, UserBank::UB1, AccessT::rw>
    {
        static constexpr BitField<0, 7> YG_ST_DATA{};
    };

    struct SELF_TEST_Z_GYRO : RegBase<addresses::SELF_TEST_Z_GYRO, UserBank::UB1, AccessT::rw>
    {
        static constexpr BitField<0, 7> ZG_ST_DATA{};
    };

    struct SELF_TEST_X_ACCEL : RegBase<addresses::SELF_TEST_X_ACCEL, UserBank::UB1, AccessT::rw>
    {
        static constexpr BitField<0, 7> XA_ST_DATA{};
    };

    struct SELF_TEST_Y_ACCEL : RegBase<addresses::SELF_TEST_Y_ACCEL, UserBank::UB1, AccessT::rw>
    {
        static constexpr BitField<0, 7> YA_ST_DATA{};
    };

    struct SELF_TEST_Z_ACCEL : RegBase<addresses::SELF_TEST_Z_ACCEL, UserBank::UB1, AccessT::rw>
    {
        static constexpr BitField<0, 7> ZA_ST_DATA{};
    };

    struct XA_OFFS : RegBase<addresses::XA_OFFS_H, UserBank::UB1, AccessT::rw, uint16_t>
    {
        static constexpr BitField<0, 14> OFFS{};
    };

    struct YA_OFFS : RegBase<addresses::YA_OFFS_H, UserBank::UB1, AccessT::rw, uint16_t>
    {
        static constexpr BitField<0, 14> OFFS{};
    };

    struct ZA_OFFS : RegBase<addresses::ZA_OFFS_H, UserBank::UB1, AccessT::rw, uint16_t>
    {
        static constexpr BitField<0, 14> OFFS{};
    };

    struct TIMEBASE_CORRECTION_PLL : RegBase<addresses::TIMEBASE_CORRECTION_PLL, UserBank::UB1, AccessT::rw>
    {
        enum struct clock_period_error : int8_t
        {
            ten_perc = 10,
            neg_ten_perc = 10
        };

        static constexpr BitField<0, 7> TBC_PLL{};
    };
} // namespace icm20948::registers
