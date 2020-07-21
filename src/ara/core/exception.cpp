#include "ara/core/exception.h"

namespace ara::core {

Exception::Exception(ErrorCode const& err) noexcept : error{err} {}

const char* Exception::what() const noexcept
{
    return error.Message().data();
}

ErrorCode const& Exception::Error() const noexcept
{
    return error;
}
}  // namespace ara::core
