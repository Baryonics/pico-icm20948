#pragma once
#include "register_base.hpp"
#include <cstdint>

namespace icm20948::registers::addresses
{

    inline constexpr uint8_t WHO_AM_I = 0x00;
    inline constexpr uint8_t USER_CTRL = 0x03;
    inline constexpr uint8_t LP_CONFIG = 0x05;
    inline constexpr uint8_t PWR_MGMT_1 = 0x06;
    inline constexpr uint8_t PWR_MGMT_2 = 0x07;
    inline constexpr uint8_t INT_PIN_CFG = 0x15;
    inline constexpr uint8_t INT_ENABLE = 0x10;
    inline constexpr uint8_t INT_ENABLE_1 = 0x11;
    inline constexpr uint8_t INT_ENABLE_2 = 0x12;
    inline constexpr uint8_t INT_ENABLE_3 = 0x13;
    inline constexpr uint8_t I2C_MST_STATUS = 0x17;
    inline constexpr uint8_t INT_STATUS = 0x19;
    inline constexpr uint8_t INT_STATUS_1 = 0x1A;
    inline constexpr uint8_t INT_STATUS_2 = 0x1B;
    inline constexpr uint8_t INT_STATUS_3 = 0x1C;
    inline constexpr uint8_t DELAY_TIMEH = 0x28;
    inline constexpr uint8_t DELAY_TIMEL = 0x29;
    inline constexpr uint8_t ACCEL_XOUT_H = 0x2D;
    inline constexpr uint8_t ACCEL_XOUT_L = 0x2E;
    inline constexpr uint8_t ACCEL_YOUT_H = 0x2F;
    inline constexpr uint8_t ACCEL_YOUT_L = 0x30;
    inline constexpr uint8_t ACCEL_ZOUT_H = 0x31;
    inline constexpr uint8_t ACCEL_ZOUT_L = 0x32;
    inline constexpr uint8_t GYRO_XOUT_H = 0x33;
    inline constexpr uint8_t GYRO_XOUT_L = 0x34;
    inline constexpr uint8_t GYRO_YOUT_H = 0x35;
    inline constexpr uint8_t GYRO_YOUT_L = 0x36;
    inline constexpr uint8_t GYRO_ZOUT_H = 0x37;
    inline constexpr uint8_t GYRO_ZOUT_L = 0x38;
    inline constexpr uint8_t TEMP_OUT_H = 0x39;
    inline constexpr uint8_t TEMP_OUT_L = 0x3A;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_00 = 0x3B;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_01 = 0x3C;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_02 = 0x3D;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_03 = 0x3E;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_04 = 0x3F;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_05 = 0x40;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_06 = 0x41;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_07 = 0x42;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_08 = 0x43;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_09 = 0x44;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_10 = 0x45;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_11 = 0x46;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_12 = 0x47;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_13 = 0x48;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_14 = 0x49;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_15 = 0x4A;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_16 = 0x4B;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_17 = 0x4C;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_18 = 0x4D;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_19 = 0x4E;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_20 = 0x4F;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_21 = 0x50;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_22 = 0x51;
    inline constexpr uint8_t EXT_SLV_SENS_DATA_23 = 0x52;
    inline constexpr uint8_t FIFO_EN_1 = 0x66;
    inline constexpr uint8_t FIFO_EN_2 = 0x67;
    inline constexpr uint8_t FIFO_RST = 0x68;
    inline constexpr uint8_t FIFO_MODE = 0x69;
    inline constexpr uint8_t FIFO_COUNTH = 0x70;
    inline constexpr uint8_t FIFO_COUNTL = 0x71;
    inline constexpr uint8_t FIFO_R_W = 0x72;
    inline constexpr uint8_t DATA_RDY_STATUS = 0x74;
    inline constexpr uint8_t FIFO_CFG = 0x76;
    inline constexpr uint8_t REG_BANK_SEL = 0x7F;
} // namespace icm20948::registers::addresses

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

    struct GYRO_ZOUT : RegBase<addresses::GYRO_ZOUT_H, UserBank::UB0, AccessT::r, uint16_t>
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

    struct FIFO_EN_1 : RegBase<addresses::FIFO_EN_1, UserBank::UB0, AccessT::rw>
    {
        Bit<3> SLV_3_FIFO_EN{};
        Bit<2> SLV_2_FIFO_EN{};
        Bit<1> SLV_1_FIFO_EN{};
        Bit<0> SLV_0_FIFO_EN{};
    };

    struct FIFO_EN_2 : RegBase<addresses::FIFO_EN_2, UserBank::UB0, AccessT::rw>
    {
        Bit<4> ACCEL_FIFO_EN{};
        Bit<3> Gyro_Z_FIFO_EN{};
        Bit<2> GYRO_Y_FIFO_EN{};
        Bit<1> GYRO_X_FIFO_EN{};
        Bit<0> TEMP_FIFO_EN{};
    };

    struct FIFO_RST : RegBase<addresses::FIFO_MODE, UserBank::UB0, AccessT::rw>
    {
        BitField<0, 4> FIFO_RESET{};
    };

    struct FIFO_MODE : RegBase<addresses::FIFO_RST, UserBank::UB0, AccessT::rw>
    {
        enum class mode : uint8_t
        {
            stream = 0,
            snapshot = 1
        };

        BitField<0, 4> FIFO_MODE{};
    };

    struct FIFO_COUNT : RegBase<addresses::FIFO_COUNTH, UserBank::UB0, AccessT::r, uint16_t>
    {
        BitField<0, 12> FIFO_CNT{};
    };

    struct FIFO_R_W : RegBase<addresses::FIFO_R_W, UserBank::UB0, AccessT::rw>
    {
        BitField<0, 7> R_W{};
    };

    struct DATA_RDY_STATUS : RegBase<addresses::DATA_RDY_STATUS, UserBank::UB0, AccessT::r>
    {
        Bit<7> WOF_STATUS{};
        BitField<0, 3> RAW_DATA_RDY{};
    };

    struct FIFO_CFG : RegBase<addresses::FIFO_CFG, UserBank::UB0, AccessT::rw>
    {
        Bit<0> FG{};
    };
} // namespace icm20948::registers
