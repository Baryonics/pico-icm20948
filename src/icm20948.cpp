#include "i2c.hpp"
#include "userbank0.hpp"
#include <cstdint>
#include <hardware/i2c.h>
#include <icm20948/icm20948.hpp>

namespace icm20948
{
    ICM20948::ICM20948(i2c_inst_t* i2c_instance)
    {
        i2c_instance_ = i2c_instance;
        enable_magnetometer();
    }

    auto ICM20948::who_am_i() -> uint8_t
    {
        auto who_am_i = registers::WHO_AM_I{};
        who_am_i = i2c_instance_.read<registers::WHO_AM_I>();
        return who_am_i.bits;
    }

    void ICM20948::enable_magnetometer() {}

    auto ICM20948::get_temp() -> uint16_t { return get_value<registers::TEMP_OUT>(); }

    /** accel getter **/
    auto ICM20948::get_acc_x() -> uint16_t { return get_value<registers::ACCEL_XOUT>(); }

    auto ICM20948::get_acc_y() -> uint16_t { return get_value<registers::ACCEL_YOUT>(); }

    auto ICM20948::get_acc_z() -> uint16_t { return get_value<registers::ACCEL_ZOUT>(); }

    /** gyro getter **/
    auto ICM20948::get_gyro_x() -> uint16_t { return get_value<registers::GYRO_XOUT>(); }

    auto ICM20948::get_gyro_y() -> uint16_t { return get_value<registers::GYRO_YOUT>(); }

    auto ICM20948::get_gyro_z() -> uint16_t { return get_value<registers::GYRO_ZOUT>(); }

} // namespace icm20948
