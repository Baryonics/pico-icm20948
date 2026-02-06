#pragma once
#include "register_base.hpp"
#include <cstdint>

namespace icm20948::registers::addresses
{

    inline constexpr uint8_t GYRO_SMPLRT_DIV = 0x00;
    inline constexpr uint8_t GYRO_CONFIG_1 = 0x01;
    inline constexpr uint8_t GYRO_CONFIG_2 = 0x02;
    inline constexpr uint8_t XG_OFFS_USRH = 0x03;
    inline constexpr uint8_t XG_OFFS_USRL = 0x04;
    inline constexpr uint8_t YG_OFFS_USRH = 0x05;
    inline constexpr uint8_t YG_OFFS_USRL = 0x06;
    inline constexpr uint8_t ZG_OFFS_USRH = 0x07;
    inline constexpr uint8_t ZG_OFFS_USRL = 0x08;
    inline constexpr uint8_t ODR_ALIGN_EN = 0x09;
    inline constexpr uint8_t ACCEL_SMPLRT_DIV_1 = 0x10;
    inline constexpr uint8_t ACCEL_SMPLRT_DIV_2 = 0x11;
    inline constexpr uint8_t ACCEL_INTEL_CRT = 0x12;
    inline constexpr uint8_t ACCEL_WOM_THR = 0x13;
    inline constexpr uint8_t ACCEL_CONFIG = 0x14;
    inline constexpr uint8_t ACCEL_CONFIG_2 = 0x15;
    inline constexpr uint8_t FSYNC_CONFIG = 0x52;
    inline constexpr uint8_t TEMP_CONFIG = 0x53;
    inline constexpr uint8_t MOD_CTRL_USR = 0x54;
} // namespace icm20948::registers::addresses

namespace icm20948::registers
{

    struct GYRO_SMPLRT_DIV : RegBase<addresses::GYRO_SMPLRT_DIV, UserBank::UB2, AccessT::rw>
    {
        static constexpr BitField<0, 7> SMPTLRT_DIV{};
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

        static constexpr BitField<3, 5> GYRO_DLPFCFG{};
        static constexpr BitField<1, 2> GYRO_FS_SEL{};
        static constexpr Bit<0> GYRO_FCHOICE{};
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

        static constexpr Bit<5> XGYRO_CTEN{};
        static constexpr Bit<4> YGYRO_CTEN{};
        static constexpr Bit<3> ZGYRO_CTEN{};
        static constexpr BitField<0, 2> GYRO_AVGCFG{};
    };

    struct XG_OFFS_USR : RegBase<addresses::XG_OFFS_USRH, UserBank::UB2, AccessT::rw, uint16_t>
    {
        static constexpr BitField<0, 15> X_OFFS_USER{};
    };

    struct YG_OFFS_USR : RegBase<addresses::YG_OFFS_USRH, UserBank::UB2, AccessT::rw, uint16_t>
    {
        static constexpr BitField<0, 15> Y_OFFS_USER{};
    };

    struct ZG_OFFS_USR : RegBase<addresses::ZG_OFFS_USRH, UserBank::UB2, AccessT::rw, uint16_t>
    {
        static constexpr BitField<0, 15> Z_OFFS_USER{};
    };

    struct ODR_ALIGN_EN : RegBase<addresses::ODR_ALIGN_EN, UserBank::UB2, AccessT::rw>
    {
        static constexpr Bit<0> ALIGN_EN{};
    };

    struct ACCEL_SMPLRT_DIV : RegBase<addresses::ACCEL_SMPLRT_DIV_1, UserBank::UB2, AccessT::rw, uint16_t>
    {
        static constexpr BitField<0, 11> SMPLRT_DIV{};
    };

    struct ACCEL_INTEL_CTRL : RegBase<addresses::ACCEL_INTEL_CRT, UserBank::UB2, AccessT::rw>
    {
        static constexpr Bit<1> ACCEL_INTEL_EN{};
        static constexpr Bit<0> ACCEL_INTEL_MODE_INT{};
    };

    struct ACCEL_WOM_THR : RegBase<addresses::ACCEL_WOM_THR, UserBank::UB2, AccessT::rw>
    {
        static constexpr BitField<0, 7> WOM_THRESHOLD{};
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

        static constexpr BitField<3, 5> ACCEL_CLPFCFG{};
        static constexpr BitField<1, 2> ACCEL_FS_SEL{};
        static constexpr Bit<0> ACCEL_FCHOICE{};
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

        static constexpr Bit<4> AX_ST_EN_REG{};
        static constexpr Bit<3> AY_ST_EN_REG{};
        static constexpr Bit<2> AZ_ST_EN_REG{};
        static constexpr BitField<0, 1> DEC3_CFG{};
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

        static constexpr Bit<7> DELAY_TIME_EN{};
        static constexpr Bit<5> WOF_DEGLITCH_EN{};
        static constexpr Bit<4> WOF_EDGE_INT{};
        static constexpr BitField<0, 3> EXT_SYNC_SET{};
    };

    struct TEMP_CONFIG : RegBase<addresses::TEMP_CONFIG, UserBank::UB2, AccessT::rw>
    {
        static constexpr BitField<0, 2> TEMP_DLPFCFG{};
    };

    struct MOD_CTRL_USR : RegBase<addresses::MOD_CTRL_USR, UserBank::UB2, AccessT::rw>
    {
        static constexpr Bit<0> REG_LP_DMP_EN{};
    };
} // namespace icm20948::registers
