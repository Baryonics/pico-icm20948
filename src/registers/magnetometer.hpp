#pragma once
#include "register_base.hpp"
#include <cstdint>

namespace icm20948::registers::mag::addresses
{
    inline constexpr uint8_t WIA2 = 0x01;
    inline constexpr uint8_t ST1 = 0x10;
    inline constexpr uint8_t HXL = 0x11;
    inline constexpr uint8_t HXH = 0x12;
    inline constexpr uint8_t HYL = 0x13;
    inline constexpr uint8_t HYH = 0x14;
    inline constexpr uint8_t HZL = 0x15;
    inline constexpr uint8_t HZH = 0x16;
    inline constexpr uint8_t ST2 = 0x18;
    inline constexpr uint8_t CNTL2 = 0x31;
    inline constexpr uint8_t CNTL3 = 0x32;
} // namespace icm20948::registers::mag::addresses
