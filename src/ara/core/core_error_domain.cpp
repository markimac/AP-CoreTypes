#include "ara/core/core_error_domain.h"

#include <type_traits>

namespace ara::core {

CoreException::CoreException(ErrorCode const& err) noexcept : Exception{err} {}

char const* CoreErrorDomain::Name() const noexcept
{
    return "Core";
}

char const*
CoreErrorDomain::Message(ErrorDomain::CodeType errorCode) const noexcept
{
    switch (static_cast<CoreErrorDomain::Errc>(errorCode))
    {
    case CoreErrorDomain::Errc::kInvalidArgument:
        return "an invalid argument was passed to a function";
    case CoreErrorDomain::Errc::kInvalidMetaModelShortname:
        return "given string is not a valid model element shortname";
    case CoreErrorDomain::Errc::kInvalidMetaModelPath:
        return "missing or invalid path to model element";
    default:
        return "Invalid code value";
    }
}

void CoreErrorDomain::ThrowAsException(ErrorCode const& errorCode) const
{
    throw CoreErrorDomain::Exception(errorCode);
}

}  // namespace ara::core
