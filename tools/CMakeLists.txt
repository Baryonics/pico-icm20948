
cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(calibration_firmware C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(
  "${CMAKE_CURRENT_LIST_DIR}/.."              # = repo root (wo pico_icm_20948/CMakeLists.txt liegt)
  "${CMAKE_BINARY_DIR}/pico_icm_20948_build"  # beliebiges build-dir
)
pico_sdk_init()
add_executable(calib_fw
    calib_fw.cpp
)

target_link_libraries(calib_fw
    PRIVATE
        pico_stdlib
        hardware_i2c
        pico_icm_20948
)


pico_enable_stdio_usb(calib_fw 1)
pico_enable_stdio_uart(calib_fw 1)
pico_add_extra_outputs(calib_fw)

