#pragma once
#include <concepts>
#include <cstdint>
#include <utility>

namespace icm20948::registers
{
    /** Access indicator **/
    enum class AccessT
    {
        r,
        w,
        rw
    };

    enum class UserBank
    {
        UB0 = 0,
        UB1 = 1,
        UB2 = 2,
        UB3 = 3,
        MAG = 4
    };

    template <uint8_t From, uint8_t To>
    struct BitField
    {
        constexpr static uint8_t from = From;
        constexpr static uint8_t to = To;
    };

    template <uint8_t Pos>

    struct Bit
    {
        constexpr static uint8_t pos = Pos;
    };

    /** Base Class for Registers **/
    template <uint8_t Address, UserBank UB, AccessT Access, typename RegSizeT = uint8_t>
        requires(std::same_as<RegSizeT, uint8_t> || std::same_as<RegSizeT, uint16_t>)
    struct RegBase
    {
        constexpr static uint8_t address = Address;
        constexpr static UserBank user_bank = UB;
        constexpr static AccessT access = Access;
        RegSizeT bits{ 0 };

        template <uint8_t pos>
            requires(pos < 8 and (access == AccessT::rw or access == AccessT::w))
        RegBase& set_bit(Bit<pos> bit, bool state = true)
        {
            auto mask = (RegSizeT(1) << pos);
            bits = (bits & ~mask) | (state ? mask : 0);
            return *this;
        }

        template <uint8_t from, uint8_t to, typename T>
            requires(std::is_enum_v<T> and from < to and to < 8 and (access == AccessT::rw or access == AccessT::w))
        RegBase& set_field(BitField<from, to>, T value)
        {
            constexpr auto width = uint8_t{ (to - from + 1U) };
            auto mask = RegSizeT{ ((1U << width) - 1U) << from };
            bits = (bits & ~mask) | (((std::to_underlying(value) << from)) & mask);
            return *this;
        }

        template <uint8_t pos>
            requires(pos < 8 and (access == AccessT::rw or access == AccessT::r))
        bool get_bit(Bit<pos> bit)
        {
            return (bits & (RegSizeT(1) << pos)) != 0;
        }

        template <uint8_t from, uint8_t to, typename T>
            requires(std::is_enum_v<T> and from < to and to < 8 and (access == AccessT::rw or access == AccessT::r))
        T get_field(BitField<from, to>)
        {
            constexpr auto width = uint8_t{ (to - from + 1U) };
            auto mask = RegSizeT{ ((1U << width) - 1U) << from };

            return static_cast<T>((mask & bits) >> from);
        }
    };

    template <typename T>
    concept reg_type = requires {
        { T::address } -> std::convertible_to<uint8_t>;
        { T::user_bank } -> std::same_as<const UserBank&>;
        { T::access } -> std::same_as<const AccessT&>;
    };

} // namespace icm20948::registers
