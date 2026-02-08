#pragma once

#include "i2c.hpp"
#include "registers/register_base.hpp"
#include "registers/userbank2.hpp"
#include "userbank0.hpp"
#include "userbank1.hpp"
#include "userbank3.hpp"
#include <bit>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <hardware/i2c.h>

/** BIG TODOS: Magic Numbers, expected **/
namespace icm20948
{
    template <typename T>
        requires(std::integral<T> || std::floating_point<T>)
    struct Vec3
    {
        Vec3() = default;
        Vec3(T x, T y, T z)
            : x(x)
            , y(y)
            , z(z)
        {
        }

        template <typename U>
            requires(std::integral<U> || std::floating_point<U>)
        Vec3(const Vec3<U>& other)
            : x(static_cast<T>(other.x))
            , y(static_cast<T>(other.y))
            , z(static_cast<T>(other.z))
        {
        }

        Vec3<float> operator/(float const f) const
        {
            return Vec3<float>{ static_cast<float>(x) / f, static_cast<float>(y) / f, static_cast<float>(z) / f };
        }

        Vec3<T>& operator=(Vec3<T> const& v)
        {
            x = v.x;
            y = v.y;
            z = v.z;
            return *this;
        }

        T x, y, z;
    };

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
        static constexpr size_t SENSOR_DATA_LEN = 20;
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

        float calc_temp_from_raw(int16_t raw_temp);

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
        registers::I2C_SLV0_DO i2c_slv0_do_{};

      public:
        ICM20948(i2c_inst_t* rp_i2c);
        void update();
        void apply();

        void set_accel_range(AccelRange range);
        Vec3<float> get_accel();

        void set_gyro_range(GyroRange range);
        Vec3<float> get_gyro();

        Vec3<float> get_mag();

        uint8_t who_am_i();

        template <typename ValType>
            requires registers::reg_type<ValType>
        int16_t get_value()
        {
            auto val_reg = i2c_instance.read<ValType>();
            return static_cast<int16_t>(std::byteswap(val_reg.bits));
        }
    };
} // namespace icm20948
