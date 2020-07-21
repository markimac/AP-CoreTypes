/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_BYTE_H_
#define ARA_CORE_BYTE_H_

#include <cstddef>

namespace ara::core {
/**
 * @brief Wrapper class for std::byte class object.
 *
 * @req {SWS_CORE_10100}
 */
class ByteImpl
{
 public:
    using ByteType = uint8_t;

    /**
     * @brief Construct a new Byte Impl object with no defined value.
     *
     * @req {SWS_CORE_10104}
     */
    ByteImpl() = default;

    /**
     * @brief Constuct object with given value.
     * @param Value of byte
     *
     * @req {SWS_CORE_10102, SWS_CORE_10103}
     */
    constexpr explicit ByteImpl(ByteType value) : impl{value} {}

    /**
     * @brief Default destructor.
     *
     * @req {SWS_CORE_10105}
     */
    ~ByteImpl() = default;

    /**
     * @brief Cast operator for machine byte type. Allowed only explicit
     * conversion.
     *
     * @return ByteType Value of byte given in byte machine type
     * @req {SWS_CORE_10106, SWS_CORE_10107, SWS_CORE_10108}
     */
    constexpr explicit operator ByteType() const
    {
        return static_cast<ByteType>(impl);
    }

    /**
     * @brief Equality operator for Byte object.
     *
     * @param rhs Byte object to compare with
     * @return true When given Byte object is equal
     * @return false When given Byte object is not equal
     * @req {SWS_CORE_10109}
     */
    constexpr bool operator==(const ByteImpl& rhs) const
    {
        return impl == rhs.impl;
    }

    /**
     * @brief Non-equality operator for Byte object.
     *
     * @param rhs Byte object to compare with
     * @return true When given Byte object is not equal
     * @return false When given Byte object equal
     * @req {SWS_CORE_10110}
     */
    constexpr bool operator!=(const ByteImpl& rhs) const
    {
        return ! (*this == rhs);
    }

 private:
    /**
     * @brief Only member is std::byte object which contains value.
     *
     * @req {SWS_CORE_10101}
     */
    std::byte impl;
};

/**
 * @brief Gives value of Byte object as integer.
 *
 * @tparam IntegerType Exact type of integer to return
 * @param b Byte object
 * @return constexpr IntegerType Integer value
 */
template<
  class IntegerType,
  class = typename std::enable_if<std::is_integral<IntegerType>::value>::type>
constexpr IntegerType to_integer(ByteImpl b) noexcept
{
    return IntegerType(static_cast<ByteImpl::ByteType>(b));
}

/**
 * @brief Left shift operator for Byte object.
 *
 * @tparam IntegerType Type of argument
 * @param b Byte object
 * @param shift Amount of bits to shift
 * @return constexpr ByteImpl Object with shifted value
 */
template<
  class IntegerType,
  class = typename std::enable_if<std::is_integral<IntegerType>::value>::type>
constexpr ByteImpl operator<<(ByteImpl b, IntegerType shift) noexcept
{
    return ByteImpl(static_cast<ByteImpl::ByteType>(
      static_cast<ByteImpl::ByteType>(b) << shift));
}

/**
 * @brief Left shift operator with assigment for Byte object.
 *
 * @tparam IntegerType Type of argument
 * @param b Byte object
 * @param shift Amount of bits to shift
 * @return constexpr ByteImpl& Reference to object with shifted value
 */
template<
  class IntegerType,
  class = typename std::enable_if<std::is_integral<IntegerType>::value>::type>
constexpr ByteImpl& operator<<=(ByteImpl& b, IntegerType shift) noexcept
{
    return b = b << shift;
}

/**
 * @brief Right shift operator for Byte object.
 *
 * @tparam IntegerType Type of argument
 * @param b Byte object
 * @param shift Amount of bits to shift
 * @return constexpr ByteImpl Object with shifted value
 */
template<
  class IntegerType,
  class = typename std::enable_if<std::is_integral<IntegerType>::value>::type>
constexpr ByteImpl operator>>(ByteImpl b, IntegerType shift) noexcept
{
    return ByteImpl(static_cast<ByteImpl::ByteType>(
      static_cast<ByteImpl::ByteType>(b) >> shift));
}

/**
 * @brief Right shift operator with assigment for Byte object.
 *
 * @tparam IntegerType Type of argument
 * @param b Byte object
 * @param shift Amount of bits to shift
 * @return constexpr ByteImpl& Reference to object with shifted value
 */
template<
  class IntegerType,
  class = typename std::enable_if<std::is_integral<IntegerType>::value>::type>
constexpr ByteImpl& operator>>=(ByteImpl& b, IntegerType shift) noexcept
{
    return b = b >> shift;
}

/**
 * @brief Bitwise OR operator for Byte object.
 *
 * @param l First byte object
 * @param r Second byte object
 * @return constexpr ByteImpl Object with result of OR operation
 */
constexpr ByteImpl operator|(ByteImpl l, ByteImpl r) noexcept
{
    return ByteImpl(static_cast<ByteImpl::ByteType>(l)
                    | static_cast<ByteImpl::ByteType>(r));
}

/**
 * @brief Bitwise OR operator with assigment for Byte object.
 *
 * @param l First byte object
 * @param r Second byte object
 * @return constexpr ByteImpl& Reference to object with result of OR operation
 */
constexpr ByteImpl& operator|=(ByteImpl& l, ByteImpl r) noexcept
{
    return l = l | r;
}

/**
 * @brief Bitwise AND operator for Byte object.
 *
 * @param l First byte object
 * @param r Second byte object
 * @return constexpr ByteImpl Object with result of AND operation
 */
constexpr ByteImpl operator&(ByteImpl l, ByteImpl r) noexcept
{
    return ByteImpl(static_cast<ByteImpl::ByteType>(l)
                    & static_cast<ByteImpl::ByteType>(r));
}

/**
 * @brief Bitwise AND operator with assigment for Byte object.
 *
 * @param l First byte object
 * @param r Second byte object
 * @return constexpr ByteImpl& Reference to object with result of AND operation
 */
constexpr ByteImpl& operator&=(ByteImpl& l, ByteImpl r) noexcept
{
    return l = l & r;
}

/**
 * @brief Bitwise XOR operator for Byte object.
 *
 * @param l First byte object
 * @param r Second byte object
 * @return constexpr ByteImpl Object with result of XOR operation
 */
constexpr ByteImpl operator^(ByteImpl l, ByteImpl r) noexcept
{
    return ByteImpl(static_cast<ByteImpl::ByteType>(l)
                    ^ static_cast<ByteImpl::ByteType>(r));
}

/**
 * @brief Bitwise XOR operator with assigment for Byte object.
 *
 * @param l First byte object
 * @param r Second byte object
 * @return constexpr ByteImpl& Reference to object with result of XOR operation
 */
constexpr ByteImpl& operator^=(ByteImpl& l, ByteImpl r) noexcept
{
    return l = l ^ r;
}

/**
 * @brief Bit inversion operator for Byte object.
 *
 * @param b Byte object
 * @return constexpr ByteImpl Object with value after inverting bits
 */
constexpr ByteImpl operator~(ByteImpl b) noexcept
{
    return ByteImpl(~static_cast<ByteImpl::ByteType>(b));
}

}  // namespace ara::core

#endif  // ARA_CORE_BYTE_H_
