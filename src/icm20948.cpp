#include "i2c.hpp"
#include "userbank0.hpp"
#include <array>
#include <cstdint>
#include <hardware/i2c.h>
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
        output.y = array_to_int16(input.subspan(3, 2));
        output.z = array_to_int16(input.subspan(5, 2));
    }
} // namespace

namespace icm20948
{
    ICM20948::ICM20948(i2c_inst_t* rp_i2c)
    {
        i2c_instance = rp_i2c;
        i2c_instance.write(registers::PWR_MGMT_1{}); // init with 0 to wake from sleep
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
        raw_to_vec(data_buf_span.subspan(5, 6), raw_gyro);
        auto raw_temp = array_to_int16(data_buf_span.subspan(11, 2));
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

    auto ICM20948::calc_temp_from_raw(int16_t raw) -> float
    {
        return ((raw - ROOM_TEMP_OFFS) / TEMP_SENS) + ROOM_TEMP_OFFS;
    }
} // namespace icm20948
