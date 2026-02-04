#include "i2c.hpp"
#include "hardware/i2c.h"
#include "register_base.hpp"
#include "sensors/raw_data.hpp"
#include "userbank0.hpp"
#include <array>
#include <cstdint>
#include <cstring>

namespace icm20948
{
    void I2C::bulk_read_data_registers(data::ComposedRawData& raw_data)
    {
        select_user_bank(registers::UserBank::UB0);
        i2c_write_blocking(i2c_, address, &registers::ACCEL_XOUT::address, 1, true);
        auto raw_data_buffer = std::array<uint8_t, data::RAW_COMPOSED_SIZE>{};
        i2c_read_blocking(i2c_, address, raw_data_buffer.data(), data::RAW_COMPOSED_SIZE, false);
        memcpy(&raw_data.acc.x, &raw_data_buffer[0], sizeof(int16_t));
        memcpy(&raw_data.acc.y, &raw_data_buffer[2], sizeof(int16_t));
        memcpy(&raw_data.acc.z, &raw_data_buffer[4], sizeof(int16_t));
        memcpy(&raw_data.gyro.x, &raw_data_buffer[6], sizeof(int16_t));
        memcpy(&raw_data.gyro.y, &raw_data_buffer[8], sizeof(int16_t));
        memcpy(&raw_data.gyro.z, &raw_data_buffer[10], sizeof(int16_t));
        memcpy(&raw_data.temp, &raw_data_buffer[12], sizeof(int16_t));
    }
} // namespace icm20948
