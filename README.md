# pico-icm20948

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue)
![RP2040](https://img.shields.io/badge/RP2040-Pico-green)
![Pico SDK](https://img.shields.io/badge/Pico%20SDK-required-blueviolet)

A small **C++20 driver/library for the InvenSense ICM-20948** (9-axis IMU) for
the **Raspberry Pi Pico / RP2040** using the **Pico SDK** (I2C).
This library is designed for clean, type-safe register access and modern C++20 usage on embedded systems.

> Status: work in progress. Sensor readout and basic configuration works. Sensor fusion (Madgwick) is planned

---

## Features

- Read:
  - Accelerometer ( $\frac{m}{s^2}$ )
  - Gyroscope ( $\frac{\text{deg}}{s}$)
  - Magnetometer ( $\mu T$ )
  - Temperature ( $^\circ C$ )
- Configure accel/gyro ranges
- Basic health/status checks
- Simple `Vec3` struct for data handling
- Error handling based on an `expected`-style API (`ErrorT<T>`)
  - No exceptions
  - Errors are propagated explicitly
  - Suitable for embedded systems

---

## Requirements

- Raspberry Pi pico SDK
- C++20 compatible ARM compiler

---

## Usage

Example (in your project `CMakeLists.txt`):

```cmake
add_subdirectory(pico-icm20948)

target_link_libraries(your_target
  PRIVATE
    pico_icm_20948
)
```

> Your Top-Level CMakeLists.txt needs to link against `pico_stdlib` and `hardware_i2c`

The library exports the public include directory (include/), so you can:

```C++
#include <icm20948/icm20948.hpp>
```

### Basic example

```C++
#include <icm20948/icm20948.hpp>
#include <hardware/i2c.h>

using namespace icm20948;

int main() {
    // init pico sdk, clocks, stdio etc.

    i2c_inst_t* i2c = i2c0; // or i2c1
    ICM20948 imu{i2c};

    if (auto err = imu.init(); !err) {
        // handle error
    }

    // optional: configure ranges
    imu.set_accel_range(AccelRange::g_4);
    imu.set_gyro_range(GyroRange::dps_500);

    while (true) {
        if (auto err = imu.update(); !err) { // reads sensors and updates cached values
          //handle error
        }

        Vec3<float> accel = imu.get_accel();
        Vec3<float> gyro  = imu.get_gyro();
        Vec3<int>   mag   = imu.get_mag();

        // use values...
    }
}
```

### Health checks

```C++
imu.update_health();

if (!imu.health.is_responsive) {
    // sensor not responding
}
```

## Error handling

This library does not use exceptions.
All functions that may fail return an `ErrorT<T>` type (similar to `std::expected`).
`ErrorT<T>` is an alias for `std::expected<T, ICMErrorT>`.

```C++
if (auto err = imu.update(); !err) {
  //handle error
}
```
