#include "i2c.hpp"
#include "pico/stdlib.h"
#include "registers/userbank2.hpp"
#include "userbank0.hpp"
#include <array>
#include <cstdint>
#include <hardware/i2c.h>
#include <hardware/timer.h>
#include <icm20948/icm20948.hpp>
#include <span>

namespace
{
    using namespace icm20948;
    auto array_to_int16(std::span<uint8_t> input) -> int16_t
    {
        auto int16_buf = int16_t{};
        memcpy(&int16_buf, input.data(), 2);
        return std::byteswap(int16_buf);
    }

    void raw_to_vec(std::span<uint8_t> input, Vec3<int16_t>& output)
    {
        output.x = array_to_int16(input.subspan(0, 2));
        output.y = array_to_int16(input.subspan(2, 2));
        output.z = array_to_int16(input.subspan(4, 2));
    }
} // namespace

namespace icm20948
{
    ICM20948::ICM20948(i2c_inst_t* rp_i2c)
    {
        i2c_instance = rp_i2c;
        i2c_instance.write(registers::PWR_MGMT_1{}); // init with 0 to wake from sleep
        set_accel_range(AccelRange::g16);
        set_gyro_range(GyroRange::dps2000);
    }

    void ICM20948::update()
    {
        auto raw_data_buffer = std::array<uint8_t, SENSOR_DATA_LEN>{};
        auto data_buf_span = std::span(raw_data_buffer);
        i2c_instance.block_read<registers::ACCEL_XOUT>(std::span(raw_data_buffer));
        auto raw_accel = Vec3<int16_t>{};
        auto raw_gyro = Vec3<int16_t>{};
        auto raw_mag = Vec3<int16_t>{};

        raw_to_vec(data_buf_span.subspan(0, 6), raw_accel);
        raw_to_vec(data_buf_span.subspan(6, 6), raw_gyro);
        auto raw_temp = array_to_int16(data_buf_span.subspan(12, 2));
        raw_to_vec(data_buf_span.subspan(14, 6), raw_mag);

        acc_val_ = raw_accel / acc_scale_;
        gyro_val_ = raw_gyro / gyro_scale_;
        temp_val_ = calc_temp_from_raw(raw_temp);
        mag_val_ = raw_mag;
    };

    auto ICM20948::who_am_i() -> uint8_t
    {
        auto who_am_i = registers::WHO_AM_I{};
        who_am_i = i2c_instance.read<registers::WHO_AM_I>();
        return who_am_i.bits;
    }

    void ICM20948::set_accel_range(AccelRange range)
    {
        using reg = registers::ACCEL_CONFIG;

        auto fs = reg::accel_full_scale_select{};

        switch (range)
        {
            case AccelRange::g2:
                fs = reg::accel_full_scale_select::g2;
                acc_scale_ = 16384.0f;
                break;

            case AccelRange::g4:
                fs = reg::accel_full_scale_select::g4;
                acc_scale_ = 8192.0f;
                break;

            case AccelRange::g8:
                fs = reg::accel_full_scale_select::g8;
                acc_scale_ = 4096.0f;
                break;

            case AccelRange::g16:
                fs = reg::accel_full_scale_select::g16;
                acc_scale_ = 2048.0;
                break;
        }

        accel_config_.set_field(reg::ACCEL_FS_SEL, fs);
    }

    auto ICM20948::get_accel() -> Vec3<float> { return acc_val_; }

    void ICM20948::set_gyro_range(GyroRange range)
    {
        using reg = registers::GYRO_CONFIG_1;

        auto fs = reg::full_scale_select{};

        switch (range)
        {
            case GyroRange::dps250:
                fs = reg::full_scale_select::dps250;
                gyro_scale_ = 131.0f;
                break;

            case GyroRange::dps500:
                fs = reg::full_scale_select::dps500;
                gyro_scale_ = 65.5f;
                break;

            case GyroRange::dps1000:
                fs = reg::full_scale_select::dps1000;
                gyro_scale_ = 32.8f;
                break;

            case GyroRange::dps2000:
                fs = reg::full_scale_select::dps2000;
                gyro_scale_ = 16.4f;
                break;
        }

        gyro_config_1_.set_field(reg::GYRO_FS_SEL, fs);
    }
    auto ICM20948::get_gyro() -> Vec3<float> { return gyro_val_; }
    auto ICM20948::calc_temp_from_raw(int16_t raw) -> float
    {
        return ((static_cast<int>(raw) - ROOM_TEMP_OFFS) / TEMP_SENS) + ROOM_TEMP_OFFS;
    }
} // namespace icm20948
