#include <catch2/catch.hpp>

#include <type_traits>

#include "ara/core/byte.h"

TEST_CASE("ByteImpl is not integral type", "[SWS_CORE], [SWS_CORE_10100]")
{
    REQUIRE(std::is_integral_v<ara::core::ByteImpl> == 0);
}

TEST_CASE("Size of ByteImpl is one", "[SWS_CORE], [SWS_CORE_10101]")
{
    REQUIRE(sizeof(ara::core::ByteImpl) == 1);
}

TEST_CASE("ByteImpl should be constrained in unsigned char limits",
          "[SWS_CORE], [SWS_CORE_10102]")
{
    REQUIRE_NOTHROW(ara::core::ByteImpl{0});
    REQUIRE_NOTHROW(
      ara::core::ByteImpl{std::numeric_limits<unsigned char>::max()});
}

TEST_CASE("ByteImpl can be created with integral type",
          "[SWS_CORE], [SWS_CORE_10103]")
{
    REQUIRE_NOTHROW(ara::core::ByteImpl{1});
    constexpr ara::core::ByteImpl byte{2};
    REQUIRE_NOTHROW((void) byte);
}

TEST_CASE("ByteImpl can be default constructed", "[SWS_CORE], [SWS_CORE_10104]")
{
    REQUIRE_NOTHROW(ara::core::ByteImpl{});
}

TEST_CASE("ByteImpl is trivially destructable", "[SWS_CORE], [SWS_CORE_10105]")
{
    REQUIRE(std::is_trivially_destructible_v<ara::core::ByteImpl>);
}

TEST_CASE("ByteImpl is not implicitly convertible from any other type",
          "[SWS_CORE], [SWS_CORE_10106]")
{
    REQUIRE_FALSE(std::is_convertible_v<uint8_t, ara::core::ByteImpl>);
    REQUIRE_FALSE(std::is_convertible_v<int, ara::core::ByteImpl>);
    REQUIRE_FALSE(std::is_convertible_v<char, ara::core::ByteImpl>);
}

TEST_CASE("ByteImpl is not implicitly convertible to any other type",
          "[SWS_CORE], [SWS_CORE_10107]")
{
    REQUIRE_FALSE(std::is_convertible_v<ara::core::ByteImpl, uint8_t>);
    REQUIRE_FALSE(std::is_convertible_v<ara::core::ByteImpl, int>);
    REQUIRE_FALSE(std::is_convertible_v<ara::core::ByteImpl, char>);
}

TEST_CASE("ByteImpl can be converted to unsigned char",
          "[SWS_CORE], [SWS_CORE_10108]")
{
    WHEN("Not in constant expression")
    {
        const unsigned char value{7};
        ara::core::ByteImpl byteObject{value};
        auto                byteValue = static_cast<unsigned char>(byteObject);
        REQUIRE(value == byteValue);
    }

    WHEN("In constant expression")
    {
        const unsigned char           value{7};
        constexpr ara::core::ByteImpl byteObject{value};
        constexpr auto byteValue = static_cast<unsigned char>(byteObject);
        REQUIRE(value == byteValue);
    }
}

TEST_CASE("ByteImpl shall be comparable for equality",
          "[SWS_CORE], [SWS_CORE_10109]")
{
    WHEN("ByteImpl objects are equal")
    {
        ara::core::ByteImpl byteObject1{1}, byteObject2{1};
        REQUIRE(byteObject1 == byteObject2);
    }

    WHEN("ByteImpl objects are not equal")
    {
        ara::core::ByteImpl byteObject1{1}, byteObject2{2};
        REQUIRE_FALSE(byteObject1 == byteObject2);
    }
}

TEST_CASE("ByteImpl shall be comparable for non-equality",
          "[SWS_CORE], [SWS_CORE_10110]")
{
    WHEN("ByteImpl objects are equal")
    {
        ara::core::ByteImpl byteObject1{1}, byteObject2{1};
        REQUIRE_FALSE(byteObject1 != byteObject2);
    }

    WHEN("ByteImpl objects are not equal")
    {
        ara::core::ByteImpl byteObject1{1}, byteObject2{2};
        REQUIRE(byteObject1 != byteObject2);
    }
}

TEST_CASE("ByteImpl can be changed to Integral type", "[SWS_CORE]")
{
    ara::core::ByteImpl byteObject{1};
    auto                int32Value(ara::core::to_integer<int32_t>(byteObject));
    REQUIRE(int32Value == 1);
    auto uint16Value(ara::core::to_integer<uint16_t>(byteObject));
    REQUIRE(uint16Value == 1u);
}

TEST_CASE("ByteImpl can be used with shift operators", "[SWS_CORE]")
{
    ara::core::ByteImpl byteObject1{4}, byteObject2{1};
    WHEN("Using operator >>") { REQUIRE((byteObject1 >> 2) == byteObject2); }
    WHEN("Using operator <<") { REQUIRE((byteObject2 << 2) == byteObject1); }
    WHEN("Using operator >>=")
    {
        byteObject1 >>= 2;
        REQUIRE(byteObject1 == byteObject2);
    }
    WHEN("Using operator <<=")
    {
        byteObject2 <<= 2;
        REQUIRE(byteObject2 == byteObject1);
    }
}

TEST_CASE("ByteImpl can be used with bitwise operators", "[SWS_CORE]")
{
    ara::core::ByteImpl byteObject1{1}, byteObject2{2}, byteObject3{3};
    WHEN("Using |,&,^,~")
    {
        REQUIRE((byteObject1 | byteObject3) == byteObject3);   // 01 | 11 = 11
        REQUIRE((byteObject1 & byteObject3) == byteObject1);   // 01 & 11 = 01
        REQUIRE((byteObject1 ^ byteObject3) == byteObject2);   // 01 ^ 11 = 10
        REQUIRE((~ara::core::ByteImpl{0xFE}) == byteObject1);  // ~0xFE = 0x01
    }
    WHEN("Using |=")
    {
        byteObject1 |= byteObject3;
        REQUIRE(byteObject1 == byteObject3);
    }
    WHEN("Using &=")
    {
        byteObject3 &= byteObject1;
        REQUIRE(byteObject1 == byteObject3);
    }
    WHEN("Using ^=")
    {
        byteObject1 ^= byteObject3;
        REQUIRE(byteObject1 == byteObject2);
    }
}
