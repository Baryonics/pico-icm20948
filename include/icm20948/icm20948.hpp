#pragma once

#include "errors.hpp"
#include "i2c.hpp"
#include "registers/reg_magnetometer.hpp"
#include "registers/register_base.hpp"
#include "registers/userbank0.hpp"
#include "registers/userbank1.hpp"
#include "registers/userbank2.hpp"
#include "registers/userbank3.hpp"
#include "vec3.hpp"
#include <bit>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <hardware/i2c.h>

/** BIG TODOS: Magic Numbers, expected **/
namespace icm20948
{

    enum class AccelRange : uint8_t
    {
        g2,
        g4,
        g8,
        g16
    };

    enum class GyroRange : uint8_t
    {
        dps250,
        dps500,
        dps1000,
        dps2000
    };

    class ICM20948
    {
        static constexpr size_t SENSOR_DATA_LEN = 22;
        static constexpr float TEMP_SENS = 333.87;
        static constexpr int ROOM_TEMP_OFFS = 21;

        I2C i2c_instance;
        Vec3<float> acc_val_{};
        Vec3<float> gyro_val_{};
        Vec3<int> mag_val_{};
        float temp_val_{};

        float acc_scale_{};
        float gyro_scale_{};
        uint8_t temp_scale_{};

        /** helpers **/
        float calc_temp_from_raw(int16_t raw_temp);
        ICM20948& enable_mag();

        template <typename ValType>
            requires registers::reg_type<ValType>
        int16_t get_value()
        {
            auto val_reg = i2c_instance.read<ValType>();
            return static_cast<int16_t>(std::byteswap(val_reg.bits));
        }

        /** Config Registers **/
        registers::USER_CTRL user_ctrl_{};
        registers::LP_CONFIG lp_config_{};
        registers::PWR_MGMT_1 pwr_mgmt_1_{};
        registers::PWR_MGMT_2 pwr_mgmt_2_{};
        registers::INT_PIN_CFG int_pin_cfg_{};
        registers::INT_ENABLE int_enable_{};
        registers::INT_ENABLE_1 int_enable_1_{};
        registers::INT_ENABLE_2 int_enable_2_{};
        registers::INT_ENABLE_3 int_enable_3_{};
        registers::FIFO_EN_1 fifo_en_1_{};
        registers::FIFO_EN_2 fifo_en_2_{};
        registers::FIFO_RST fifo_rst_{};
        registers::FIFO_MODE fifo_mode_{};
        registers::FIFO_R_W fifo_r_w_{};
        registers::FIFO_CFG fifo_cfg_{};

        registers::SELF_TEST_X_GYRO self_test_x_gyro_{};
        registers::SELF_TEST_Y_GYRO self_test_y_gyro_{};
        registers::SELF_TEST_Z_GYRO self_test_z_gyro_{};
        registers::SELF_TEST_X_ACCEL self_test_x_accel_{};
        registers::SELF_TEST_Y_ACCEL self_test_y_accel_{};
        registers::SELF_TEST_Z_ACCEL self_test_z_accel_{};

        registers::XA_OFFS xa_offs_{};
        registers::YA_OFFS ya_offs_{};
        registers::ZA_OFFS za_offs{};

        registers::TIMEBASE_CORRECTION_PLL timebase_correction_pll_{};

        registers::GYRO_SMPLRT_DIV gtro_smplrt_div_{};
        registers::GYRO_CONFIG_1 gyro_config_1_{};
        registers::GYRO_CONFIG_2 gyro_config_2_{};

        registers::XG_OFFS_USR xg_ofss_usr_{};
        registers::YG_OFFS_USR yg_offs_usr_{};
        registers::ZG_OFFS_USR zg_offs_usr_{};

        registers::ODR_ALIGN_EN odr_align_en_{};
        registers::ACCEL_SMPLRT_DIV accel_smplrt_div_{};
        registers::ACCEL_INTEL_CTRL accel_intel_ctrl_{};
        registers::ACCEL_WOM_THR accel_wom_thr_{};
        registers::ACCEL_CONFIG accel_config_{};
        registers::ACCEL_CONFIG_2 accel_confg_2_{};

        registers::FSYNC_CONFIG fsync_config_{};
        registers::TEMP_CONFIG temp_config_{};
        registers::MOD_CTRL_USR mod_ctrl_user_{};

        registers::I2C_MST_STATUS i2c_mst_status_{};
        registers::I2C_MST_CTRL i2c_mst_ctrl_{};

        registers::I2C_SLV0_ADDR i2c_slv0_addr{};
        registers::I2C_SLV0_REG i2c_slv0_reg_{};
        registers::I2C_MST_CTRL i2c_slv0_ctrl_{};
        registers::I2C_SLV0_DO i2c_slv0_do_{};

        registers::I2C_SLV4_ADDR i2c_slv4_addr_{};
        registers::I2C_SLV4_REG i2c_slv4_reg_{};
        registers::I2C_MST_CTRL i2c_slv4_ctrl_{};
        registers::I2C_SLV4_DO i2c_slv4_do_{};

        /** Magnetometer Config **/
        registers::mag::CNTRL2 mag_cntrl2_{};
        registers::mag::CNTRL3 mag_cntrl3_{};

      public:
        ICM20948(i2c_inst_t* rp_i2c);
        void update();

        /** config methods **/
        void apply();
        ICM20948& sleep(bool is_sleep);

        ICM20948& set_accel_range(AccelRange range);
        ICM20948& set_gyro_range(GyroRange range);

        /** sensor getters **/
        Vec3<float> get_gyro();
        Vec3<float> get_accel();
        Vec3<int> get_mag();

        uint8_t who_am_i();
    };
} // namespace icm20948
