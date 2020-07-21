/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef ARA_CORE_COREERRORDOMAIN_H_
#define ARA_CORE_COREERRORDOMAIN_H_

#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "ara/core/exception.h"

namespace ara::core {
/**
 * An enumeration that defines all errors of the CORE Functional Cluster.
 *
 * @req {SWS_CORE_05200}
 */
enum class CoreErrc : ErrorDomain::CodeType {
    /** an invalid argument was passed to a function */
    kInvalidArgument = 22,
    /** given string is not a valid model element shortname */
    kInvalidMetaModelShortname = 137,
    /** missing or invalid path to model element */
    kInvalidMetaModelPath = 138
};

/**
 * Exception type thrown for CORE errors.
 *
 * @req {SWS_CORE_05211}
 */
class CoreException : public Exception
{
 public:
    /**
     * Construct a new CoreException from an ErrorCode.
     *
     * @param err the ErrorCode
     */
    explicit CoreException(ErrorCode const& err) noexcept;
};

/**
 * An error domain for errors originating from the CORE Functional Cluster.
 *
 * @req {SWS_CORE_05221}
 */
class CoreErrorDomain final : public ErrorDomain
{
    constexpr static IdType coreId = 0x8000000000000014;

 public:
    /**
     * Alias for the error code value enumeration.
     *
     * @req {SWS_CORE_05231}
     */
    using Errc = CoreErrc;

    /**
     * Alias for the exception base class.
     *
     * @req {SWS_CORE_05232}
     */
    using Exception = CoreException;

    /**
     * Default constructor.
     *
     * @req {SWS_CORE_05241}
     */
    constexpr CoreErrorDomain() noexcept : ErrorDomain{coreId} {}

    /**
     * Return the "shortname" ApApplicationErrorDomain.SN of this error domain.
     *
     * @return char const* "Core"
     * @req {SWS_CORE_05242}
     */
    char const* Name() const noexcept override;

    /**
     * Translate an error code value into a text message.
     *
     * @param errorCode the error code value
     * @return char const* the text message, never nullptr
     * @req {SWS_CORE_05243}
     */
    char const*
    Message(ErrorDomain::CodeType errorCode) const noexcept override;

    /**
     * Throw the exception type corresponding to the given ErrorCode.
     *
     * @param errorCode the ErrorCode instance
     * @req {SWS_CORE_05244}
     */
    void ThrowAsException(ErrorCode const& errorCode) const override;
};

/**
 * Global CoreErrorDomain, which is returned in GetCoreErrorDomain function.
 *
 * The constexpr global variable is used, because GetCoreErrorDomain is
 * constexpr, so no static storage variable can be used.
 */
constexpr CoreErrorDomain coreErrorDomain;

/**
 * @brief Return a reference to the global CoreErrorDomain.
 *
 * @return constexpr ErrorDomain const& the CoreErrorDomain
 * @req {SWS_CORE_05280}
 */
constexpr ErrorDomain const& GetCoreErrorDomain() noexcept
{
    return coreErrorDomain;
}

/**
 * Create a new ErrorCode within CoreErrorDomain.
 * This function is used internally by constructors of ErrorCode. It is usually
 * not used directly by users.
 *
 * @param code the CoreErrorDomain-specific error code value
 * @param data optional vendor-specific error data
 * @return constexpr ErrorCode a new ErrorCode instance
 * @req {SWS_CORE_05290}
 */
constexpr ErrorCode
MakeErrorCode(CoreErrc code, ErrorDomain::SupportDataType data) noexcept
{
    return ErrorCode{static_cast<ErrorDomain::CodeType>(code),
                     GetCoreErrorDomain(),
                     data};
}

}  // namespace ara::core

#endif  // ARA_CORE_COREERRORDOMAIN_H_
