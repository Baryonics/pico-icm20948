#pragma once

#include "../src/core/registers.hpp"
#include "core/i2c.hpp"
#include <cstdint>
#include <hardware/i2c.h>

namespace icm20948
{
    struct ICM20948
    {
        ICM20948(i2c_inst_t* i2c_instance);

        I2C i2c_instance_;
        void write();

        uint8_t test_read();
        uint8_t read_int_status();
        void set_int();

        /** User Bank 0 **/
        registers::WHO_AM_I who_am_i{};
        registers::USER_CTRL usr_ctrl{};
        registers::LP_CONFIG lp_config{};
        registers::PWR_MGMT_1 pwr_mgmt_1{};
        registers::PWR_MGMT_2 pwr_mgmt_2{};
        registers::INT_PIN_CFG int_pin_cfg{};
        registers::INT_ENABLE int_enable{};
        registers::INT_ENABLE_1 int_enable_1{};
        registers::INT_ENABLE_2 int_enable_2{};
        registers::INT_ENABLE_3 int_enable_3{};
        registers::I2C_MST_STATUS i2c_mst_status{};
        registers::INT_STATUS int_status{};
        registers::INT_STATUS_1 int_status_1{};
        registers::INT_STATUS_2 int_status_2{};
        registers::INT_STATUS_3 int_status_3{};
        registers::DELAY_TIME delay_timeh{};

        registers::ACCEL_XOUT accel_xout{};
        registers::ACCEL_YOUT accel_yout{};
        registers::ACCEL_ZOUT accel_zout{};

        registers::GYRO_XOUT gyro_xout{};
        registers::GYRO_YOUT gyro_yout{};
        registers::GYRO_ZOUT gyro_zout{};

        registers::TEMP_OUT temp_out_h{};

        registers::EXT_SLV_SENS_DATA_00 ext_slv_sens_data_00{};
        registers::EXT_SLV_SENS_DATA_01 ext_slv_sens_data_01{};
        registers::EXT_SLV_SENS_DATA_02 ext_slv_sens_data_02{};
        registers::EXT_SLV_SENS_DATA_03 ext_slv_sens_data_03{};
        registers::EXT_SLV_SENS_DATA_04 ext_slv_sens_data_04{};
        registers::EXT_SLV_SENS_DATA_05 ext_slv_sens_data_05{};
        registers::EXT_SLV_SENS_DATA_06 ext_slv_sens_data_06{};
        registers::EXT_SLV_SENS_DATA_07 ext_slv_sens_data_07{};
        registers::EXT_SLV_SENS_DATA_08 ext_slv_sens_data_08{};
        registers::EXT_SLV_SENS_DATA_09 ext_slv_sens_data_09{};
        registers::EXT_SLV_SENS_DATA_10 ext_slv_sens_data_10{};
        registers::EXT_SLV_SENS_DATA_11 ext_slv_sens_data_11{};
        registers::EXT_SLV_SENS_DATA_12 ext_slv_sens_data_12{};
        // registers::EXT_SLV_SENS_DATA_13 ext_slv_sens_data_13{};
        // registers::EXT_SLV_SENS_DATA_14 ext_slv_sens_data_14{};
        // registers::EXT_SLV_SENS_DATA_15 ext_slv_sens_data_15{};
        // registers::EXT_SLV_SENS_DATA_16 ext_slv_sens_data_16{};
        // registers::EXT_SLV_SENS_DATA_17 ext_slv_sens_data_17{};
        // registers::EXT_SLV_SENS_DATA_18 ext_slv_sens_data_18{};
        // registers::EXT_SLV_SENS_DATA_19 ext_slv_sens_data_19{};
        // registers::EXT_SLV_SENS_DATA_20 ext_slv_sens_data_20{};
        // registers::EXT_SLV_SENS_DATA_21 ext_slv_sens_data_21{};
        // registers::EXT_SLV_SENS_DATA_22 ext_slv_sens_data_22{};
        // registers::EXT_SLV_SENS_DATA_23 ext_slv_sens_data_23{};

        registers::FIFO_EN_1 fifo_en_1{};
        registers::FIFO_EN_2 fifo_en_2{};
        registers::FIFO_RST fifo_rst{};
        registers::FIFO_MODE fifo_mode{};
        registers::FIFO_COUNT fifo_count{};
        registers::FIFO_R_W fifo_r_w{};
        registers::DATA_RDY_STATUS data_rdy_status{};
        registers::FIFO_CFG fifo_cfg{};
        registers::REG_BANK_SEL reg_bank_sel{};

        /** User Bank 1 **/
        registers::SELF_TEST_X_GYRO self_test_x_gyro{};
        registers::SELF_TEST_Y_GYRO self_test_y_gyro{};
        registers::SELF_TEST_Z_GYRO self_test_z_gyro{};
        registers::SELF_TEST_X_ACCEL self_test_x_accel{};
        registers::SELF_TEST_Y_ACCEL self_test_y_accel{};
        registers::SELF_TEST_Z_ACCEL self_test_z_accel{};
        registers::XA_OFFS xa_offs{};
        registers::YA_OFFS ya_offs{};
        registers::ZA_OFFS za_offs{};
        registers::TIMEBASE_CORRECTION_PLL timebase_correction_pll{};

        /** User Bank 2 **/
        registers::GYRO_SMPLRT_DIV gyro_smplrt_div{};
        registers::GYRO_CONFIG_1 gyro_config_1{};
        registers::GYRO_CONFIG_2 gyro_config_2{};
        registers::XG_OFFS_USR xg_offs_usr{};
        registers::YG_OFFS_USR yg_offs_usr{};
        registers::ZG_OFFS_USR zg_offs_usr{};
        registers::ODR_ALIGN_EN odr_align_en{};
        registers::ACCEL_SMPLRT_DIV accel_smplrt_div{};
        registers::ACCEL_INTEL_CTRL accel_intel_crt{};
        registers::ACCEL_WOM_THR accel_wom_thr{};
        registers::ACCEL_CONFIG accel_config{};
        registers::ACCEL_CONFIG_2 accel_config_2{};
        registers::FSYNC_CONFIG fsync_config{};
        registers::TEMP_CONFIG temp_config{};
        registers::MOD_CTRL_USR mod_ctrl_usr{};

        /** User Bank 3 **/
        registers::I2C_MST_ODR_CONFIG i2c_mst_odr_config{};
        registers::I2C_MST_CTRL i2c_mst_ctrl{};
        registers::I2C_MST_DELAY_CTRL i2c_mst_delay_ctrl{};
        registers::I2C_SLV0_ADDR i2c_slv0_addr{};
        registers::I2C_SLV0_REG i2c_slv0_reg{};
        registers::I2C_SLV0_CTRL i2c_slv0_ctrl{};
        registers::I2C_SLV0_DO i2c_slv0_do{};
        registers::I2C_SLV1_ADDR i2c_slv1_addr{};
        registers::I2C_SLV1_REG i2c_slv1_reg{};
        registers::I2C_SLV1_CTRL i2c_slv1_ctrl{};
        registers::I2C_SLV1_DO i2c_slv1_do{};
        registers::I2C_SLV2_ADDR i2c_slv2_addr{};
        registers::I2C_SLV2_REG i2c_slv2_reg{};
        registers::I2C_SLV2_CTRL i2c_slv2_ctrl{};
        registers::I2C_SLV2_DO i2c_slv2_do{};
        registers::I2C_SLV3_ADDR i2c_slv3_addr{};
        registers::I2C_SLV3_REG i2c_slv3_reg{};
        registers::I2C_SLV3_CTRL i2c_slv3_ctrl{};
        registers::I2C_SLV3_DO i2c_slv3_do{};
        registers::I2C_SLV4_ADDR i2c_slv4_addr{};
        registers::I2C_SLV4_REG i2c_slv4_reg{};
        registers::I2C_SLV4_CTRL i2c_slv4_ctrl{};
        registers::I2C_SLV4_DO i2c_slv4_do{};
        registers::I2C_SLV4_DI i2c_slv4_di{};
    };
} // namespace icm20948
