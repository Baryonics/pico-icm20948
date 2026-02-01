#include "i2c.hpp"
#include "userbank0.hpp"
#include <bit>
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

    auto ICM20948::get_temp() -> uint16_t
    {
        auto temp_reg = i2c_instance_.read<registers::TEMP_OUT>();
        return std::byteswap(temp_reg.bits);
    }

} // namespace icm20948
