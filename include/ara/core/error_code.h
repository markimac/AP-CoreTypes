/**
 * Copyright (c) 2020
 * umlaut Software Development and contributors
 *
 * SPDX-License-Identifier: MIT
 */
#ifndef ARA_CORE_ERRORCODE_H_
#define ARA_CORE_ERRORCODE_H_

#include "ara/core/error_domain.h"
#include "ara/core/string_view.h"

namespace ara::core {

// forward declarations
class ErrorDomain;

/**
 * Encapsulation of an error code.
 *
 * An ErrorCode contains a raw error code value and an error domain. The raw
 * error code value is specific to this error domain.
 *
 * @req {SWS_CORE_00501}
 */
class ErrorCode final
{
 public:
    /**
     * Construct a new ErrorCode instance with parameters.
     *
     * This constructor does not participate in overload resolution unless EnumT
     * is an enum type.
     *
     * @tparam EnumT an enum type that contains error code values.
     * @param e a domain-specific error code value.
     * @param data optional vendor-specific supplementary error context data.
     * @req {SWS_CORE_00512}
     */
    template<typename EnumT>
    constexpr ErrorCode(EnumT                        e,
                        ErrorDomain::SupportDataType data =
                          ErrorDomain::SupportDataType()) noexcept
    {
        *this = MakeErrorCode(e, data);
    }

    /**
     * Construct a new ErrorCode instance with parameters.
     *
     * @param value a domain-specific error code value.
     * @param domain the ErrorDomain associated with value.
     * @param data optional vendor-specific supplementary error context data.
     * @req {SWS_CORE_00513}
     */
    constexpr ErrorCode(ErrorDomain::CodeType        value,
                        ErrorDomain const&           domain,
                        ErrorDomain::SupportDataType data =
                          ErrorDomain::SupportDataType()) noexcept
      : value{value}, domain{&domain}, data{data}
    {}

    /**
     * Return the raw error code value.
     *
     * @return constexpr ErrorDomain::CodeType the raw error code value.
     * @req {SWS_CORE_00514}
     */
    constexpr ErrorDomain::CodeType Value() const noexcept { return value; }

    /**
     * Return the domain with which this ErrorCode is associated.
     *
     * @return constexpr ErrorDomain const& the ErrorDomain
     * @req {SWS_CORE_00515}
     */
    constexpr ErrorDomain const& Domain() const noexcept { return *domain; }

    /**
     * Return the supplementary error context data.
     *
     * The underlying type and the meaning of the returned value are
     * implementation-defined.
     *
     * @return constexpr ErrorDomain::SupportDataType the supplementary error
     * context data.
     * @req {SWS_CORE_00516}
     */
    constexpr ErrorDomain::SupportDataType SupportData() const noexcept
    {
        return data;
    }

    /**
     * Return a textual representation of this ErrorCode.
     *
     * @return StringView the error message text
     * @req {SWS_CORE_00518}
     */
    StringView Message() const noexcept { return StringView(domain->Name()); }

    /**
     * Throw this error as exception.
     *
     * This function will determine the appropriate exception type for this
     * ErrorCode and throw it. The thrown exception will contain this ErrorCode.
     *
     * @req {SWS_CORE_00519}
     */
    void ThrowAsException() const { domain->ThrowAsException(*this); }

 private:
    /**
     * The domain-specific error code value.
     */
    ErrorDomain::CodeType value;
    /**
     * The ErrorDomain associated with value
     */
    const ErrorDomain* domain;
    /**
     * Optional vendor-specific supplementary error context data
     */
    ErrorDomain::SupportDataType data;
};

/**
 * Global operator== for ErrorCode.
 *
 * Two ErrorCode instances compare equal if the results of their Value() and
 * Domain() functions are equal. The result of SupportData() is not considered
 * for equality.
 *
 * @param lhs the left hand side of the comparison
 * @param rhs the right hand side of the comparison
 * @return true if the two instances compare equal, false otherwise
 * @req {SWS_CORE_00571}
 */
constexpr bool operator==(ErrorCode const& lhs, ErrorCode const& rhs) noexcept
{
    return lhs.Value() == rhs.Value() && lhs.Domain() == rhs.Domain();
}

/**
 * Global operator!= for ErrorCode.
 *
 * Two ErrorCode instances compare equal if the results of their Value() and
 * Domain() functions are equal. The result of SupportData() is not considered
 * for equality.
 *
 * @param lhs the left hand side of the comparison
 * @param rhs the right hand side of the comparison
 * @return true if the two instances compare not equal, false otherwise
 * @req {SWS_CORE_00572}
 */
constexpr bool operator!=(ErrorCode const& lhs, ErrorCode const& rhs) noexcept
{
    return ! (lhs == rhs);
}

}  // namespace ara::core

#endif  // ARA_CORE_ERRORCODE_H_
