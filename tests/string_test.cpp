#include <catch2/catch.hpp>

#include <type_traits>
#include <cstring>

#include "ara/core/string.h"

namespace core = ara::core;

TEST_CASE("BasicString: Implicit conversion to StringView (nothrow)", "[SWS_CORE], [SWS_CORE_03301]")
{
    using core::BasicString;
    using core::StringView;

    CHECK(std::is_convertible<BasicString<>, StringView >::value);
    CHECK(std::is_nothrow_convertible<BasicString<>, StringView >::value);

}

TEST_CASE("BasicString: Constructor from StringView (explicit)", "[SWS_CORE], [SWS_CORE_03302]")
{
    using core::BasicString;
    using core::StringView;

    CHECK(std::is_constructible<BasicString<>, StringView>::value);
    CHECK_FALSE(std::is_convertible<StringView, BasicString<> >::value);

}

TEST_CASE("BasicString: Constructor from implicit StringView", "[SWS_CORE], [SWS_CORE_03303]")
{
    using core::BasicString;
    using core::StringView;

    typedef BasicString<>::size_type size_type;

    CHECK(std::is_constructible<BasicString<>, StringView, size_type, size_type>::value);

}

TEST_CASE("BasicString: operator= from StringView", "[SWS_CORE], [SWS_CORE_03304]")
{
    using core::BasicString;
    using core::StringView;

    CHECK(std::is_assignable<BasicString<>, StringView>::value);
}

TEST_CASE("BasicString: String type", "[SWS_CORE], [SWS_CORE_03001]")
{
    CHECK(std::is_same<class core::BasicString<>, typename core::String >::value);
}

TEST_CASE("BasicString: swap overload for BasicString", "[SWS_CORE], [SWS_CORE_03296]")
{
    using core::BasicString;
    using core::swap;

    BasicString a("a");
    BasicString b("b");

    REQUIRE(a == "a");
    REQUIRE(b == "b");

    swap(a, b);

    CHECK(a == "b");
    CHECK(b == "a");
}

TEST_CASE("BasicString::operator=", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    REQUIRE(std::is_copy_assignable<BasicString<> >::value);
    REQUIRE(std::is_move_assignable<BasicString<> >::value);
    REQUIRE(std::is_assignable<BasicString<>, const char*>::value);
    REQUIRE(std::is_assignable<BasicString<>, char>::value);
    REQUIRE(std::is_assignable<BasicString<>, std::initializer_list<char> >::value);

    BasicString str;
    REQUIRE(str.empty());

    SECTION("BasicString::operator=(const BasicString&)")
    {
        BasicString qwerty("QWERTY");
        str = qwerty;
        CHECK(str == qwerty);
    }
    SECTION("BasicString::operator=(BasicString&&)")
    {
        str = BasicString("QWERTY");
        CHECK(str == "QWERTY");
    }
    SECTION("BasicString::operator=(const char*)")
    {
        str = "QWERTY";
        CHECK(str == "QWERTY");
    }
    SECTION("BasicString::operator=(char)")
    {
        str = 'Q';
        CHECK(str == "Q");
    }
    SECTION("BasicString::operator=(std::initializer_list<char>)")
    {
        str = {'Q', 'W', 'E', 'R', 'T', 'Y'};
        CHECK(str == "QWERTY");
    }
}

TEST_CASE("BasicString::BasicString", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;
    typedef core::BasicString<>::size_type size_type;
    typedef core::Allocator<char> Alloc;

    REQUIRE(std::is_constructible<BasicString<>, Alloc>::value);

    REQUIRE(std::is_copy_constructible<BasicString<> >::value);

    REQUIRE(std::is_nothrow_move_constructible<BasicString<> >::value);

    REQUIRE(std::is_constructible<BasicString<>, BasicString<>&, size_type, size_type, const Alloc&>::value);
    REQUIRE(std::is_constructible<BasicString<>, BasicString<>&, size_type, size_type>::value);

    REQUIRE(std::is_constructible<BasicString<>, const char*, size_type, const Alloc&>::value);
    REQUIRE(std::is_constructible<BasicString<>, const char*, size_type>::value);

    REQUIRE(std::is_constructible<BasicString<>, const char*, const Alloc&>::value);
    REQUIRE(std::is_constructible<BasicString<>, const char*>::value);

    REQUIRE(std::is_constructible<BasicString<>, size_type, char, const Alloc&>::value);
    REQUIRE(std::is_constructible<BasicString<>, size_type, char>::value);

    REQUIRE(std::is_constructible<BasicString<>, char*, char*, const Alloc&>::value);

    REQUIRE(std::is_constructible<BasicString<>, std::initializer_list<char>, const Alloc&>::value);
    REQUIRE(std::is_constructible<BasicString<>, std::initializer_list<char> >::value);

    REQUIRE(std::is_constructible<BasicString<>, const BasicString<>&, const Alloc&>::value);
    REQUIRE(std::is_constructible<BasicString<>, BasicString<>&, const Alloc&>::value);

}

TEST_CASE("BasicString::operator==", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString qwerty1("QWERTY");
    BasicString qwerty2("QWERTY");
    BasicString qwertz1("QWERTZ");

    SECTION("BasicString::operator==(const BasicString&) const")
    {
        CHECK(qwerty1 == qwerty2);
        CHECK(qwerty2 == qwerty1);
        CHECK_FALSE(qwerty1 == qwertz1);
        CHECK_FALSE(qwertz1 == qwerty1);
    }

    SECTION("BasicString::operator==(const char*) const")
    {
        CHECK(qwerty1 == "QWERTY");
        CHECK_FALSE(qwerty1 == "QWERTZ");
    }

    SECTION("operator==(const char*, const BasicString&)")
    {
        CHECK("QWERTY" == qwerty1);
        CHECK_FALSE("QWERTZ" == qwerty1);
    }
}

TEST_CASE("BasicString::operator!=", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString qwerty1("QWERTY");
    BasicString qwerty2("QWERTY");
    BasicString qwertz1("QWERTZ");

    SECTION("BasicString::operator!=(const BasicString&) const")
    {
        CHECK_FALSE(qwerty1 != qwerty2);
        CHECK_FALSE(qwerty2 != qwerty1);
        CHECK(qwerty1 != qwertz1);
        CHECK(qwertz1 != qwerty1);
    }

    SECTION("BasicString::operator!=(const char*) const")
    {
        CHECK(qwerty1 != "QWERTZ");
        CHECK_FALSE(qwerty1 != "QWERTY");
    }

    SECTION("operator!=(const char*, const BasicString&)")
    {
        CHECK("QWERTZ" != qwerty1);
        CHECK_FALSE("QWERTY" != qwerty1);
    }
}

TEST_CASE("BasicString::operator<", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString abc("abc");

    SECTION("operator<(const char*, const BasicString&)")
    {
        CHECK("ab" < abc);
        CHECK("abba" < abc);
        CHECK_FALSE("ad" < abc);
        CHECK_FALSE("abc" < abc);
        CHECK_FALSE("abca" < abc);
    }

    SECTION("BasicString::operator<(const char*)")
    {
        CHECK(abc < "abd");
        CHECK(abc < "abcd");
        CHECK_FALSE(abc < "ab");
        CHECK_FALSE(abc < "aba");
        CHECK_FALSE(abc < "abab");
    }

    SECTION("BasicString::operator<(const BasicString&)")
    {
        CHECK(abc < BasicString("ad"));
        CHECK(abc < BasicString("abd"));
        CHECK(abc < BasicString("abca"));
        CHECK_FALSE(abc < BasicString("ab"));
        CHECK_FALSE(abc < BasicString("aba"));
        CHECK_FALSE(abc < BasicString("abab"));
    }
}

TEST_CASE("BasicString::operator>", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString abc("abc");
    SECTION("operator>(const char*, const BasicString&)")
    {
        CHECK("abd" > abc);
        CHECK("abde" > abc);
        CHECK_FALSE("aba" > abc);
        CHECK_FALSE("abae" > abc);
    }

    SECTION("BasicString::operator>(const char*)")
    {
        CHECK(abc > "ab");
        CHECK(abc > "abb");
        CHECK(abc > "abab");
        CHECK_FALSE(abc > "ac");
        CHECK_FALSE(abc > "acb");
        CHECK_FALSE(abc > "abcb");
    }

    SECTION("BasicString::operator>(const BasicString&)")
    {
        CHECK(abc > BasicString("ab"));
        CHECK(abc > BasicString("abb"));
        CHECK(abc > BasicString("abab"));
        CHECK_FALSE(abc > BasicString("ac"));
        CHECK_FALSE(abc > BasicString("acb"));
        CHECK_FALSE(abc > BasicString("abcb"));
    }
}

TEST_CASE("BasicString::operator<=", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString abc("abc");

    SECTION("operator<=(const char*, const BasicString&)")
    {
        CHECK("ab" <= abc);
        CHECK("abc" <= abc);
        CHECK("abba" <= abc);
        CHECK_FALSE("ad" <= abc);
        CHECK_FALSE("abd" <= abc);
        CHECK_FALSE("abca" <= abc);
    }

    SECTION("BasicString::operator<=(const char*)")
    {
        CHECK(abc <= "abd");
        CHECK(abc <= "abc");
        CHECK(abc <= "abcd");
        CHECK_FALSE(abc <= "ab");
        CHECK_FALSE(abc <= "aba");
        CHECK_FALSE(abc <= "abab");
    }

    SECTION("BasicString::operator<=(const BasicString&)")
    {
        CHECK(abc <= BasicString("ad"));
        CHECK(abc <= BasicString("abc"));
        CHECK(abc <= BasicString("abd"));
        CHECK(abc <= BasicString("abca"));
        CHECK_FALSE(abc <= BasicString("ab"));
        CHECK_FALSE(abc <= BasicString("aba"));
        CHECK_FALSE(abc <= BasicString("abab"));
    }
}

TEST_CASE("BasicString::operator>=", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString abc("abc");
    SECTION("operator>=(const char*, const BasicString&)")
    {
        CHECK("abd" >= abc);
        CHECK("abc" >= abc);
        CHECK("abde" >= abc);
        CHECK_FALSE("aba" >= abc);
        CHECK_FALSE("abae" >= abc);
    }

    SECTION("BasicString::operator>=(const char*)")
    {
        CHECK(abc >= "ab");
        CHECK(abc >= "abb");
        CHECK(abc >= "abc");
        CHECK(abc >= "abab");
        CHECK_FALSE(abc >= "ac");
        CHECK_FALSE(abc >= "acb");
        CHECK_FALSE(abc >= "abcb");
    }

    SECTION("BasicString::operator>=(const BasicString&)")
    {
        CHECK(abc >= BasicString("ab"));
        CHECK(abc >= BasicString("abb"));
        CHECK(abc >= BasicString("abc"));
        CHECK(abc >= BasicString("abab"));
        CHECK_FALSE(abc >= BasicString("ac"));
        CHECK_FALSE(abc >= BasicString("acb"));
        CHECK_FALSE(abc >= BasicString("abcb"));
    }
}

TEST_CASE("BasicString::compare", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString abc("abc");
    SECTION("BasicString::compare(const BasicString&) >= 0")
    {
        CHECK(      abc.compare(BasicString("ab")) >= 0);
        CHECK(      abc.compare(BasicString("abb")) >= 0);
        CHECK(      abc.compare(BasicString("abc")) >= 0);
        CHECK(      abc.compare(BasicString("abab")) >= 0);
        CHECK_FALSE(abc.compare(BasicString("ac")) >= 0);
        CHECK_FALSE(abc.compare(BasicString("acb")) >= 0);
        CHECK_FALSE(abc.compare(BasicString("abcb")) >= 0);
    }

    SECTION("BasicString::compare(const BasicString&) > 0")
    {
        CHECK(      abc.compare(BasicString("ab")) > 0);
        CHECK(      abc.compare(BasicString("abb")) > 0);
        CHECK(      abc.compare(BasicString("abab")) > 0);
        CHECK_FALSE(abc.compare(BasicString("ac")) > 0);
        CHECK_FALSE(abc.compare(BasicString("acb")) > 0);
        CHECK_FALSE(abc.compare(BasicString("abcb")) > 0);
    }

    SECTION("BasicString::compare(const BasicString&) <= 0")
    {
        CHECK(      abc.compare(BasicString("ad")) <= 0);
        CHECK(      abc.compare(BasicString("abc")) <= 0);
        CHECK(      abc.compare(BasicString("abd")) <= 0);
        CHECK(      abc.compare(BasicString("abca")) <= 0);
        CHECK_FALSE(abc.compare(BasicString("ab")) <= 0);
        CHECK_FALSE(abc.compare(BasicString("aba")) <= 0);
        CHECK_FALSE(abc.compare(BasicString("abab")) <= 0);
    }

    SECTION("BasicString::compare(const BasicString&) < 0")
    {
        CHECK(      abc.compare(BasicString("ad")) < 0);
        CHECK(      abc.compare(BasicString("abd")) < 0);
        CHECK(      abc.compare(BasicString("abca")) < 0);
        CHECK_FALSE(abc.compare(BasicString("ab")) < 0);
        CHECK_FALSE(abc.compare(BasicString("aba")) < 0);
        CHECK_FALSE(abc.compare(BasicString("abab")) < 0);
    }

    SECTION("BasicString::compare(const char*) >= 0")
    {
        CHECK(      abc.compare("ab") >= 0);
        CHECK(      abc.compare("abb") >= 0);
        CHECK(      abc.compare("abc") >= 0);
        CHECK(      abc.compare("abab") >= 0);
        CHECK_FALSE(abc.compare("ac") >= 0);
        CHECK_FALSE(abc.compare("acb") >= 0);
        CHECK_FALSE(abc.compare("abcb") >= 0);
    }

    SECTION("BasicString::compare(const char*) > 0")
    {
        CHECK(      abc.compare("ab") > 0);
        CHECK(      abc.compare("abb") > 0);
        CHECK(      abc.compare("abab") > 0);
        CHECK_FALSE(abc.compare("ac") > 0);
        CHECK_FALSE(abc.compare("acb") > 0);
        CHECK_FALSE(abc.compare("abcb") > 0);
    }

    SECTION("BasicString::compare(const char*) <= 0")
    {
        CHECK(      abc.compare("ad") <= 0);
        CHECK(      abc.compare("abc") <= 0);
        CHECK(      abc.compare("abd") <= 0);
        CHECK(      abc.compare("abca") <= 0);
        CHECK_FALSE(abc.compare("ab") <= 0);
        CHECK_FALSE(abc.compare("aba") <= 0);
        CHECK_FALSE(abc.compare("abab") <= 0);
    }

    SECTION("BasicString::compare(const char*) < 0")
    {
        CHECK(      abc.compare("ad") < 0);
        CHECK(      abc.compare("abd") < 0);
        CHECK(      abc.compare("abca") < 0);
        CHECK_FALSE(abc.compare("ab") < 0);
        CHECK_FALSE(abc.compare("aba") < 0);
        CHECK_FALSE(abc.compare("abab") < 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const char*) >= 0")
    {
        CHECK(      abc.compare(0, 3, "ab") >= 0);
        CHECK(      abc.compare(0, 3, "abb") >= 0);
        CHECK(      abc.compare(0, 3, "abc") >= 0);
        CHECK(      abc.compare(0, 3, "abab") >= 0);
        CHECK_FALSE(abc.compare(0, 3, "ac") >= 0);
        CHECK_FALSE(abc.compare(0, 3, "acb") >= 0);
        CHECK_FALSE(abc.compare(0, 3, "abcb") >= 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const char*) > 0")
    {
        CHECK(      abc.compare(0, 3, "ab") > 0);
        CHECK(      abc.compare(0, 3, "abb") > 0);
        CHECK(      abc.compare(0, 3, "abab") > 0);
        CHECK_FALSE(abc.compare(0, 3, "ac") > 0);
        CHECK_FALSE(abc.compare(0, 3, "acb") > 0);
        CHECK_FALSE(abc.compare(0, 3, "abcb") > 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const char*) <= 0")
    {
        CHECK(      abc.compare(0, 3, "ad") <= 0);
        CHECK(      abc.compare(0, 3, "abc") <= 0);
        CHECK(      abc.compare(0, 3, "abd") <= 0);
        CHECK(      abc.compare(0, 3, "abca") <= 0);
        CHECK_FALSE(abc.compare(0, 3, "ab") <= 0);
        CHECK_FALSE(abc.compare(0, 3, "aba") <= 0);
        CHECK_FALSE(abc.compare(0, 3, "abab") <= 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const char*) < 0")
    {
        CHECK(      abc.compare(0, 3, "ad") < 0);
        CHECK(      abc.compare(0, 3, "abd") < 0);
        CHECK(      abc.compare(0, 3, "abca") < 0);
        CHECK_FALSE(abc.compare(0, 3, "ab") < 0);
        CHECK_FALSE(abc.compare(0, 3, "aba") < 0);
        CHECK_FALSE(abc.compare(0, 3, "abab") < 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const BasicString&) >= 0")
    {
        CHECK(      abc.compare(0, 3, BasicString("ab")) >= 0);
        CHECK(      abc.compare(0, 3, BasicString("abb")) >= 0);
        CHECK(      abc.compare(0, 3, BasicString("abc")) >= 0);
        CHECK(      abc.compare(0, 3, BasicString("abab")) >= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("ac")) >= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("acb")) >= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("abcb")) >= 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const BasicString&) > 0")
    {
        CHECK(      abc.compare(0, 3, BasicString("ab")) > 0);
        CHECK(      abc.compare(0, 3, BasicString("abb")) > 0);
        CHECK(      abc.compare(0, 3, BasicString("abab")) > 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("ac")) > 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("acb")) > 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("abcb")) > 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const BasicString&) <= 0")
    {
        CHECK(      abc.compare(0, 3, BasicString("ad")) <= 0);
        CHECK(      abc.compare(0, 3, BasicString("abc")) <= 0);
        CHECK(      abc.compare(0, 3, BasicString("abd")) <= 0);
        CHECK(      abc.compare(0, 3, BasicString("abca")) <= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("ab")) <= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("aba")) <= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("abab")) <= 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const BasicString&) < 0")
    {
        CHECK(      abc.compare(0, 3, BasicString("ad")) < 0);
        CHECK(      abc.compare(0, 3, BasicString("abd")) < 0);
        CHECK(      abc.compare(0, 3, BasicString("abca")) < 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("ab")) < 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("aba")) < 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("abab")) < 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const char*, size_type) >= 0")
    {
        CHECK(      abc.compare(0, 3, "ab", 2) >= 0);
        CHECK(      abc.compare(0, 3, "abb", 3) >= 0);
        CHECK(      abc.compare(0, 3, "abc", 3) >= 0);
        CHECK(      abc.compare(0, 3, "abab", 4) >= 0);
        CHECK_FALSE(abc.compare(0, 3, "ac", 2) >= 0);
        CHECK_FALSE(abc.compare(0, 3, "acb", 3) >= 0);
        CHECK_FALSE(abc.compare(0, 3, "abcb", 4) >= 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const char*, size_type) > 0")
    {
        CHECK(      abc.compare(0, 3, "ab", 2) > 0);
        CHECK(      abc.compare(0, 3, "abb", 3) > 0);
        CHECK(      abc.compare(0, 3, "abab", 4) > 0);
        CHECK_FALSE(abc.compare(0, 3, "ac", 2) > 0);
        CHECK_FALSE(abc.compare(0, 3, "acb", 3) > 0);
        CHECK_FALSE(abc.compare(0, 3, "abcb", 4) > 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const char*, size_type) <= 0")
    {
        CHECK(      abc.compare(0, 3, "ad", 2) <= 0);
        CHECK(      abc.compare(0, 3, "abc", 3) <= 0);
        CHECK(      abc.compare(0, 3, "abd", 3) <= 0);
        CHECK(      abc.compare(0, 3, "abca", 4) <= 0);
        CHECK_FALSE(abc.compare(0, 3, "ab", 2) <= 0);
        CHECK_FALSE(abc.compare(0, 3, "aba", 3) <= 0);
        CHECK_FALSE(abc.compare(0, 3, "abab", 4) <= 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const char*, size_type) < 0")
    {
        CHECK(      abc.compare(0, 3, "ad", 2) < 0);
        CHECK(      abc.compare(0, 3, "abd", 3) < 0);
        CHECK(      abc.compare(0, 3, "abca", 4) < 0);
        CHECK_FALSE(abc.compare(0, 3, "ab", 2) < 0);
        CHECK_FALSE(abc.compare(0, 3, "aba", 3) < 0);
        CHECK_FALSE(abc.compare(0, 3, "abab", 4) < 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const BasicString&, size_type, size_type) >= 0")
    {
        CHECK(      abc.compare(0, 3, BasicString("ab"), 0, 2) >= 0);
        CHECK(      abc.compare(0, 3, BasicString("abb"), 0, 3) >= 0);
        CHECK(      abc.compare(0, 3, BasicString("abc"), 0, 3) >= 0);
        CHECK(      abc.compare(0, 3, BasicString("abab"), 0, 4) >= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("ac"), 0, 2) >= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("acb"), 0, 3) >= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("abcb"), 0, 4) >= 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const BasicString&, size_type, size_type) > 0")
    {
        CHECK(      abc.compare(0, 3, BasicString("ab"), 0, 2) > 0);
        CHECK(      abc.compare(0, 3, BasicString("abb"), 0, 3) > 0);
        CHECK(      abc.compare(0, 3, BasicString("abab"), 0, 4) > 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("ac"), 0, 2) > 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("acb"), 0, 3) > 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("abcb"), 0, 4) > 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const BasicString&, size_type, size_type) <= 0")
    {
        CHECK(      abc.compare(0, 3, BasicString("ad"), 0, 2) <= 0);
        CHECK(      abc.compare(0, 3, BasicString("abc"), 0, 3) <= 0);
        CHECK(      abc.compare(0, 3, BasicString("abd"), 0, 3) <= 0);
        CHECK(      abc.compare(0, 3, BasicString("abca"), 0, 4) <= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("ab"), 0, 2) <= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("aba"), 0, 3) <= 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("abab"), 0, 4) <= 0);
    }

    SECTION("BasicString::compare(size_type, size_type, const BasicString&, size_type, size_type) < 0")
    {
        CHECK(      abc.compare(0, 3, BasicString("ad"), 0, 2) < 0);
        CHECK(      abc.compare(0, 3, BasicString("abd"), 0, 3) < 0);
        CHECK(      abc.compare(0, 3, BasicString("abca"), 0, 4) < 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("ab"), 0, 2) < 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("aba"), 0, 3) < 0);
        CHECK_FALSE(abc.compare(0, 3, BasicString("abab"), 0, 4) < 0);
    }

}

TEST_CASE("BasicString::find", "[SWS_CORE], [SWS_CORE_03000]")
{
    /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    constexpr char sample[] = " the quick brown fox jumps over the lazy dog";
    BasicString haystack(sample);
    std::string example(sample);

    SECTION("BasicString::find(const BasicString&, size_type = 0) const noexcept")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find(BasicString(needle)) == example.find(std::string(needle)));
            CHECK(haystack.find(BasicString(needle), 3) == example.find(std::string(needle), 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find(BasicString("fox")) == example.find(std::string(needle)));
            CHECK(haystack.find(BasicString("fox"), 3) == example.find(std::string(needle), 3));
        }
    }

    SECTION("BasicString::find(const char*, size_type, size_type) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find(needle, 0, 3) == example.find(needle, 0, 3));
            CHECK(haystack.find(needle, 3, 3) == example.find(needle, 3, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find(needle, 0, 3) == example.find(needle, 0, 3));
            CHECK(haystack.find(needle, 3, 3) == example.find(needle, 3, 3));
        }
    }

    SECTION("BasicString::find(const char*, size_type = 0) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find(needle) == example.find(needle));
            CHECK(haystack.find(needle, 3) == example.find(needle, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find(needle) == example.find(needle));
            CHECK(haystack.find(needle, 3) == example.find(needle, 3));
        }
    }

    SECTION("BasicString::find(const char*, size_type = 0) const")
    {
        {
            const char needle = 't';
            CHECK(haystack.find(needle) == example.find(needle));
            CHECK(haystack.find(needle, 3) == example.find(needle, 3));
        }
        {
            const char needle = 'x';
            CHECK(haystack.find(needle) == example.find(needle));
            CHECK(haystack.find(needle, 3) == example.find(needle, 3));
        }
    }
}

TEST_CASE("BasicString::rfind", "[SWS_CORE], [SWS_CORE_03000]")
{
     /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    constexpr char sample[] = " the quick brown fox jumps over the lazy dog";
    BasicString haystack(sample);
    std::string example(sample);

    SECTION("BasicString::rfind(const BasicString&, size_type = npos) const noexcept")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.rfind(BasicString(needle)) == example.rfind(std::string(needle)));
            CHECK(haystack.rfind(BasicString(needle), 1) == example.rfind(std::string(needle), 1));
            CHECK(haystack.rfind(BasicString(needle), 0) == example.rfind(std::string(needle), 0));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.rfind(BasicString(needle)) == example.rfind(std::string(needle)));
            CHECK(haystack.rfind(BasicString(needle), 17) == example.rfind(std::string(needle), 17));
            CHECK(haystack.rfind(BasicString(needle), 16) == example.rfind(std::string(needle), 16));
        }
    }

    SECTION("BasicString::rfind(const char*, size_type, size_type) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.rfind(needle, 0, 3) == example.rfind(needle, 0, 3));
            CHECK(haystack.rfind(needle, 3, 3) == example.rfind(needle, 3, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.rfind(needle,  0, 3) == example.rfind(needle,  0, 3));
            CHECK(haystack.rfind(needle, 17, 3) == example.rfind(needle, 17, 3));
        }
    }

    SECTION("BasicString::rfind(const char*, size_type = npos) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.rfind(needle) == example.rfind(needle));
            CHECK(haystack.rfind(needle, 3) == example.rfind(needle, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.rfind(needle) == example.rfind(needle));
            CHECK(haystack.rfind(needle, 3) == example.rfind(needle, 3));
        }
    }

    SECTION("BasicString::rfind(const char*, size_type = 0) const")
    {
        {
            const char needle = 't';
            CHECK(haystack.rfind(needle) == example.rfind(needle));
            CHECK(haystack.rfind(needle, 3) == example.rfind(needle, 3));
        }
        {
            const char needle = 'x';
            CHECK(haystack.rfind(needle) == example.rfind(needle));
            CHECK(haystack.rfind(needle, 3) == example.rfind(needle, 3));
        }
    }
}

TEST_CASE("BasicString::find_first_of", "[SWS_CORE], [SWS_CORE_03000]")
{
 /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    constexpr char sample[] = " the quick brown fox jumps over the lazy dog";
    BasicString haystack(sample);
    std::string example(sample);

    SECTION("BasicString::find_first_of(const BasicString&, size_type = 0) const noexcept")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find_first_of(BasicString(needle)) == example.find_first_of(std::string(needle)));
            CHECK(haystack.find_first_of(BasicString(needle), 3) == example.find_first_of(std::string(needle), 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_first_of(BasicString(needle)) == example.find_first_of(std::string(needle)));
            CHECK(haystack.find_first_of(BasicString(needle), 3) == example.find_first_of(std::string(needle), 3));
        }
    }

    SECTION("BasicString::find_first_of(const char*, size_type, size_type) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find_first_of(needle, 0, 3) == example.find_first_of(needle, 0, 3));
            CHECK(haystack.find_first_of(needle, 3, 3) == example.find_first_of(needle, 3, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_first_of(needle, 3, 3) == example.find_first_of(needle, 3, 3));
            CHECK(haystack.find_first_of(needle, 0, 3) == example.find_first_of(needle, 0, 3));
        }
    }

    SECTION("BasicString::find_first_of(const char*, size_type = 0) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find_first_of(needle) == example.find_first_of(needle));
            CHECK(haystack.find_first_of(needle, 3) == example.find_first_of(needle, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_first_of(needle) == example.find_first_of(needle));
            CHECK(haystack.find_first_of(needle, 3) == example.find_first_of(needle, 3));
        }
    }

    SECTION("BasicString::find_first_of(const char*, size_type = 0) const")
    {
        {
            const char needle = 't';
            CHECK(haystack.find_first_of(needle) == example.find_first_of(needle));
            CHECK(haystack.find_first_of(needle, 3) == example.find_first_of(needle, 3));
        }
        {
            const char needle = 'x';
            CHECK(haystack.find_first_of(needle) == example.find_first_of(needle));
            CHECK(haystack.find_first_of(needle, 3) == example.find_first_of(needle, 3));
        }
    }
}

TEST_CASE("BasicString::find_last_of", "[SWS_CORE], [SWS_CORE_03000]")
{
 /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    constexpr char sample[] = " the quick brown fox jumps over the lazy dog";
    BasicString haystack(sample);
    std::string example(sample);

    SECTION("BasicString::find_last_of(const BasicString&, size_type = 0) const noexcept")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find_last_of(BasicString(needle)) == example.find_last_of(std::string(needle)));
            CHECK(haystack.find_last_of(BasicString(needle), 3) == example.find_last_of(std::string(needle), 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_last_of(BasicString(needle)) == example.find_last_of(std::string(needle)));
            CHECK(haystack.find_last_of(BasicString(needle), 3) == example.find_last_of(std::string(needle), 3));
        }
    }

    SECTION("BasicString::find_last_of(const char*, size_type, size_type) const")
    {
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_last_of(needle, 45, 3) == example.find_last_of(needle, 45, 3));
            CHECK(haystack.find_last_of(needle,  3, 3) == example.find_last_of(needle,  3, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_last_of(needle,  3, 3) == example.find_last_of(needle,  3, 3));
            CHECK(haystack.find_last_of(needle, 32, 3) == example.find_last_of(needle, 32, 3));
        }
    }

    SECTION("BasicString::find_last_of(const char*, size_type = 0) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find_last_of(needle) == example.find_last_of(needle));
            CHECK(haystack.find_last_of(needle, 3) == example.find_last_of(needle, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_last_of(needle) == example.find_last_of(needle));
            CHECK(haystack.find_last_of(needle, 3) == example.find_last_of(needle, 3));
        }
    }

    SECTION("BasicString::find_last_of(const char*, size_type = 0) const")
    {
        {
            const char needle = 't';
            CHECK(haystack.find_last_of(needle) == example.find_last_of(needle));
            CHECK(haystack.find_last_of(needle, 3) == example.find_last_of(needle, 3));
        }
        {
            const char needle = 'x';
            CHECK(haystack.find_last_of(needle) == example.find_last_of(needle));
            CHECK(haystack.find_last_of(needle, 3) == example.find_last_of(needle, 3));
        }
    }
}

TEST_CASE("BasicString::find_first_not_of", "[SWS_CORE], [SWS_CORE_03000]")
{
     /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    constexpr char sample[] = " the quick brown fox jumps over the lazy dog";
    BasicString haystack(sample);
    std::string example(sample);

    SECTION("BasicString::find_first_not_of(const BasicString&, size_type = 0) const noexcept")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find_first_not_of(BasicString(needle)) == example.find_first_not_of(std::string(needle)));
            CHECK(haystack.find_first_not_of(BasicString(needle), 3) == example.find_first_not_of(std::string(needle), 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_first_not_of(BasicString(needle)) == example.find_first_not_of(std::string(needle)));
            CHECK(haystack.find_first_not_of(BasicString(needle), 3) == example.find_first_not_of(std::string(needle), 3));
        }
    }

    SECTION("BasicString::find_first_not_of(const char*, size_type, size_type) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find_first_not_of(needle, 0, 3) == example.find_first_not_of(needle, 0, 3));
            CHECK(haystack.find_first_not_of(needle, 3, 3) == example.find_first_not_of(needle, 3, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_first_not_of(needle, 3, 3) == example.find_first_not_of(needle, 3, 3));
            CHECK(haystack.find_first_not_of(needle, 0, 3) == example.find_first_not_of(needle, 0, 3));
        }
    }

    SECTION("BasicString::find_first_not_of(const char*, size_type = 0) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find_first_not_of(needle) == example.find_first_not_of(needle));
            CHECK(haystack.find_first_not_of(needle, 3) == example.find_first_not_of(needle, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_first_not_of(needle) == example.find_first_not_of(needle));
            CHECK(haystack.find_first_not_of(needle, 3) == example.find_first_not_of(needle, 3));
        }
    }

    SECTION("BasicString::find_first_of(const char*, size_type = 0) const")
    {
        {
            const char needle = 't';
            CHECK(haystack.find_first_not_of(needle) == example.find_first_not_of(needle));
            CHECK(haystack.find_first_not_of(needle, 3) == example.find_first_not_of(needle, 3));
        }
        {
            const char needle = 'x';
            CHECK(haystack.find_first_not_of(needle) == example.find_first_not_of(needle));
            CHECK(haystack.find_first_not_of(needle, 3) == example.find_first_not_of(needle, 3));
        }
    }
}

TEST_CASE("BasicString::find_last_not_of", "[SWS_CORE], [SWS_CORE_03000]")
{
 /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    constexpr char sample[] = " the quick brown fox jumps over the lazy dog";
    BasicString haystack(sample);
    std::string example(sample);

    SECTION("BasicString::find_last_not_of(const BasicString&, size_type = 0) const noexcept")
    {
        CHECK(haystack.find_last_not_of(BasicString("the quick brown fox jumps over the lazy d")) == example.find_last_not_of(std::string("the quick brown fox jumps over the lazy d")));
        CHECK(haystack.find_last_not_of(BasicString("the"), 3) == example.find_last_not_of(std::string("the"), 3));
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_last_not_of(BasicString(needle)) == example.find_last_not_of(std::string(needle)));
            CHECK(haystack.find_last_not_of(BasicString(needle), 3) == example.find_last_not_of(std::string(needle), 3));
        }
    }

    SECTION("BasicString::find_last_not_of(const char*, size_type, size_type) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find_last_not_of(needle, 45, 3) == example.find_last_not_of(needle, 45, 3));
            CHECK(haystack.find_last_not_of(needle,  3, 3) == example.find_last_not_of(needle,  3, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_last_not_of(needle,  3, 3) == example.find_last_not_of(needle,  3, 3));
            CHECK(haystack.find_last_not_of(needle, 32, 3) == example.find_last_not_of(needle, 32, 3));
        }
    }

    SECTION("BasicString::find_last_not_of(const char*, size_type = 0) const")
    {
        {
            constexpr char needle[] = "the";
            CHECK(haystack.find_last_not_of(needle) == example.find_last_not_of(needle));
            CHECK(haystack.find_last_not_of(needle, 3) == example.find_last_not_of(needle, 3));
        }
        {
            constexpr char needle[] = "fox";
            CHECK(haystack.find_last_not_of(needle) == example.find_last_not_of(needle));
            CHECK(haystack.find_last_not_of(needle, 3) == example.find_last_not_of(needle, 3));
        }
    }

    SECTION("BasicString::find_last_not_of(const char*, size_type = 0) const")
    {
        {
            const char needle = 't';
            CHECK(haystack.find_last_not_of(needle) == example.find_last_not_of(needle));
            CHECK(haystack.find_last_not_of(needle, 3) == example.find_last_not_of(needle, 3));
        }
        {
            const char needle = 'x';
            CHECK(haystack.find_last_not_of(needle) == example.find_last_not_of(needle));
            CHECK(haystack.find_last_not_of(needle, 3) == example.find_last_not_of(needle, 3));
        }
    }
}

TEST_CASE("BasicString::append", "[SWS_CORE], [SWS_CORE_03000]")
{
 /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    SECTION("BasicString::append(const BasicString&)")
    {
        BasicString bs("qwe");
        std::string str("qwe");

        BasicString bs_rty("rty");
        std::string str_rty("rty");

        BasicString bs_asdf("asdf");
        std::string str_asdf("asdf");

        bs.append(bs_rty).append(bs_asdf);
        str.append(str_rty).append(str_asdf);

        CHECK(bs == str.c_str());
    }

    SECTION("BasicString::append(BasicString&&)")
    {
        BasicString bs("qwe");
        std::string str("qwe");

        bs.append(BasicString("rty")).append(BasicString("asdf"));
        str.append(std::string("rty")).append(std::string("asdf"));

        CHECK(bs == str.c_str());
    }

    SECTION("BasicString::append(const BasicString&, size_type, size_type)")
    {
        BasicString bs("qwe");
        std::string str("qwe");

        constexpr char rty[] = "   rty   ";
        constexpr char asdf[] = " asdf ";

        bs.assign(BasicString(rty), 3, 3).append(BasicString(asdf), 1, 4);
        str.assign(std::string(rty), 3, 3).append(std::string(asdf), 1, 4);

        CHECK(bs == str.c_str());
    }

    SECTION("BasicString::append(const char*, size_type)")
    {
        BasicString bs("qwe");
        std::string str("qwe");

        bs.append("rtyuiop", 3).append("asdfgh", 4);
        str.append("rtyuiop", 3).append("asdfgh", 4);

        CHECK(bs == str.c_str());
    }

    SECTION("BasicString::append(const char*)")
    {
        BasicString bs("qwe");
        std::string str("qwe");

        bs.append("rty").append("asdf");
        str.append("rty").append("asdf");

        CHECK(bs == str.c_str());
    }

    SECTION("BasicString::append(size_type, char)")
    {
        typedef std::size_t size_type;

        BasicString bs("qwert");
        std::string str("qwert");

        // type cast to size_type due to type deduction ambiguity

        bs.append(size_type(2), 'y').append(size_type(3), '.');
        str.append(size_type(2), 'y').append(size_type(3), '.');

        CHECK(bs == str.c_str());
    }

    SECTION("BasicString::append(std::initializer_list<char>)")
    {
        BasicString bs("qwe");
        std::string str("qwe");

        bs.append({'r', 't', 'y'}).append({'a', 's', 'd', 'f'});
        str.append({'r', 't', 'y'}).append({'a', 's', 'd', 'f'});

        CHECK(bs == str.c_str());
    }
}

TEST_CASE("BasicString::assign", "[SWS_CORE], [SWS_CORE_03000]")
{
 /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    SECTION("BasicString::assign(const BasicString&)")
    {
        BasicString str;
        BasicString qwerty("qwerty");

        REQUIRE(str.empty());
        str.assign(qwerty);
        CHECK(str == qwerty);
    }

    SECTION("BasicString::assign(BasicString&&)")
    {
        BasicString str;

        REQUIRE(str.empty());
        str.assign(BasicString("qwerty"));
        CHECK(str == "qwerty");
    }

    SECTION("BasicString::assign(const BasicString&, size_type, size_type)")
    {
        BasicString str;
        BasicString qwerty(" qwertyuiop");

        REQUIRE(str.empty());
        str.assign(qwerty, 1, 6);
        CHECK(str == "qwerty");
    }

    SECTION("BasicString::assign(const char*, size_type)")
    {
        BasicString str;

        REQUIRE(str.empty());
        str.assign("qwerty   ", 6);
        CHECK(str == "qwerty");
    }

    SECTION("BasicString::assign(const char*)")
    {
        BasicString str;

        REQUIRE(str.empty());
        str.assign("qwerty");
        CHECK(str == "qwerty");
    }

    SECTION("BasicString::assign(InputIterator, InputIterator)")
    {
        std::string example(" the quick brown fox jumps over the lazy dog");
        BasicString str;

        REQUIRE(str.empty());

        auto begin = example.begin();
        auto end = example.begin();
        std::advance(begin, 1);
        std::advance(end, 4);

        str.assign(begin, end);

        CHECK(str == "the");
    }

    SECTION("BasicString::assign(std::initializer_list<char>)")
    {
        BasicString str;

        REQUIRE(str.empty());
        str.assign( { 'q', 'w', 'e', 'r', 't', 'y' } );
        CHECK(str == "qwerty");
    }
}

TEST_CASE("BasicString::insert", "[SWS_CORE], [SWS_CORE_03000]")
{
 /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    SECTION("BasicString::insert(size_type, const BasicString&)")
    {
        constexpr char text[] = "lorum";
        constexpr char ins[] = "em ips";
        BasicString bs_text(text);
        std::string str_text(text);
        BasicString bs_ins(ins);
        std::string str_ins(ins);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        bs_text.insert(3, bs_ins);
        str_text.insert(3, str_ins);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "lorem ipsum");
    }

    SECTION("BasicString::insert(size_type, const BasicString&, size_type, size_type)")
    {
        constexpr char text[] = "lorum";
        constexpr char ins[] = "eem ipsil";
        BasicString bs_text(text);
        std::string str_text(text);
        BasicString bs_ins(ins);
        std::string str_ins(ins);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        bs_text.insert(3, bs_ins, 1, 6);
        str_text.insert(3, str_ins, 1, 6);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "lorem ipsum");
    }

    SECTION("BasicString::insert(size_type, const char*, size_type)")
    {
        constexpr char text[] = "lorum";
        BasicString bs_text(text);
        std::string str_text(text);
        constexpr char ins[] = "em ips ";

        REQUIRE(bs_text == "lorum");
        REQUIRE(str_text == "lorum");

        bs_text.insert(3, ins, 6);
        str_text.insert(3, ins, 6);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "lorem ipsum");
    }

    SECTION("BasicString::insert(size_type, const char*)")
    {
        constexpr char text[] = "lorum";
        BasicString bs_text(text);
        std::string str_text(text);
        constexpr char ins[] = "em ips";

        REQUIRE(bs_text == "lorum");
        REQUIRE(str_text == "lorum");

        bs_text.insert(3, ins);
        str_text.insert(3, ins);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "lorem ipsum");
    }

    SECTION("BasicString::insert(size_type, const char*, size_type)")
    {
        constexpr char text[] = "lorum";
        BasicString bs_text(text);
        std::string str_text(text);
        constexpr char ins[] = "em ips ";

        REQUIRE(bs_text == "lorum");
        REQUIRE(str_text == "lorum");

        bs_text.insert(3, ins, 6);
        str_text.insert(3, ins, 6);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "lorem ipsum");
    }

    SECTION("BasicString::insert(size_type, size_type, char)")
    {
        typedef std::size_t size_type;

        constexpr char text[] = "qwerty";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == "qwerty");
        REQUIRE(str_text == "qwerty");

        bs_text.insert(size_type(6), size_type(3), '.');
        str_text.insert(size_type(6), size_type(3), '.');

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "qwerty...");
    }

    SECTION("BasicString::insert(const_iterator, char)")
    {
        constexpr char text[] = "qerty";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        auto bs_iter = bs_text.cbegin();
        auto str_iter = str_text.cbegin();
        std::advance(bs_iter, 1);
        std::advance(str_iter, 1);

        bs_text.insert(bs_iter, 'w');
        str_text.insert(str_iter, 'w');

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "qwerty");
    }

    SECTION("BasicString::insert(const_iterator, size_type, char)")
    {
        constexpr char text[] = "qwerty";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        auto bs_iter = bs_text.cbegin();
        auto str_iter = str_text.cbegin();
        std::advance(bs_iter, 3);
        std::advance(str_iter, 3);

        bs_text.insert(bs_iter, 2, 'r');
        str_text.insert(str_iter, 2, 'r');

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "qwerrrty");
    }

    SECTION("BasicString::insert(const_iterator, InputIterator, InputIterator)")
    {
        constexpr char text[] = "qy";
        constexpr char ins[] = "qwerty";
        BasicString bs_text(text);
        std::string str_text(text);
        BasicString bs_ins(ins);
        std::string str_ins(ins);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);
        REQUIRE(bs_ins == ins);
        REQUIRE(str_ins == ins);

        auto bs_iter = bs_text.cbegin();
        auto str_iter = str_text.cbegin();
        std::advance(bs_iter, 1);
        std::advance(str_iter, 1);

        auto bs_begin = bs_ins.begin();
        auto str_begin = str_ins.begin();
        std::advance(bs_begin, 1);
        std::advance(str_begin, 1);

        auto bs_end = bs_ins.begin();
        auto str_end = str_ins.begin();
        std::advance(bs_end, 5);
        std::advance(str_end, 5);

        bs_text.insert(bs_iter, bs_begin, bs_end);
        str_text.insert(str_iter, str_begin, str_end);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "qwerty");
    }

    SECTION("BasicString::insert(const_iterator, std::initializer_list<char>)")
    {
        constexpr char text[] = "lorum";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        auto bs_iter = bs_text.cbegin();
        auto str_iter = str_text.cbegin();
        std::advance(bs_iter, 3);
        std::advance(str_iter, 3);

        bs_text.insert(bs_iter, {'e', 'm', ' ', 'i', 'p', 's' });
        str_text.insert(str_iter, {'e', 'm', ' ', 'i', 'p', 's' });

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "lorem ipsum");
    }
}

TEST_CASE("BasicString::erase", "[SWS_CORE], [SWS_CORE_03000]")
{
 /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    SECTION("BasicString::erase(size_type, size_type = npos)")
    {
        constexpr char text[] = "qweasdrty";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        bs_text.erase(3, 3);
        str_text.erase(3, 3);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "qwerty");
    }

    SECTION("BasicString::erase(const_iterator)")
    {
        constexpr char text[] = "qwertyy";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        auto bs_iter = bs_text.cbegin();
        auto str_iter = str_text.cbegin();
        std::advance(bs_iter, 6);
        std::advance(str_iter, 6);

        bs_text.erase(bs_iter);
        str_text.erase(str_iter);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "qwerty");
    }

    SECTION("BasicString::erase(const_iterator, const_iterator)")
    {
        constexpr char text[] = "qweasdfrty";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        auto bs_begin = bs_text.cbegin();
        auto str_begin = str_text.cbegin();

        std::advance(bs_begin, 3);
        std::advance(str_begin, 3);

        auto bs_end = bs_text.cbegin();
        auto str_end = str_text.cbegin();

        std::advance(bs_end, 3+4);
        std::advance(str_end, 3+4);

        bs_text.erase(bs_begin, bs_end);
        str_text.erase(str_begin, str_end);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "qwerty");
    }
}

TEST_CASE("BasicString::replace", "[SWS_CORE], [SWS_CORE_03000]")
{
 /*
    Comparing results to the std::string's equivalents due to SWS_CORE_03000 requirement:

    "All members of this class and supporting constructs (such as global relational operators)
    shall behave identical to those of std::basic_string in header <string>
    from [5, the C++11 standard] section 21.3, except that the default value for the Allocator
    template argument is implementation-defined.""
    */

    using core::BasicString;

    SECTION("BasicString::replace(size_type, size_type, const BasicString&)")
    {
        constexpr char text[] = "the quick silvery fox jumps over the lazy dog";
        constexpr char replacement[] = "brown";
        BasicString bs_text(text);
        std::string str_text(text);
        BasicString bs_replacement(replacement);
        std::string str_replacement(replacement);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);
        REQUIRE(bs_replacement == replacement);
        REQUIRE(str_replacement == replacement);

        bs_text.replace(10, 7, bs_replacement);
        str_text.replace(10, 7, str_replacement);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "the quick brown fox jumps over the lazy dog");
    }

    SECTION("BasicString::replace(size_type, size_type, const BasicString&, size_type, size_type)")
    {
        constexpr char text[] = "the quick silvery fox jumps over the lazy dog";
        constexpr char replacement[] = "debrowning agent";
        BasicString bs_text(text);
        std::string str_text(text);
        BasicString bs_replacement(replacement);
        std::string str_replacement(replacement);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);
        REQUIRE(bs_replacement == replacement);
        REQUIRE(str_replacement == replacement);

        bs_text.replace(10, 7, bs_replacement, 2, 5);
        str_text.replace(10, 7, str_replacement, 2, 5);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "the quick brown fox jumps over the lazy dog");
    }

    SECTION("BasicString::replace(size_type, size_type, const char*, size_type)")
    {
        constexpr char text[] = "the quick silvery fox jumps over the lazy dog";
        constexpr char replacement[] = "browning";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        bs_text.replace(10, 7, replacement, 5);
        str_text.replace(10, 7, replacement, 5);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "the quick brown fox jumps over the lazy dog");
    }

    SECTION("BasicString::replace(size_type, size_type, const char*)")
    {
        constexpr char text[] = "the quick silvery fox jumps over the lazy dog";
        constexpr char replacement[] = "brown";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        bs_text.replace(10, 7, replacement);
        str_text.replace(10, 7, replacement);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "the quick brown fox jumps over the lazy dog");
    }

    SECTION("BasicString::replace(size_type, size_type, size_type, char)")
    {
        typedef std::size_t size_type;

        constexpr char text[] = "wuud";
        constexpr char replacement = 'o';
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        bs_text.replace(size_type(1), size_type(2), size_type(2), replacement);
        str_text.replace(size_type(1), size_type(2), size_type(2), replacement);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "wood");
    }

    SECTION("BasicString::replace(const_iterator, const_iterator, const BasicString&)")
    {
        constexpr char text[] = "the quick silvery fox jumps over the lazy dog";
        constexpr char replacement[] = "brown";
        BasicString bs_text(text);
        std::string str_text(text);
        BasicString bs_replacement(replacement);
        std::string str_replacement(replacement);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);
        REQUIRE(bs_replacement == replacement);
        REQUIRE(str_replacement == replacement);

        auto bs_begin = bs_text.cbegin();
        auto bs_end = bs_text.cbegin();
        std::advance(bs_begin, 10);
        std::advance(bs_end, 17);
        auto str_begin = str_text.cbegin();
        auto str_end = str_text.cbegin();
        std::advance(str_begin, 10);
        std::advance(str_end, 17);

        bs_text.replace(bs_begin, bs_end, bs_replacement);
        str_text.replace(str_begin, str_end, str_replacement);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "the quick brown fox jumps over the lazy dog");
    }

    SECTION("BasicString::replace(const_iterator, const_iterator, const char*, size_type)")
    {
        constexpr char text[] = "the quick silvery fox jumps over the lazy dog";
        constexpr char replacement[] = "browning agent";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        auto bs_begin = bs_text.cbegin();
        auto bs_end = bs_text.cbegin();
        std::advance(bs_begin, 10);
        std::advance(bs_end, 17);
        auto str_begin = str_text.cbegin();
        auto str_end = str_text.cbegin();
        std::advance(str_begin, 10);
        std::advance(str_end, 17);

        bs_text.replace(bs_begin, bs_end, replacement, 5);
        str_text.replace(str_begin, str_end, replacement, 5);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "the quick brown fox jumps over the lazy dog");
    }

    SECTION("BasicString::replace(const_iterator, const_iterator, const char*)")
    {
        constexpr char text[] = "the quick silvery fox jumps over the lazy dog";
        constexpr char replacement[] = "brown";
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        auto bs_begin = bs_text.cbegin();
        auto bs_end = bs_text.cbegin();
        std::advance(bs_begin, 10);
        std::advance(bs_end, 17);
        auto str_begin = str_text.cbegin();
        auto str_end = str_text.cbegin();
        std::advance(str_begin, 10);
        std::advance(str_end, 17);

        bs_text.replace(bs_begin, bs_end, replacement);
        str_text.replace(str_begin, str_end, replacement);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "the quick brown fox jumps over the lazy dog");
    }

    SECTION("BasicString::replace(const_iterator, const_iterator, size_type, char)")
    {
        constexpr char text[] = "wuud";
        constexpr char replacement = 'o';
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        auto bs_begin = bs_text.cbegin();
        auto bs_end = bs_text.cbegin();
        std::advance(bs_begin, 1);
        std::advance(bs_end, 3);
        auto str_begin = str_text.cbegin();
        auto str_end = str_text.cbegin();
        std::advance(str_begin, 1);
        std::advance(str_end, 3);

        bs_text.replace(bs_begin, bs_end, 2, replacement);
        str_text.replace(str_begin, str_end, 2, replacement);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "wood");
    }

    SECTION("BasicString::replace(const_iterator, const_iterator, InputIterator, InputIterator)")
    {
        constexpr char text[] = "the quick silvery fox jumps over the lazy dog";
        constexpr char replacement[] = "debrowning agent";
        BasicString bs_text(text);
        std::string str_text(text);
        BasicString bs_replacement(replacement);
        std::string str_replacement(replacement);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);
        REQUIRE(bs_replacement == replacement);
        REQUIRE(str_replacement == replacement);

        auto bs_begin = bs_text.cbegin();
        auto bs_end = bs_text.cbegin();
        std::advance(bs_begin, 10);
        std::advance(bs_end, 17);
        auto str_begin = str_text.cbegin();
        auto str_end = str_text.cbegin();
        std::advance(str_begin, 10);
        std::advance(str_end, 17);

        auto bs_replacement_begin = bs_replacement.cbegin();
        auto bs_replacement_end = bs_replacement.cbegin();
        std::advance(bs_replacement_begin, 2);
        std::advance(bs_replacement_end, 7);
        auto str_replacement_begin = str_replacement.cbegin();
        auto str_replacement_end = str_replacement.cbegin();
        std::advance(str_replacement_begin, 2);
        std::advance(str_replacement_end, 7);

        bs_text.replace(bs_begin, bs_end, bs_replacement_begin, bs_replacement_end);
        str_text.replace(str_begin, str_end, str_replacement_begin, str_replacement_end);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "the quick brown fox jumps over the lazy dog");
    }

    SECTION("BasicString::replace(const_iterator, const_iterator, std::initialize_list<char>)")
    {
        constexpr char text[] = "the quick silvery fox jumps over the lazy dog";
        std::initializer_list<char> replacement = { 'b', 'r', 'o', 'w', 'n' };
        BasicString bs_text(text);
        std::string str_text(text);

        REQUIRE(bs_text == text);
        REQUIRE(str_text == text);

        auto bs_begin = bs_text.cbegin();
        auto bs_end = bs_text.cbegin();
        std::advance(bs_begin, 10);
        std::advance(bs_end, 17);
        auto str_begin = str_text.cbegin();
        auto str_end = str_text.cbegin();
        std::advance(str_begin, 10);
        std::advance(str_end, 17);

        bs_text.replace(bs_begin, bs_end, replacement);
        str_text.replace(str_begin, str_end, replacement);

        CHECK(bs_text == str_text.c_str());
        CHECK(bs_text == "the quick brown fox jumps over the lazy dog");
    }
}

TEST_CASE("BasicString::swap", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString a("a");
    BasicString b("b");

    REQUIRE(a == "a");
    REQUIRE(b == "b");

    a.swap(b);

    CHECK(a == "b");
    CHECK(b == "a");
}

TEST_CASE("BasicString::copy", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString str("qwerty");
    char cpy[7] = { '\0' };

    REQUIRE(str == "qwerty");
    REQUIRE(str != cpy);

    str.copy(cpy, 6, 0);

    CHECK(str == cpy);
}

TEST_CASE("BasicString::pop_back", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString bs_text("qwerty");

    REQUIRE(bs_text == "qwerty");

    bs_text.pop_back();

    CHECK(bs_text == "qwert");
}

TEST_CASE("BasicString::push_back", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString bs_text("qwert");

    REQUIRE(bs_text == "qwert");

    bs_text.push_back('y');

    CHECK(bs_text == "qwerty");
}

TEST_CASE("BasicString::c_str", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString bs_text("qwerty");

    REQUIRE(bs_text == "qwerty");

    CHECK('\0' == bs_text.c_str()[bs_text.size()]);
    CHECK(bs_text.size() == std::strlen(bs_text.c_str()));
    CHECK(std::strcmp(bs_text.c_str(), "qwerty") == 0);
}

TEST_CASE("BasicString::data", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString bs_text("qwerty");

    REQUIRE(bs_text == "qwerty");

    CHECK('\0' == bs_text.data()[bs_text.size()]);
    CHECK(bs_text.size() == std::strlen(bs_text.data()));
    CHECK(std::strcmp(bs_text.data(), "qwerty") == 0);
}

TEST_CASE("BasicString::clear", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString bs_text("qwerty");

    REQUIRE(bs_text == "qwerty");

    bs_text.clear();

    CHECK(bs_text.empty());
}

TEST_CASE("BasicString::empty", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    BasicString bs_text;

    CHECK(bs_text.empty());

    bs_text = "qwerty";

    CHECK_FALSE(bs_text.empty());
}

TEST_CASE("BasicString::get_allocator", "[SWS_CORE], [SWS_CORE_03000]")
{
    using core::BasicString;

    core::Allocator<char> alloc;
    BasicString bs_text(alloc);

    CHECK(bs_text.get_allocator() == alloc);
}
