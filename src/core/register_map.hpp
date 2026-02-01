#pragma once

#include <cstdint>

namespace icm20948::registers::addresses
{

    /** User Bank 0 **/
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

    /** User Bank 1 **/
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

    /** User Bank 2 **/
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

    /** User Bank 3 **/
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
