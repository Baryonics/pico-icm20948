#pragma once

#include "i2c.hpp"
#include "registers/register_base.hpp"
#include "userbank2.hpp"
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

        registers::ACCEL_CONFIG accel_config_{};
        registers::GYRO_CONFIG_1 gyro_config_1_{};

      public:
        ICM20948(i2c_inst_t* rp_i2c);
        void update();

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
