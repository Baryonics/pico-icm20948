#include "i2c.hpp"
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

    void ICM20948::enable_magnetometer() {}
} // namespace icm20948
