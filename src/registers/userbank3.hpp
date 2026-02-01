#pragma once
#include "register_base.hpp"
#include <cstdint>

namespace icm20948::registers::addresses
{

    inline constexpr uint8_t I2C_MST_ODR_CONFIG = 0x00;
    inline constexpr uint8_t I2C_MST_CTRL = 0x01;
    inline constexpr uint8_t I2C_MST_DELAY_CTRL = 0x02;
    inline constexpr uint8_t I2C_SLV0_ADDR = 0x03;
    inline constexpr uint8_t I2C_SLV0_REG = 0x04;
    inline constexpr uint8_t I2C_SLV0_CTRL = 0x05;
    inline constexpr uint8_t I2C_SLV0_DO = 0x06;
    inline constexpr uint8_t I2C_SLV1_ADDR = 0x07;
    inline constexpr uint8_t I2C_SLV1_REG = 0x08;
    inline constexpr uint8_t I2C_SLV1_CTRL = 0x09;
    inline constexpr uint8_t I2C_SLV1_DO = 0x0A;
    inline constexpr uint8_t I2C_SLV2_ADDR = 0x0B;
    inline constexpr uint8_t I2C_SLV2_REG = 0x0C;
    inline constexpr uint8_t I2C_SLV2_CTRL = 0x0D;
    inline constexpr uint8_t I2C_SLV2_DO = 0x0E;
    inline constexpr uint8_t I2C_SLV3_ADDR = 0x0F;
    inline constexpr uint8_t I2C_SLV3_REG = 0x10;
    inline constexpr uint8_t I2C_SLV3_CTRL = 0x11;
    inline constexpr uint8_t I2C_SLV3_DO = 0x12;
    inline constexpr uint8_t I2C_SLV4_ADDR = 0x13;
    inline constexpr uint8_t I2C_SLV4_REG = 0x14;
    inline constexpr uint8_t I2C_SLV4_CTRL = 0x15;
    inline constexpr uint8_t I2C_SLV4_DO = 0x16;
    inline constexpr uint8_t I2C_SLV4_DI = 0x17;
} // namespace icm20948::registers::addresses

namespace icm20948::registers
{

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
