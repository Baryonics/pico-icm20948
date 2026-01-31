#pragma once
#include "register_base.hpp"
#include "register_map.hpp"
#include <cstdint>

namespace icm20948::registers
{
    struct REG_BANK_SEL : RegBase<addresses::REG_BANK_SEL, UserBank::UB0, AccessT::rw>
    {
        BitField<4, 5> USER_BANK{};
    };

    struct WHO_AM_I : RegBase<addresses::WHO_AM_I, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> WHO_I_AM;
    };

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
        enum class ClockSource : uint8_t
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
        enum class accele_pwr : uint8_t
        {
            accel_on = 7,
            accel_off = 0
        };

        enum class gyro_pwr : uint8_t
        {
            gyro_on = 7,
            gyro_off = 0
        };

        BitField<6, 7> DISABLE_ACCEL{};
        BitField<0, 2> DISABLE_GYRO{};
    };

    struct INT_PIN_CFG : RegBase<addresses::INT_PIN_CFG, UserBank::UB0, AccessT::rw>
    {
        Bit<7> INT1_ACTL{};
        Bit<6> INT1_OPEN{};
        Bit<5> INT1_LATCH_EN{};
        Bit<4> INT_ANYRD_2CLEAR{};
        Bit<3> ACTL_FSYNC{};
        Bit<2> FSYNC_INT_MODE_EN{};
        Bit<1> BYPASS_EN{};
    };

    struct INT_ENABLE : RegBase<addresses::INT_ENABLE, UserBank::UB0, AccessT::rw>
    {
        Bit<7> REG_WOF_EN{};
        Bit<3> WOM_INT_EN{};
        Bit<2> PLL_RDY_EN{};
        Bit<1> DMP_INT1_EN{};
        Bit<0> I2C_MST_INT_EN{};
    };

    struct INT_ENABLE_1 : RegBase<addresses::INT_ENABLE_1, UserBank::UB0, AccessT::rw>
    {
        Bit<0> RAW_DATA_0_RDY_EN{};
    };

    struct INT_ENABLE_2 : RegBase<addresses::INT_ENABLE_2, UserBank::UB0, AccessT::rw>
    {
        enum class enable_data_ready_interupt : uint8_t
        {
            enable = 1,
            disable = 0
        };
        BitField<0, 4> FIFO_OVERFLOW_EN{};
    };

    struct INT_ENABLE_3 : RegBase<addresses::INT_ENABLE_3, UserBank::UB0, AccessT::rw>
    {
        enum class enable_watermark_interrupt : uint8_t
        {
            enable = 1,
            disable = 0
        };
        BitField<0, 4> FIFO_WM_EN{};
    };

    struct I2C_MST_STATUS : RegBase<addresses::I2C_MST_STATUS, UserBank::UB0, AccessT::r>
    {
        Bit<7> PASS_THROUGH{};
        Bit<6> I2C_SLV4_DONE{};
        Bit<5> I2C_LOST_ARB{};
        Bit<4> I2C_SLV4_NACK{};
        Bit<3> I2C_SLV3_NACK{};
        Bit<2> I2C_SLV2_NACK{};
        Bit<1> I2C_SLV1_NACK{};
        Bit<0> I2C_SLV0_NACK{};
    };

    struct INT_STATUS : RegBase<addresses::INT_STATUS, UserBank::UB0, AccessT::r>
    {
        Bit<3> WOM_INIT{};
        Bit<2> PLL_RDY_INT{};
        Bit<1> DMP_INT1{};
        Bit<0> I2C_MST_INT{};
    };

    struct INT_STATUS_1 : RegBase<addresses::INT_STATUS_1, UserBank::UB0, AccessT::r>
    {
        Bit<0> RAW_DATA_0_RDY_INT{};
    };

    struct INT_STATUS_2 : RegBase<addresses::INT_STATUS_2, UserBank::UB0, AccessT::r>
    {
        BitField<0, 4> FIFO_OVERFLOW_INT{};
    };

    struct INT_STATUS_3 : RegBase<addresses::INT_STATUS_3, UserBank::UB0, AccessT::r>
    {
        BitField<0, 4> FIFO_WM_INT{};
    };

    struct DELAY_TIME : RegBase<addresses::DELAY_TIMEH, UserBank::UB0, AccessT::r, uint16_t>
    {
        BitField<0, 15> DELAY_TIME_V{};
    };

    struct ACCEL_XOUT : RegBase<addresses::ACCEL_XOUT_H, UserBank::UB0, AccessT::r, uint16_t>
    {
        BitField<0, 15> VALUE{};
    };

    struct ACCEL_YOUT : RegBase<addresses::ACCEL_YOUT_H, UserBank::UB0, AccessT::r, uint16_t>
    {
        BitField<0, 15> VAULE{};
    };

    struct ACCEL_ZOUT : RegBase<addresses::ACCEL_ZOUT_H, UserBank::UB0, AccessT::r, uint16_t>
    {
        BitField<0, 15> VALUE{};
    };

    struct GYRO_XOUT : RegBase<addresses::GYRO_XOUT_H, UserBank::UB0, AccessT::r, uint16_t>
    {
        BitField<0, 15> VALUE{};
    };

    struct GYRO_YOUT : RegBase<addresses::GYRO_YOUT_H, UserBank::UB0, AccessT::r, uint16_t>
    {
        BitField<0, 15> VALUE{};
    };

    struct GYRO_zOUT : RegBase<addresses::GYRO_ZOUT_H, UserBank::UB0, AccessT::r, uint16_t>
    {
        BitField<0, 15> VALUE{};
    };

    struct TEMP_OUT : RegBase<addresses::TEMP_OUT_H, UserBank::UB0, AccessT::r, uint16_t>
    {
        BitField<0, 15> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_00 : RegBase<addresses::EXT_SLV_SENS_DATA_00, UserBank::UB0, AccessT::r, uint16_t>
    {
        BitField<0, 15> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_01 : RegBase<addresses::EXT_SLV_SENS_DATA_01, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_02 : RegBase<addresses::EXT_SLV_SENS_DATA_02, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_03 : RegBase<addresses::EXT_SLV_SENS_DATA_03, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_04 : RegBase<addresses::EXT_SLV_SENS_DATA_04, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_05 : RegBase<addresses::EXT_SLV_SENS_DATA_05, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_06 : RegBase<addresses::EXT_SLV_SENS_DATA_06, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_07 : RegBase<addresses::EXT_SLV_SENS_DATA_07, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_08 : RegBase<addresses::EXT_SLV_SENS_DATA_08, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_09 : RegBase<addresses::EXT_SLV_SENS_DATA_09, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_10 : RegBase<addresses::EXT_SLV_SENS_DATA_10, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_11 : RegBase<addresses::EXT_SLV_SENS_DATA_11, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

    struct EXT_SLV_SENS_DATA_12 : RegBase<addresses::EXT_SLV_SENS_DATA_12, UserBank::UB0, AccessT::r>
    {
        BitField<0, 7> VALUE{};
    };

} // namespace icm20948::registers
