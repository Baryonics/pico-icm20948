#pragma once
#include "register_base.hpp"
#include "register_map.hpp"
namespace icm20948::registers
{
    struct USER_CTRL : RegBase<addresses::USER_CTRL, UserBank::UB0, AccessT::rw>
    {
        Bit<7> DMP_EN{};
        Bit<6> FIFO_EN{};
        Bit<5> I2C_MST_EN{};
        Bit<4> I2C_IF_DIS{};
        Bit<3> DMP_RST{};
        Bit<2> SRAM_RST{};
        Bit<1> I2C_MST_RST{};
    };

    struct LP_CONFIG : RegBase<addresses::LP_CONFIG, UserBank::UB0, AccessT::rw>
    {
        Bit<6> I2C_MST_CYCLE{};
        Bit<5> ACCEL_CYCLE{};
        Bit<4> GYRO_CYCLE{};
    };

    struct PWR_MGMT_1 : RegBase<addresses::PWR_MGMT_1, UserBank::UB0, AccessT::rw>
    {
        enum class ClockSource
        {
            internal = 0,
            auto_sel = 1,
            stop_clk = 7
        };

        Bit<7> DEVICE_RESET{};
        Bit<6> SLEEP{};
        Bit<5> LP_EN{};
        Bit<3> TEMP_DIS{};
        BitField<0, 2> CLKSEL{};
    };

    struct PWR_MGMT_2 : RegBase<addresses::PWR_MGMT_2, UserBank::UB0, AccessT::rw>
    {
        BitField<6, 7> DISABLE_ACCEL{};
        BitField<0, 2> DISABLE_GYRO{};
    };
} // namespace icm20948::registers
