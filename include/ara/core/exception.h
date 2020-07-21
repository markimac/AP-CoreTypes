/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef ARA_CORE_EXCEPTION_H_
#define ARA_CORE_EXCEPTION_H_

#include <exception>

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"

namespace ara::core {

// forward declarations
class ErrorCode;
class ErrorDomain;

/**
 * Base type for all AUTOSAR exception types.
 *
 * @req {SWS_CORE_00601}
 */
class Exception : public std::exception
{
 public:
    /**
     * Construct a new Exception object with a specific ErrorCode
     *
     * @param err the ErrorCode
     * @req {SWS_CORE_00611}
     */
    explicit Exception(ErrorCode const& err) noexcept;

    /**
     * Return the explanatory string.
     *
     * This function overrides the virtual function std::exception::what. All
     * guarantees about the lifetime of the returned pointer that are given for
     * std::exception::what are preserved.
     *
     * @return char const* a null-terminated string
     * @req {SWS_CORE_00612}
     */
    const char* what() const noexcept override;

    /**
     * Return the embedded ErrorCode that was given to the constructor.
     *
     * @return ErrorCode const& reference to the embedded ErrorCode
     * @req {SWS_CORE_00613}
     */
    ErrorCode const& Error() const noexcept;

 private:
    /**
     * The embedded ErrorCode.
     */
    ErrorCode const& error;
};

}  // namespace ara::core

#endif
