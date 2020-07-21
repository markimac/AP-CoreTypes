/**
 * Copyright (c) 2020
 *
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ARA_CORE_ALLOCATOR_H_
#define ARA_CORE_ALLOCATOR_H_

#include <memory>  // std::allocator

namespace ara::core {

/**
 * @brief Allocator
 *
 * @todo Define custom Allocator
 */
template<class T> using Allocator = std::allocator<T>;

/**
 * @brief AllocatorTraits
 *
 * @todo Define custom AllocatorTraits
 */
template<class Alloc> using AllocatorTraits = std::allocator_traits<Alloc>;

}  // namespace ara::core

#endif  // ARA_CORE_ALLOCATOR_H_
