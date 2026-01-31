#pragma once

#include "../src/core/registers.hpp"

namespace icm20948
{
    struct ICM20948
    {
        ICM20948();
        registers::USER_CTRL usr_ctrl{};
        registers::PWR_MGMT_1 pwr_mgmt_1{};

        void write();
    };
} // namespace icm20948
