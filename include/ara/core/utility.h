/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef ARA_CORE_UTILITY_H_
#define ARA_CORE_UTILITY_H_

#include <utility>

#include "ara/core/byte.h"

namespace ara::core {
/**
 * It is a type that is able to hold a “byte” of the machine.
 * It is an own type distinct from any other type.
 *
 * @req {SWS_CORE_04200}
 */
using Byte = ByteImpl;

/**
 * An instance of this type can be passed to certain constructors of
 * ara::core::Optional to denote the intention that construction of the
 * contained type shall be done in-place.
 *
 * @req {SWS_CORE_04011, SWS_CORE_04012}
 */
struct in_place_t
{
    explicit in_place_t() = default;
};

/**
 * Instance of ara::core::in_place_t
 *
 * @req {SWS_CORE_04013}
 */
inline constexpr in_place_t in_place{};

/**
 * An instance of this type can be passed to certain constructors of
 * ara::core::Variant to denote the intention that construction of the contained
 * type shall be done in-place. Denote an type-distinguishing operation.
 *
 * @req {SWS_CORE_04021, SWS_CORE_04022}
 */
template<typename T> struct in_place_type_t
{
    explicit in_place_type_t() = default;
};

/**
 * An instance of this type can be passed to certain constructors of
 * ara::core::Variant to denote the intention that construction of the contained
 * type shall be done in-place. Denote an index-distinguishing operation.
 *
 * @req {SWS_CORE_04031, SWS_CORE_04032}
 */
template<std::size_t I> struct in_place_index_t
{
    explicit in_place_index_t() = default;
};

/**
 * These global functions allow uniform access to the data and size properties
 * of contiguous containers. They are eqavilents to functions from C++17
 */

/**
 * Return a pointer to the block of memory that contains the elements of a
 * container.
 *
 * @param c the container
 * @return pointer to data
 * @req {SWS_CORE_04110}
 */
template<typename Container> constexpr auto data(Container& c)
  -> decltype(c.data())
{
    return std::data(c);
}

/**
 * Return a const_pointer to the block of memory that contains the elements of a
 * container
 *
 * @param c the container
 * @return const pointer to data
 * @req {SWS_CORE_04111}
 */
template<typename Container> constexpr auto data(Container const& c)
  -> decltype(c.data())
{
    return std::data(c);
}

/**
 * Return a pointer to the block of memory that contains the elements of a raw
 * array.
 *
 * @param array the array
 * @return pointer to data
 * @req {SWS_CORE_04112}
 */
template<typename T, std::size_t N> constexpr T* data(T (&array)[N]) noexcept
{
    return std::data(array);
}

/**
 * Return a pointer to the block of memory that contains the elements of a
 * std::initializer_list
 *
 * @param il initializer list
 * @return const pointer to data
 * @req {SWS_CORE_04113}
 */
template<typename E> constexpr E const*
data(std::initializer_list<E> il) noexcept
{
    return std::data(il);
}

/**
 * Return the size of a container.
 *
 * @param c container
 * @return size of container
 *
 * @req {SWS_CORE_04120}
 */
template<typename Container> constexpr auto size(Container const& c)
  -> decltype(c.size())
{
    return std::size(c);
}

/**
 * Return the size of a raw array
 *
 * @param array the array
 * @return size of array
 * @req {SWS_CORE_04121}
 */
template<typename T, std::size_t N> constexpr std::size_t
  size(T (&array)[N]) noexcept
{
    return std::size(array);
}

/**
 * Return whether the given container is empty.
 *
 * @param c container
 * @return true if container is empty
 * @return false otherwise
 * @req {SWS_CORE_04130}
 */
template<typename Container> constexpr auto empty(Container const& c)
  -> decltype(c.empty())
{
    return std::empty(c);
}

/**
 * Return whether the given raw array is empty
 *
 * @param array thr array
 * @return true if array is empty
 * @return false otherwise
 * @req {SWS_CORE_04131}
 */
template<typename T, std::size_t N> constexpr bool empty(T (&array)[N]) noexcept
{
    return std::empty(array);
}

/**
 * Return whether the given std::initializer_list is empty
 *
 * @param il initializer list
 * @return true if initializer list is empty
 * @return false otherwise
 * @req {SWS_CORE_04132}
 */
template<typename E> constexpr bool empty(std::initializer_list<E> il) noexcept
{
    return std::empty(il);
}
}  // namespace ara::core
#endif  // ARA_CORE_UTILITY_H_
