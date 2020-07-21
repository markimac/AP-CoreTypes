#include <catch2/catch.hpp>

#include "ara/core/map.h"

TEST_CASE("Map can be constructed / insert / at",
          "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<std::string, int> map;

    map.insert({"first", 1});
    int x = map.at("first");

    CHECK(x == 1);
}

TEST_CASE("operator[]", "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<std::string, int> map;

    map.insert({"first", 1});

    CHECK(map["first"] == 1);
}

TEST_CASE("begin / end", "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<int, int> map;

    map[0] = 0;
    map[1] = 1;
    map[2] = 2;

    int i = 0;
    for (auto it = map.begin(); it != map.end(); ++it)
    { CHECK(it->second == i++); }
}

TEST_CASE("rbegin / rend", "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<int, int> map;

    map[0] = 2;
    map[1] = 1;
    map[2] = 0;

    int i = 0;
    for (auto it = map.rbegin(); it != map.rend(); ++it)
    { CHECK(it->second == i++); }
}

TEST_CASE("size / empty / erase", "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<std::string, int> map;

    map.insert({"first", 1});
    CHECK(map.empty() == false);
    CHECK(map.size() == 1);

    map.erase(map.begin(), map.end());
    CHECK(map.empty() == true);
}

TEST_CASE("clear", "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<std::string, int> map;

    map.insert({"first", 1});
    map.clear();
    CHECK(map.empty() == true);
}

TEST_CASE("emplace", "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<std::string, int> map;

    map.emplace(std::make_pair("first", 1));
    map.emplace("second", 2);
    CHECK(map["first"] == 1);
    CHECK(map["second"] == 2);
}

TEST_CASE("emplace_hint", "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<int, int> map;

    map[0] = 0;
    map[1] = 1;
    map[2] = 2;

    auto it = map.emplace_hint(map.end(), 3, 3);

    CHECK(it->second == 3);
}

TEST_CASE("count / find", "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<int, int> map;

    map[0] = 0;
    map[1] = 1;
    map[2] = 2;

    CHECK(map.count(0) == 1);
    CHECK(map.count(3) == 0);
    CHECK(map.find(1)->second == 1);
}

TEST_CASE("equal_range", "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<char, int> map;

    map['a'] = 0;
    map['b'] = 1;
    map['c'] = 2;

    CHECK(map.equal_range('b').first->second == 1);
    CHECK(map.equal_range('b').second->second == 2);
}

TEST_CASE("lower_bound / upper_bound", "[SWS_CORE], [SWS_CORE_01400]")
{
    ara::core::Map<int, int> map;

    map[0] = 0;
    map[2] = 1;
    map[4] = 2;

    CHECK(map.lower_bound(1)->second == 1);
    CHECK(map.upper_bound(3)->second == 2);
}

TEST_CASE("key_comp", "[SWS_CORE], [SWS_CORE_01400]")
{
    struct NewCmp
    {
        bool operator()(const int lhs, const int rhs) const
        {
            return lhs < rhs;
        }
    };

    ara::core::Map<int, int, NewCmp> map = {{0, 0}, {2, 1}, {4, 2}};
    auto                             cmp = map.key_comp();

    int  max_key = map.end()->first;
    auto it      = map.begin();
    int  i       = 0;

    while (cmp((*it++).first, max_key)) { i++; }

    CHECK(i == 2);
}

TEST_CASE("value_comp", "[SWS_CORE], [SWS_CORE_01400]")
{
    struct NewCmp
    {
        bool operator()(const int lhs, const int rhs) const
        {
            return lhs < rhs;
        }
    };

    ara::core::Map<int, int, NewCmp> map = {{0, 0}, {2, 1}, {4, 2}};
    auto                             cmp = map.value_comp();

    const std::pair<int, int> max_val = {1, 1};
    auto                      it      = map.begin();
    int                       i       = 0;

    while (cmp((*it++), max_val)) { i++; }

    CHECK(i == 1);
}

TEST_CASE("swap", "[SWS_CORE], [SWS_CORE_01496]")
{
    ara::core::Map<char, int> p = {{'a', 0}};
    ara::core::Map<char, int> q = {{'a', 1}};

    ara::core::swap(p, q);

    CHECK(p['a'] == 1);
    CHECK(q['a'] == 0);
}
