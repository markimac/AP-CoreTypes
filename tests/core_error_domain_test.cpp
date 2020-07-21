#include <catch2/catch.hpp>

#include <cstring>  // strcmp

#include "ara/core/core_error_domain.h"

namespace core = ara::core;

TEST_CASE("CoreErrc has correct values", "[SWS_CORE],[SWS_CORE_05200]")
{
    CHECK(static_cast<int>(core::CoreErrc::kInvalidArgument) == 22);
    CHECK(static_cast<int>(core::CoreErrc::kInvalidMetaModelShortname) == 137);
    CHECK(static_cast<int>(core::CoreErrc::kInvalidMetaModelPath) == 138);
}

TEST_CASE("CoreErrorDomain can be constructed",
          "[SWS_CORE],[SWS_CORE_05221],[SWS_CORE_05241]")
{
    core::CoreErrorDomain err;
    CHECK(err.Id() == core::ErrorDomain::IdType{0x8000000000000014});
}

TEST_CASE("CoreErrorDomain::Name should return `Core` c string",
          "[SWS_CORE],[SWS_CORE_05221],[SWS_CORE_05242]")
{
    auto& coreError = core::GetCoreErrorDomain();

    CHECK(std::strcmp(coreError.Name(), "Core") == 0);
}

TEST_CASE(
  "CoreErrorDomain::Message return proper c string, depending on CodeType passed",
  "[SWS_CORE],[SWS_CORE_05221],[SWS_CORE_05243]")
{
    auto& coreError = core::GetCoreErrorDomain();

    CHECK(
      std::strcmp(coreError.Message(static_cast<core::ErrorDomain::CodeType>(
                    core::CoreErrc::kInvalidArgument)),
                  "an invalid argument was passed to a function")
      == 0);
    CHECK(
      std::strcmp(coreError.Message(static_cast<core::ErrorDomain::CodeType>(
                    core::CoreErrc::kInvalidMetaModelShortname)),
                  "given string is not a valid model element shortname")
      == 0);
    CHECK(
      std::strcmp(coreError.Message(static_cast<core::ErrorDomain::CodeType>(
                    core::CoreErrc::kInvalidMetaModelPath)),
                  "missing or invalid path to model element")
      == 0);
    CHECK(std::strcmp(coreError.Message(core::ErrorDomain::CodeType{0}),
                      "Invalid code value")
          == 0);
}

TEST_CASE("CoreErrorDomain::ThrowAsException throw the correct Exception type",
          "[SWS_CORE],[SWS_CORE_05221],[SWS_CORE_05244]")
{
    core::ErrorCode error =
      core::MakeErrorCode(core::CoreErrc::kInvalidArgument,
                          core::ErrorDomain::SupportDataType{0});
    CHECK_THROWS_AS(core::GetCoreErrorDomain().ThrowAsException(error),
                    core::CoreException);
}

TEST_CASE("GetCoreErrorDomain return proper reference to the CoreErrorDomain",
          "[SWS_CORE],[SWS_CORE_05280]")
{
    CHECK(core::GetCoreErrorDomain() == core::coreErrorDomain);
    CHECK(core::GetCoreErrorDomain() == core::GetCoreErrorDomain());
}

TEST_CASE("MakeErrorCode returns proper ErrorCode",
          ",[SWS_CORE], [SWS_CORE_05290]")
{
    core::ErrorCode error =
      core::MakeErrorCode(core::CoreErrc::kInvalidArgument,
                          core::ErrorDomain::SupportDataType{0});

    CHECK(error.Domain() == core::GetCoreErrorDomain());
    CHECK(error.SupportData() == core::ErrorDomain::SupportDataType{0});
    CHECK(error.Message() == core::GetCoreErrorDomain().Name());
}

TEST_CASE("CoreException can be created and contains proper values",
          "[SWS_CORE], [SWS_CORE_05211]")
{
    core::ErrorCode error =
      core::MakeErrorCode(core::CoreErrc::kInvalidArgument,
                          core::ErrorDomain::SupportDataType{0});
    core::CoreException ex{error};

    CHECK(ex.what() == error.Message());
    CHECK(ex.Error() == error);
}
