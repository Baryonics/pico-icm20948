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

auto print_vec(const icm20948::Vec3<float>& vec) -> void
{
    for (auto idx : std::views::iota(0, 3))
    {
        printf("%.6f,", vec[idx]);
    }
}

auto print_calib_message(icm20948::Measurement& vals)
{
    print_vec(vals.acc_val);
    print_vec(vals.gyro_val);
    print_vec(vals.mag_val);
    printf("\n");
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

    icm20948::Measurement vals{};

    while (true)
    {
        while (!icm.update())
        {
            error_cnt++;
        }

        icm.get_measurement(vals);

        print_calib_message(vals);

        // auto raw = icm20948::RawMeasurement{};
        // icm.get_raw_measurements(raw);

        sleep_ms(20); // my god python is so slow
    }
}
