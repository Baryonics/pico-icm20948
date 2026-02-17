#include "config_enums.hpp"
#include "errors.hpp"
#include "i2c.hpp"
#include "pico/stdlib.h"
#include "reg_magnetometer.hpp"
#include "registers/userbank2.hpp"
#include "userbank0.hpp"
#include "userbank3.hpp"
#include <array>
#include <concepts>
#include <cstdint>
#include <expected>
#include <hardware/i2c.h>
#include <hardware/timer.h>
#include <icm20948/icm20948.hpp>
#include <pico/error.h>
#include <pico/types.h>
#include <span>

namespace
{
    using namespace icm20948;
    auto array_to_int16(std::span<uint8_t> input, bool no_swap = false) -> int16_t
    {
        auto int16_buf = int16_t{};
        memcpy(&int16_buf, input.data(), 2);
        if (no_swap)
        {
            return int16_buf;
        }
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
        : i2c_instance(rp_i2c)
    {
    }

    /** public **/
    ErrorT<void> ICM20948::update()
    {
        auto raw_data_buffer = std::array<uint8_t, SENSOR_DATA_LEN>{};
        auto data_buf_span = std::span(raw_data_buffer);
        if (auto r = i2c_instance.block_read<registers::ACCEL_XOUT>(std::span(raw_data_buffer)); !r)
        {
            return std::unexpected(r.error());
        }
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

        return {};
    };

    auto ICM20948::init() -> ErrorT<void>
    {

        i2c_instance.write(registers::PWR_MGMT_1{});
        set_accel_range(AccelRange::g16).set_gyro_range(GyroRange::dps2000).enable_mag().apply();
        mag_cntrl3_.set_bit(registers::mag::CNTRL3::SRST, false);
        i2c_slv4_reg_.set_field(registers::I2C_SLV4_REG::REG, mag_cntrl3_.address);
        i2c_slv4_do_.set_field(registers::I2C_SLV4_DO::DO, mag_cntrl3_.bits);
        i2c_instance.write(i2c_slv4_reg_, i2c_slv4_do_);
        // set_accel_range(AccelRange::g16).set_gyro_range(GyroRange::dps2000).apply();
    }

    void ICM20948::apply()
    {
        auto WAT = i2c_instance.write(user_ctrl_,
                                      pwr_mgmt_1_,
                                      accel_config_,
                                      gyro_config_1_,
                                      i2c_mst_ctrl_,

                                      i2c_slv0_addr,
                                      i2c_slv0_reg_,
                                      i2c_slv0_ctrl_,

                                      i2c_slv4_addr_,
                                      i2c_slv4_reg_,
                                      i2c_slv4_do_,
                                      i2c_slv4_ctrl_);
    }

    auto ICM20948::sleep(bool is_sleep) -> ErrorT<void>
    {
        pwr_mgmt_1_.set_bit(registers::PWR_MGMT_1::SLEEP, is_sleep);
        return {};
    }

    auto ICM20948::enable_mag() -> ErrorT<void>
    {
        user_ctrl_.set_bit(registers::USER_CTRL::I2C_MST_EN, true);

        mag_cntrl2_.set_field(registers::mag::CNTRL2::MODE,
                              registers::mag::CNTRL2::mode_select::continuous_mesaurement4);

        i2c_mst_ctrl_.set_field(registers::I2C_MST_CTRL::I2C_MST_CLK, 7);

        i2c_slv0_ctrl_.set_bit(registers::I2C_SLV0_CTRL::I2C_SLV0_EN, true)
            .set_field(registers::I2C_SLV0_CTRL::I2C_SLV0_LENG, 8);
        i2c_slv0_addr.set_field(registers::I2C_SLV0_ADDR::I2C_ID_0, 0x0C)
            .set_bit(registers::I2C_SLV0_ADDR::I2C_SLV0_RNW, true);
        i2c_slv0_reg_.set_field(registers::I2C_SLV0_REG::REG, registers::mag::HX::address);

        i2c_slv4_ctrl_.set_bit(registers::I2C_SLV4_CTRL::I2C_SLV4_EN, true);
        i2c_slv4_addr_.set_field(registers::I2C_SLV4_ADDR::I2C_ID_4, 0xC);
        i2c_slv4_reg_.set_field(registers::I2C_SLV4_REG::REG, registers::mag::CNTRL2::address);
        i2c_slv4_do_.set_field(registers::I2C_SLV4_DI::DI, mag_cntrl2_.bits);
        return {};
    }

    auto ICM20948::set_accel_range(AccelRange range) -> ErrorT<void>
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
        return {};
    }

    auto ICM20948::set_gyro_range(GyroRange range) -> ErrorT<void>
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
        return {};
    }

    /** Sensor Getters **/
    auto ICM20948::get_accel() -> Vec3<float> { return acc_val_; }

    auto ICM20948::get_gyro() -> Vec3<float> { return gyro_val_; }

    auto ICM20948::get_mag() -> Vec3<int> { return mag_val_; };

    auto ICM20948::who_am_i() -> ErrorT<uint8_t>
    {
        auto r = i2c_instance.read<registers::WHO_AM_I>();
        if (!r)
        {
            return std::unexpected(r.error());
        }
        return r.value().bits;
    }

    /** private **/
    auto ICM20948::enable_slave(const uint8_t address, const SlaveMode rw) -> ErrorT<void> {}

    /** helpers **/
    auto ICM20948::calc_temp_from_raw(int16_t raw) -> float
    {
        return ((static_cast<int>(raw) - ROOM_TEMP_OFFS) / TEMP_SENS) + ROOM_TEMP_OFFS;
    }

} // namespace icm20948
