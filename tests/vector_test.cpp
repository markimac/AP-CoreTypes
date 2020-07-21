#include <catch2/catch.hpp>

#include "ara/core/vector.h"

TEST_CASE("Constructs an empty vector", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector;

    CHECK(vector.size() == 0);
}

TEST_CASE("Constructs a vector with n value-initialized elements",
          "[SWS_CORE], [SWS_CORE_01301]")
{
    std::size_t            size = 5;
    ara::core::Vector<int> vector(size);

    CHECK(vector.size() == size);
}

TEST_CASE("Constructs a vector with n copies of value",
          "[SWS_CORE], [SWS_CORE_01301]")
{
    std::size_t            size = 2;
    ara::core::Vector<int> vector(size, 10);

    CHECK(vector.size() == size);
    CHECK(vector.at(0) == 10);
    CHECK(vector[1] == 10);
}

TEST_CASE("Constructs a vector equal to the range",
          "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};

    ara::core::Vector<int> rangeVector(vector.begin() + 1, vector.begin() + 3);

    CHECK(rangeVector.size() == 2);
    CHECK(rangeVector.at(0) == 2);
    CHECK(rangeVector.at(1) == 3);
}

TEST_CASE("Vector copies", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector = {1, 2, 3, 4, 5};
    CHECK(vector.size() == 5);
    CHECK(vector.at(0) == 1);
    CHECK(vector.at(4) == 5);

    ara::core::Vector<int> lvalueVector = vector;
    CHECK(lvalueVector.size() == 5);
    CHECK(lvalueVector.at(0) == 1);
    CHECK(lvalueVector.at(4) == 5);

    auto                   alloc = std::allocator<int>{};
    ara::core::Vector<int> customAllocatorVector(vector, alloc);
    CHECK(customAllocatorVector.size() == 5);
    CHECK(customAllocatorVector.at(0) == 1);
    CHECK(customAllocatorVector.at(4) == 5);
}

TEST_CASE("Vector moves", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector = {1, 2, 3, 4, 5};
    CHECK(vector.size() == 5);
    CHECK(vector.at(0) == 1);
    CHECK(vector.at(4) == 5);

    ara::core::Vector<int> rvalueVector = std::move(vector);
    CHECK(rvalueVector.size() == 5);
    CHECK(rvalueVector.at(0) == 1);
    CHECK(rvalueVector.at(4) == 5);

    auto alloc = std::allocator<int>{};
    ara::core::Vector<int>
      customAllocatorVector(ara::core::Vector<int>{1, 2, 3, 4, 5}, alloc);
    CHECK(customAllocatorVector.size() == 5);
    CHECK(customAllocatorVector.at(0) == 1);
    CHECK(customAllocatorVector.at(4) == 5);
}

TEST_CASE("Vector operator=", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    ara::core::Vector<int> lvalueVector;
    ara::core::Vector<int> rvalueVector;
    ara::core::Vector<int> initListVector;

    CHECK(vector.size() == 5);
    CHECK(vector.at(0) == 1);
    CHECK(vector.at(4) == 5);

    lvalueVector = vector;
    CHECK(lvalueVector.size() == 5);
    CHECK(lvalueVector.at(0) == 1);
    CHECK(lvalueVector.at(4) == 5);

    rvalueVector = std::move(vector);
    CHECK(rvalueVector.size() == 5);
    CHECK(rvalueVector.at(0) == 1);
    CHECK(rvalueVector.at(4) == 5);

    initListVector = {1, 2, 3, 4, 5};
    CHECK(rvalueVector.size() == 5);
    CHECK(rvalueVector.at(0) == 1);
    CHECK(rvalueVector.at(4) == 5);
}

TEST_CASE("Vector - assign", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};

    ara::core::Vector<int> newVector;
    newVector.assign(vector.begin() + 1, vector.begin() + 3);
    CHECK(newVector.size() == 2);
    CHECK(newVector.at(0) == 2);
    CHECK(newVector.at(1) == 3);

    std::size_t size = 2;
    newVector.assign(size, 1);
    CHECK(newVector.size() == size);
    CHECK(newVector.at(0) == 1);
    CHECK(newVector.at(1) == 1);

    newVector.assign({1, 2});
    CHECK(newVector.size() == 2);
    CHECK(newVector.at(0) == 1);
    CHECK(newVector.at(1) == 2);
}

TEST_CASE("Vector - get_allocator", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};

    auto alloc = vector.get_allocator();
    CHECK(std::is_same<decltype(alloc), ara::core::Allocator<int>>::value);
}

TEST_CASE("Vector - iterators", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};

    CHECK(1 == *(vector.begin()));
    CHECK(1 == *(vector.cbegin()));
    CHECK(5 == *(vector.end() - 1));
    CHECK(5 == *(vector.cend() - 1));

    // reverse
    CHECK(5 == *(vector.rbegin()));
    CHECK(5 == *(vector.crbegin()));
    CHECK(1 == *(vector.rend() - 1));
    CHECK(1 == *(vector.crend() - 1));

    const ara::core::Vector<int> constVector{1, 2, 3, 4, 5};

    CHECK(1 == *(constVector.begin()));
    CHECK(5 == *(constVector.end() - 1));

    // reverse
    CHECK(5 == *(constVector.rbegin()));
    CHECK(1 == *(constVector.rend() - 1));
}

TEST_CASE("Vector - empty", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    CHECK(false == vector.empty());

    ara::core::Vector<int> emptyVector;
    CHECK(true == emptyVector.empty());
}

TEST_CASE("Vector - size", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    CHECK(5 == vector.size());

    ara::core::Vector<int> emptyVector;
    CHECK(0 == emptyVector.size());
}

TEST_CASE("Vector - max_size", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    CHECK(5 < vector.max_size());
}

TEST_CASE("Vector - resize", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};

    std::size_t size = 3;
    vector.resize(size);
    CHECK(size == vector.size());

    size = 10;
    vector.resize(size, 15);
    CHECK(size == vector.size());
    CHECK(1 == vector[0]);
    CHECK(3 == vector[2]);
    CHECK(15 == vector[5]);
}

TEST_CASE("Vector - capacity", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    CHECK(5 == vector.capacity());

    ara::core::Vector<int> emptyVector;
    CHECK(0 == emptyVector.capacity());
}

TEST_CASE("Vector - reserve", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    CHECK(5 == vector.capacity());

    std::size_t size = 100;
    vector.reserve(size);
    CHECK(100 == vector.capacity());
}

TEST_CASE("Vector - shrink_to_fit, clear", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    CHECK(5 == vector.capacity());
    CHECK(1 == vector[0]);

    vector.clear();
    vector.shrink_to_fit();
    CHECK(0 == vector.capacity());
}

TEST_CASE("Vector - operator[], at", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    CHECK(2 == vector.at(1));
    CHECK(1 == vector[0]);

    const ara::core::Vector<int> constVector{1, 2, 3, 4, 5};
    CHECK(2 == constVector.at(1));
    CHECK(1 == constVector[0]);
}

TEST_CASE("Vector - front, back", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    CHECK(1 == vector.front());
    CHECK(5 == vector.back());

    const ara::core::Vector<int> constVector{1, 2, 3, 4, 5};
    CHECK(1 == constVector.front());
    CHECK(5 == constVector.back());
}

TEST_CASE("Vector - data", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    auto                   data = vector.data();
    CHECK(1 == *data);
    CHECK(5 == *(data + 4));

    const ara::core::Vector<int> constVector{1, 2, 3, 4, 5};
    auto                         constData = constVector.data();
    CHECK(1 == *constData);
    CHECK(5 == *(constData + 4));
}

TEST_CASE("Vector - emplace_back, emplace", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector;
    CHECK(0 == vector.size());

    vector.emplace_back(1);
    vector.emplace_back(4);
    CHECK(2 == vector.size());
    CHECK(1 == vector.at(0));
    CHECK(4 == vector.at(1));

    auto it = vector.emplace(vector.begin() + 1, 2);
    vector.emplace(it + 1, 3);
    CHECK(4 == vector.size());
    CHECK(2 == vector.at(1));
    CHECK(3 == vector.at(2));
}

TEST_CASE("Vector - push_back, pop_back", "[SWS_CORE], [SWS_CORE_01301]")
{
    struct Test
    {
        int a;
    };

    ara::core::Vector<Test> vector;
    CHECK(0 == vector.size());

    Test instance;
    vector.push_back(instance);
    vector.push_back(Test());
    CHECK(2 == vector.size());

    vector.pop_back();
    CHECK(1 == vector.size());
}

TEST_CASE("Vector - insert", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{1, 2, 3, 4, 5};
    CHECK(5 == vector.size());

    auto it = vector.begin();
    it      = vector.insert(it, 200);
    CHECK(6 == vector.size());
    CHECK(200 == vector.at(0));

    std::size_t count = 2;
    vector.insert(it, count, 300);
    CHECK(8 == vector.size());
    CHECK(300 == vector.at(0));
    CHECK(300 == vector.at(1));

    it = vector.begin();
    ara::core::Vector<int> vector2{50, 50};
    vector.insert(it + 2, vector2.begin(), vector2.end());
    CHECK(10 == vector.size());
    CHECK(300 == vector.at(0));
    CHECK(300 == vector.at(1));
    CHECK(50 == vector.at(2));
    CHECK(50 == vector.at(3));

    int arr[] = {501, 502, 503};
    vector.insert(vector.begin(), arr, arr + 3);
    CHECK(13 == vector.size());
    CHECK(501 == vector.at(0));
    CHECK(502 == vector.at(1));
    CHECK(503 == vector.at(2));

    int copyElement = 69;
    vector.insert(vector.end(), copyElement);
    CHECK(14 == vector.size());
    CHECK(69 == vector.back());

    vector.insert(vector.end(), {666, 666, 666});
    CHECK(17 == vector.size());
    CHECK(666 == vector.back());
}

TEST_CASE("Vector - erase", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK(10 == vector.size());

    vector.erase(vector.begin());
    CHECK(9 == vector.size());
    CHECK(1 == vector.at(0));

    vector.erase(vector.begin() + 2, vector.begin() + 5);
    CHECK(6 == vector.size());
    CHECK(6 == vector.at(2));
    CHECK(9 == vector.at(5));
}

TEST_CASE("Vector - swap", "[SWS_CORE], [SWS_CORE_01301]")
{
    ara::core::Vector<int> lhs{1, 2, 3, 4, 5};
    ara::core::Vector<int> rhs{6, 7, 8, 9};

    CHECK(5 == lhs.size());
    CHECK(1 == lhs.at(0));
    CHECK(4 == rhs.size());
    CHECK(6 == rhs.at(0));

    lhs.swap(rhs);
    CHECK(5 == rhs.size());
    CHECK(1 == rhs.at(0));
    CHECK(4 == lhs.size());
    CHECK(6 == lhs.at(0));
}

TEST_CASE("Non member functions - operator==", "[SWS_CORE], [SWS_CORE_01390]")
{
    ara::core::Vector<int> lhs{1, 2, 3, 4, 5};
    ara::core::Vector<int> rhs{1, 2, 3, 4, 5};
    CHECK(lhs == rhs);
}

TEST_CASE("Non member functions - operator!=", "[SWS_CORE], [SWS_CORE_01391]")
{
    ara::core::Vector<int> lhs{1, 2, 3, 4, 5};
    ara::core::Vector<int> rhs{6, 7, 8, 9};
    CHECK(lhs != rhs);
}

TEST_CASE("Non member functions - operator<", "[SWS_CORE], [SWS_CORE_01392]")
{
    ara::core::Vector<int> lhs{1, 2, 3, 4, 5};
    ara::core::Vector<int> rhs{6, 7, 8, 9};
    CHECK(lhs < rhs);
}

TEST_CASE("Non member functions - operator<=", "[SWS_CORE], [SWS_CORE_01393]")
{
    ara::core::Vector<int> lhs{6, 6, 6};
    ara::core::Vector<int> rhs{6, 6, 7};
    CHECK(lhs <= rhs);
}

TEST_CASE("Non member functions - operator>", "[SWS_CORE], [SWS_CORE_01394]")
{
    ara::core::Vector<int> lhs{6, 7, 8, 9};
    ara::core::Vector<int> rhs{1, 2, 3, 4, 5};
    CHECK(lhs > rhs);
}

TEST_CASE("Non member functions - operator>=", "[SWS_CORE], [SWS_CORE_01395]")
{
    ara::core::Vector<int> lhs{6, 6, 7};
    ara::core::Vector<int> rhs{6, 6, 6};
    CHECK(lhs >= rhs);
}

TEST_CASE("Non member functions - swap", "[SWS_CORE], [SWS_CORE_01396]")
{
    ara::core::Vector<int> lhs{1, 2, 3, 4, 5};
    ara::core::Vector<int> rhs{6, 7, 8, 9};

    CHECK(5 == lhs.size());
    CHECK(1 == lhs.at(0));
    CHECK(4 == rhs.size());
    CHECK(6 == rhs.at(0));

    ara::core::swap(lhs, rhs);

    CHECK(5 == rhs.size());
    CHECK(1 == rhs.at(0));
    CHECK(4 == lhs.size());
    CHECK(6 == lhs.at(0));
}
