#pragma once
#include "register_base.hpp"
#include "register_map.hpp"
#include <cstdint>
#include <filesystem>

namespace icm20948::registers
{
    struct REG_BANK_SEL : RegBase<addresses::REG_BANK_SEL, UserBank::UB0, AccessT::rw>
    {
        BitField<4, 5> USER_BANK{};
    };

    /** User Bank 0 **/
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

    /** User Bak 1 **/
    struct SELF_TEST_X_GYRO : RegBase<addresses::SELF_TEST_X_GYRO, UserBank::UB1, AccessT::rw>
    {
        BitField<0, 7> XG_ST_DATA{};
    };

    struct SELF_TEST_Y_GYRO : RegBase<addresses::SELF_TEST_Y_GYRO, UserBank::UB1, AccessT::rw>
    {
        BitField<0, 7> YG_ST_DATA{};
    };

    struct SELF_TEST_Z_GYRO : RegBase<addresses::SELF_TEST_Z_GYRO, UserBank::UB1, AccessT::rw>
    {
        BitField<0, 7> ZG_ST_DATA{};
    };

    struct SELF_TEST_X_ACCEL : RegBase<addresses::SELF_TEST_X_ACCEL, UserBank::UB1, AccessT::rw>
    {
        BitField<0, 7> XA_ST_DATA{};
    };

    struct SELF_TEST_Y_ACCEL : RegBase<addresses::SELF_TEST_Y_ACCEL, UserBank::UB1, AccessT::rw>
    {
        BitField<0, 7> YA_ST_DATA{};
    };

    struct SELF_TEST_Z_ACCEL : RegBase<addresses::SELF_TEST_Z_ACCEL, UserBank::UB1, AccessT::rw>
    {
        BitField<0, 7> ZA_ST_DATA{};
    };

    struct XA_OFFS : RegBase<addresses::XA_OFFS_H, UserBank::UB1, AccessT::rw, uint16_t>
    {
        BitField<0, 14> OFFS{};
    };

    struct YA_OFFS : RegBase<addresses::YA_OFFS_H, UserBank::UB1, AccessT::rw, uint16_t>
    {
        BitField<0, 14> OFFS{};
    };

    struct ZA_OFFS : RegBase<addresses::ZA_OFFS_H, UserBank::UB1, AccessT::rw, uint16_t>
    {
        BitField<0, 14> OFFS{};
    };

    struct TIMEBASE_CORRECTION_PLL : RegBase<addresses::TIMEBASE_CORRECTION_PLL, UserBank::UB1, AccessT::rw>
    {
        enum struct clock_period_error : int8_t
        {
            ten_perc = 10,
            neg_ten_perc = 10
        };

        BitField<0, 7> TBC_PLL{};
    };

    /** User Bank 2 **/
    struct GYRO_SMPLRT_DIV : RegBase<addresses::GYRO_SMPLRT_DIV, UserBank::UB2, AccessT::rw>
    {
        BitField<0, 7> SMPTLRT_DIV{};
    };

    struct GYRO_CONFIG_1 : RegBase<addresses::GYRO_CONFIG_1, UserBank::UB2, AccessT::rw>
    {
        enum class full_scale_select : uint8_t
        {
            dps250 = 0,
            dps500 = 1,
            dps1000 = 2,
            dps2000 = 3
        };

        BitField<3, 5> GYRO_DLPFCFG{};
        BitField<1, 2> GYRO_FS_SEL{};
        Bit<0> GYRO_FCHOICE{};
    };

    struct GYRO_CONFIG_2 : RegBase<addresses::GYRO_CONFIG_2, UserBank::UB2, AccessT::rw>
    {
        enum class av_filter_config : uint8_t
        {
            av1x = 0,
            av2x = 1,
            av4x = 2,
            av8x = 3,
            av16x = 4,
            av32x = 5,
            av64x = 6,
            av128x = 7
        };

        Bit<5> XGYRO_CTEN{};
        Bit<4> YGYRO_CTEN{};
        Bit<3> ZGYRO_CTEN{};
        BitField<0, 2> GYRO_AVGCFG{};
    };

    struct XG_OFFS_USR : RegBase<addresses::XG_OFFS_USRH, UserBank::UB2, AccessT::rw, uint16_t>
    {
        BitField<0, 15> X_OFFS_USER{};
    };

    struct YG_OFFS_USR : RegBase<addresses::YG_OFFS_USRH, UserBank::UB2, AccessT::rw, uint16_t>
    {
        BitField<0, 15> Y_OFFS_USER{};
    };

    struct ZG_OFFS_USR : RegBase<addresses::ZG_OFFS_USRH, UserBank::UB2, AccessT::rw, uint16_t>
    {
        BitField<0, 15> Z_OFFS_USER{};
    };

    struct ODR_ALIGN_EN : RegBase<addresses::ODR_ALIGN_EN, UserBank::UB2, AccessT::rw>
    {
        Bit<0> ALIGN_EN{};
    };

    struct ACCEL_SMPLRT_DIV : RegBase<addresses::ACCEL_SMPLRT_DIV_1, UserBank::UB2, AccessT::rw, uint16_t>
    {
        BitField<0, 11> SMPLRT_DIV{};
    };

    struct ACCEL_INTEL_CTRL : RegBase<addresses::ACCEL_INTEL_CRT, UserBank::UB2, AccessT::rw>
    {
        Bit<1> ACCEL_INTEL_EN{};
        Bit<0> ACCEL_INTEL_MODE_INT{};
    };

    struct ACCEL_WOM_THR : RegBase<addresses::ACCEL_WOM_THR, UserBank::UB2, AccessT::rw>
    {
        BitField<0, 7> WOM_THRESHOLD{};
    };

    struct ACCEL_CONFIG : RegBase<addresses::ACCEL_CONFIG, UserBank::UB2, AccessT::rw>
    {
        enum class accel_full_scale_select : uint8_t
        {
            g2 = 0,
            g4 = 1,
            g8 = 2,
            g16 = 3
        };

        BitField<3, 5> ACCEL_CLPFCFG{};
        BitField<1, 2> ACCEL_FS_SEL{};
        Bit<0> ACCEL_FCHOICE{};
    };

    struct ACCEL_CONFIG_2 : RegBase<addresses::ACCEL_CONFIG_2, UserBank::UB2, AccessT::rw>
    {
        enum class sample_av_decimator
        {
            av1_4 = 0,
            av8 = 1,
            av16 = 2,
            av32 = 3
        };

        Bit<4> AX_ST_EN_REG{};
        Bit<3> AY_ST_EN_REG{};
        Bit<2> AZ_ST_EN_REG{};
        BitField<0, 1> DEC3_CFG{};
    };

    struct FSYNC_CONFIG : RegBase<addresses::FSYNC_CONFIG, UserBank::UB2, AccessT::rw>
    {
        enum class fsyc_data_smpl_pin : uint8_t
        {
            disable = 0,
            temp_out = 1,
            gyro_xout = 2,
            gyro_yout = 3,
            gyro_zout = 4,
            accel_xout = 5,
            accel_yout = 6,
            accel_zout = 7
        };

        Bit<7> DELAY_TIME_EN{};
        Bit<5> WOF_DEGLITCH_EN{};
        Bit<4> WOF_EDGE_INT{};
        BitField<0, 3> EXT_SYNC_SET{};
    };

    struct TEMP_CONFIG : RegBase<addresses::TEMP_CONFIG, UserBank::UB2, AccessT::rw>
    {
        BitField<0, 2> TEMP_DLPFCFG{};
    };

    struct MOD_CTRL_USR : RegBase<addresses::MOD_CTRL_USR, UserBank::UB2, AccessT::rw>
    {
        Bit<0> REG_LP_DMP_EN{};
    };

    /** User Bank 3 **/
    struct I2C_MST_ODR_CONFIG : RegBase<addresses::I2C_MST_ODR_CONFIG, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 3> ODR_CONFIG{};
    };

    struct I2C_MST_CTRL : RegBase<addresses::I2C_MST_CTRL, UserBank::UB3, AccessT::rw>
    {
        Bit<7> MULT_MST_EN{};
        Bit<4> I2C_MST_P_NSR{};
        BitField<0, 3> I2C_MST_CLK{};
    };

    struct I2C_MST_DELAY_CTRL : RegBase<addresses::I2C_MST_DELAY_CTRL, UserBank::UB3, AccessT::rw>
    {
        Bit<7> DELAY_ES_SHADOW{};
        Bit<4> I2C_SLV4_DELAY_EN{};
        Bit<3> I2C_SLV3_DELAY_EN{};
        Bit<2> I2C_SLV2_DELAY_EN{};
        Bit<1> I2C_SLV1_DELAY_EN{};
        Bit<0> I2C_SLV0_DELAY_EN{};
    };

    struct I2C_SLV0_ADDR : RegBase<addresses::I2C_SLV0_ADDR, UserBank::UB3, AccessT::rw>
    {
        Bit<7> I2C_SLV0_RNW{};
        BitField<0, 6> I2C_ID_0{};
    };

    struct I2C_SLV0_REG : RegBase<addresses::I2C_SLV0_REG, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> REG{};
    };

    struct I2C_SLV0_CTRL : RegBase<addresses::I2C_SLV0_CTRL, UserBank::UB3, AccessT::rw>
    {
        Bit<7> I2C_SLV0_EN{};
        Bit<6> I2C_SLV0_BYTE_SW{};
        Bit<5> I2C_SLV0_REG_DIS{};
        Bit<4> I2C_SLV0_GRP{};
        BitField<0, 3> I2C_SLV0_LENG{};
    };

    struct I2C_SLV0_DO : RegBase<addresses::I2C_SLV0_DO, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> DO{};
    };

    struct I2C_SLV1_ADDR : RegBase<addresses::I2C_SLV1_ADDR, UserBank::UB3, AccessT::rw>
    {
        Bit<7> I2C_SLV1_RNW{};
        BitField<0, 6> I2C_ID_1{};
    };

    struct I2C_SLV1_REG : RegBase<addresses::I2C_SLV1_REG, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> REG{};
    };

    struct I2C_SLV1_CTRL : RegBase<addresses::I2C_SLV1_CTRL, UserBank::UB3, AccessT::rw>
    {
        Bit<7> I2C_SLV1_EN{};
        Bit<6> I2C_SLV1_BYTE_SW{};
        Bit<5> I2C_SLV1_REG_DIS{};
        Bit<4> I2C_SLV1_GRP{};
        BitField<0, 3> I2C_SLV1_LENG{};
    };

    struct I2C_SLV1_DO : RegBase<addresses::I2C_SLV1_DO, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> DO{};
    };

    struct I2C_SLV2_ADDR : RegBase<addresses::I2C_SLV2_ADDR, UserBank::UB3, AccessT::rw>
    {
        Bit<7> I2C_SLV2_RNW{};
        BitField<0, 6> I2C_ID_2{};
    };

    struct I2C_SLV2_REG : RegBase<addresses::I2C_SLV2_REG, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> REG{};
    };

    struct I2C_SLV2_CTRL : RegBase<addresses::I2C_SLV2_CTRL, UserBank::UB3, AccessT::rw>
    {
        Bit<7> I2C_SLV2_EN{};
        Bit<6> I2C_SLV2_BYTE_SW{};
        Bit<5> I2C_SLV2_REG_DIS{};
        Bit<4> I2C_SLV2_GRP{};
        BitField<0, 3> I2C_SLV2_LENG{};
    };

    struct I2C_SLV2_DO : RegBase<addresses::I2C_SLV2_DO, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> DO{};
    };

    struct I2C_SLV3_ADDR : RegBase<addresses::I2C_SLV3_ADDR, UserBank::UB3, AccessT::rw>
    {
        Bit<7> I2C_SLV3_RNW{};
        BitField<0, 6> I2C_ID_3{};
    };

    struct I2C_SLV3_REG : RegBase<addresses::I2C_SLV3_REG, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> REG{};
    };

    struct I2C_SLV3_CTRL : RegBase<addresses::I2C_SLV3_CTRL, UserBank::UB3, AccessT::rw>
    {
        Bit<7> I2C_SLV3_EN{};
        Bit<6> I2C_SLV3_BYTE_SW{};
        Bit<5> I2C_SLV3_REG_DIS{};
        Bit<4> I2C_SLV3_GRP{};
        BitField<0, 3> I2C_SLV3_LENG{};
    };

    struct I2C_SLV3_DO : RegBase<addresses::I2C_SLV3_DO, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> DO{};
    };

    struct I2C_SLV4_ADDR : RegBase<addresses::I2C_SLV4_ADDR, UserBank::UB3, AccessT::rw>
    {
        Bit<7> I2C_SLV4_RNW{};
        BitField<0, 6> I2C_ID_4{};
    };

    struct I2C_SLV4_REG : RegBase<addresses::I2C_SLV4_REG, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> REG{};
    };

    struct I2C_SLV4_CTRL : RegBase<addresses::I2C_SLV4_CTRL, UserBank::UB3, AccessT::rw>
    {
        Bit<7> I2C_SLV4_EN{};
        Bit<6> I2C_SLV4_BYTE_SW{};
        Bit<5> I2C_SLV4_REG_DIS{};
        Bit<4> I2C_SLV4_GRP{};
        BitField<0, 3> I2C_SLV4_LENG{};
    };

    struct I2C_SLV4_DO : RegBase<addresses::I2C_SLV4_DO, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> DO{};
    };

    struct I2C_SLV4_DI : RegBase<addresses::I2C_SLV4_DI, UserBank::UB3, AccessT::rw>
    {
        BitField<0, 7> DI{};
    };
} // namespace icm20948::registers
