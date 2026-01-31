#include "i2c.hpp"
#include "registers.hpp"
#include <hardware/i2c.h>
#include <icm20948/icm20948.hpp>

namespace icm20948
{
    void ICM20948::write()
    {
        auto i2c = I2C{ i2c0_inst };
        i2c.write(usr_ctrl);
        auto pwr_mgmt = i2c.read<registers::PWR_MGMT_1>();
    }
} // namespace icm20948
