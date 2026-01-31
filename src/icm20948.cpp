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
        auto who_am_i = registers::WHO_AM_I{};
        who_am_i = i2c_instance_.read<registers::WHO_AM_I>();
        return who_am_i.bits;
    }

    auto ICM20948::read_int_status() -> uint8_t
    {
        auto int_status = registers::INT_STATUS{};
        int_status = i2c_instance_.read<registers::INT_STATUS>();
        return int_status.bits;
    }

    void ICM20948::set_int()
    {
        auto int_enable = registers::INT_ENABLE{};
        int_enable.set_bit(int_enable.DMP_INT1_EN)
            .set_bit(int_enable.I2C_MST_INT_EN)
            .set_bit(int_enable.PLL_RDY_EN)
            .set_bit(int_enable.REG_WOF_EN)
            .set_bit(int_enable.WOM_INT_EN);
        i2c_instance_.write(int_enable);
    }
} // namespace icm20948
