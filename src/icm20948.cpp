#include "i2c.hpp"
#include "registers.hpp"
#include <cstdint>
#include <hardware/i2c.h>
#include <icm20948/icm20948.hpp>

namespace icm20948
{
    void ICM20948::write()
    {
        // i2c.write(usr_ctrl);
        // auto pwr_mgmt = i2c.read<registers::PWR_MGMT_1>();
    }

    auto ICM20948::test_read() -> uint8_t
    {
        auto int_stat = registers::INT_STATUS{};
        int_stat = i2c_instance_.read<registers::INT_STATUS>();
        return int_stat.bits;
    }
} // namespace icm20948
