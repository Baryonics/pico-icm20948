add_library(pico_icm_20948 STATIC)

target_include_directories(pico_icm_20948
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

add_subdirectory(src)

target_link_libraries(pico_icm_20948
  PRIVATE
    pico_stdlib
    hardware_i2c
)
