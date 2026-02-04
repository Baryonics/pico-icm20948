target_sources(pico_icm_20948
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/icm20948.cpp
)

target_include_directories(pico_icm_20948
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/registers
    ${CMAKE_CURRENT_LIST_DIR}/imu
)

