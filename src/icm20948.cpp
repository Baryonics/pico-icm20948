#include "config_enums.hpp"
#include "errors.hpp"
#include "i2c.hpp"
#include "pico/stdlib.h"
#include "pico/time.h"
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
#include <ranges>
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
        TRY(i2c_instance.write(registers::PWR_MGMT_1{}));
        TRY(set_accel_range(AccelRange::g16));
        TRY(set_gyro_range(GyroRange::dps2000));
        TRY(enable_mag());
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

    auto ICM20948::enable_mag() -> ErrorT<void> // Das machen wir so!
    {
        mag_cntrl2_.set_field(registers::mag::CNTRL2::MODE,
                              registers::mag::CNTRL2::mode_select::continuous_mesaurement4);

        // Prepare I2C Master
        user_ctrl_.set_bit(registers::USER_CTRL::I2C_MST_EN, true);       // Enable Master
        i2c_mst_ctrl_.set_field(registers::I2C_MST_CTRL::I2C_MST_CLK, 7); // Set I2C clock

        // Prepare SLV4 for writing
        i2c_slv4_ctrl_.set_bit(registers::I2C_SLV4_CTRL::I2C_SLV4_EN, true); // enable SLV4
        i2c_slv4_addr_
            .set_field(registers::I2C_SLV4_ADDR::I2C_ID_4, 0xC)      // set SLV4 address to mag
            .set_bit(registers::I2C_SLV4_ADDR::I2C_SLV4_RNW, false); // set SLV4 to write
        i2c_slv4_reg_.set_field(registers::I2C_SLV4_REG::REG,
                                registers::mag::CNTRL2::address);             // Set register to mag control reg
        i2c_slv4_do_.set_field(registers::I2C_SLV4_DO::DO, mag_cntrl2_.bits); // write mag control reg

        // Prepare SLV0 for reading
        i2c_slv0_ctrl_
            .set_bit(registers::I2C_SLV0_CTRL::I2C_SLV0_EN, true)   // Enable SLV0
            .set_field(registers::I2C_SLV0_CTRL::I2C_SLV0_LENG, 8); // Bytes to read
        i2c_slv0_addr_
            .set_field(registers::I2C_SLV0_ADDR::I2C_ID_0, 0x0C)                            // set SLV0 address to mag
            .set_bit(registers::I2C_SLV0_ADDR::I2C_SLV0_RNW, true);                         // set mode to read
        i2c_slv0_reg_.set_field(registers::I2C_SLV0_REG::REG, registers::mag::HX::address); // set read register on

        // i2c_slv0_reg_.set_field(registers::I2C_SLV0_REG::REG, registers::mag::ST1::address); // set read register on

        TRY(i2c_instance.write(
            user_ctrl_, i2c_mst_ctrl_, i2c_slv4_reg_, i2c_slv4_addr_, i2c_slv4_do_, i2c_slv0_addr_, i2c_slv0_reg_));

        // TRY(i2c_instance.write(user_ctrl_));
        // TRY(i2c_instance.write(i2c_mst_ctrl_));
        // TRY(i2c_instance.write(i2c_slv4_reg_));
        // TRY(i2c_instance.write(i2c_slv4_addr_));
        // TRY(i2c_instance.write(i2c_slv4_do_));
        // TRY(i2c_instance.write(i2c_slv0_addr_));
        // TRY(i2c_instance.write(i2c_slv0_reg_));

        TRY(i2c_instance.write(i2c_slv0_ctrl_));
        TRY(i2c_instance.write(i2c_slv4_ctrl_));

        for ([[maybe_unused]] auto _ : std::views::iota(0, 10))
        {
            auto mst_ctrl_status = i2c_instance.read<registers::I2C_MST_STATUS>();

            if (mst_ctrl_status->get_bit(registers::I2C_MST_STATUS::I2C_SLV4_DONE))
                return {};
            if (!mst_ctrl_status)
                return std::unexpected(mst_ctrl_status.error());
            if (mst_ctrl_status->get_bit(registers::I2C_MST_STATUS::I2C_LOST_ARB))
                return std::unexpected(ICMErrorT::ic2_mag_arb);
            if (mst_ctrl_status->get_bit(registers::I2C_MST_STATUS::I2C_SLV4_NACK))
                return std::unexpected(ICMErrorT::i2c_mag_nack);
            if (mst_ctrl_status->get_bit(registers::I2C_MST_STATUS::I2C_SLV0_NACK))
                return std::unexpected(ICMErrorT::i2c_mag_nack);

            sleep_us(20);
        }

        return std::unexpected(ICMErrorT::i2c_mag_timeout);
    }
    /** helpers **/
    auto ICM20948::calc_temp_from_raw(int16_t raw) -> float
    {
        return ((static_cast<int>(raw) - ROOM_TEMP_OFFS) / TEMP_SENS) + ROOM_TEMP_OFFS;
    }

} // namespace icm20948
