#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "math.hpp"
#include "pico/stdlib.h"
#include <icm20948/calibration.hpp>
#include <icm20948/icm20948.hpp>
#include <pico/stdio.h>
#include <pico/time.h>
#include <ranges>
#include <stdio.h>

auto print_vec(const icm20948::Vec3<int16_t>& vec) -> void
{
    for (auto idx : std::views::iota(0, 3))
    {
        printf("%d,", vec[idx]);
    }
}

auto print_calib_message(icm20948::RawMeasurement& raw_vals)
{
    printf("S %d,", raw_vals.time_stamp);
    print_vec(raw_vals.raw_acc_val);
    print_vec(raw_vals.raw_gyro_val);
    print_vec(raw_vals.raw_mag_val);
    printf("%d H\n", raw_vals.raw_temp_val);
}

auto main() -> int
{
    stdio_init_all();
    i2c_init(i2c0, 400 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    sleep_ms(100);
    auto icm = icm20948::ICM20948{ i2c0 };

    auto error_cnt{ 0 };
    while (!icm.init())
    {
        sleep_ms(10);
        error_cnt++;
    }

    icm20948::RawMeasurement raw_vals{};

    while (true)
    {
        while (!icm.update())
        {
            error_cnt++;
        }

        icm.get_raw_measurements(raw_vals);

        if (error_cnt)
            printf(" \n# Errors %d \n", error_cnt);

        print_calib_message(raw_vals);
        sleep_ms(100);
    }
}
