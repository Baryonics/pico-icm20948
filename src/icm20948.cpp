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
        i2c_instance_.write(registers::PWR_MGMT_1{}); // init with 0 to wake from sleep
        enable_magnetometer();
    }

    auto ICM20948::who_am_i() -> uint8_t
    {
        auto who_am_i = registers::WHO_AM_I{};
        who_am_i = i2c_instance_.read<registers::WHO_AM_I>();
        return who_am_i.bits;
    }

    void ICM20948::enable_magnetometer() {}

    auto ICM20948::get_temp() -> int16_t { return get_value<registers::TEMP_OUT>(); }

    /** accel getter **/
    auto ICM20948::get_acc_x() -> int16_t { return get_value<registers::ACCEL_XOUT>(); }

    auto ICM20948::get_acc_y() -> int16_t { return get_value<registers::ACCEL_YOUT>(); }

    auto ICM20948::get_acc_z() -> int16_t { return get_value<registers::ACCEL_ZOUT>(); }

    /** gyro getter **/
    auto ICM20948::get_gyro_x() -> int16_t { return get_value<registers::GYRO_XOUT>(); }

    auto ICM20948::get_gyro_y() -> int16_t { return get_value<registers::GYRO_YOUT>(); }

    auto ICM20948::get_gyro_z() -> int16_t { return get_value<registers::GYRO_ZOUT>(); }

    /** mag getter **/
    auto ICM20948::get_mag_x() -> int16_t { return 0; };

    auto ICM20948::get_mag_y() -> int16_t { return 0; };

    auto ICM20948::get_mag_z() -> int16_t { return 0; };

} // namespace icm20948
