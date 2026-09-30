#include "vector.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>

TEST(VectorTests, Builds) {
    bd::vector<int> vec;
    ASSERT_EQ(0, vec.size());
    ASSERT_TRUE(vec.empty());
}

TEST(VectorTests, CreateAndPushBack) {
    bd::vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(3, vec[2]);
    EXPECT_EQ(4, vec[3]);
    EXPECT_EQ(4, vec.size());
    EXPECT_EQ(4, vec.capacity());
}

TEST(VectorTests, AddAndClear) {
    bd::vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(3, vec[2]);
    EXPECT_EQ(4, vec[3]);
    EXPECT_EQ(4, vec.size());
    EXPECT_EQ(4, vec.capacity());

    vec.clear();

    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(4, vec.capacity());
}

TEST(VectorTests, PushBackAndPopBack) {
    bd::vector<int> vec;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(3, vec[2]);
    EXPECT_EQ(4, vec[3]);
    EXPECT_EQ(4, vec.size());
    EXPECT_EQ(4, vec.capacity());

    vec.pop_back();

    EXPECT_EQ(3, vec.size());
    EXPECT_EQ(4, vec.capacity());

    vec.pop_back();

    EXPECT_EQ(2, vec.size());
    EXPECT_EQ(4, vec.capacity());

    vec.push_back(10);
    vec.push_back(11);

    EXPECT_EQ(10, vec[2]);
    EXPECT_EQ(11, vec[3]);
    EXPECT_EQ(4, vec.size());
    EXPECT_EQ(4, vec.capacity());
}

TEST(VectorTests, ReserveAndShrinkToFit) {
    bd::vector<int> vec;

    vec.reserve(1000);
    EXPECT_EQ(1000, vec.capacity());
    EXPECT_EQ(0, vec.size());

    vec.push_back(10);
    vec.push_back(10);
    vec.push_back(10);
    vec.push_back(10);
    vec.push_back(10);

    EXPECT_EQ(1000, vec.capacity());
    EXPECT_EQ(5, vec.size());

    vec.shrink_to_fit();

    EXPECT_EQ(5, vec.capacity());
    EXPECT_EQ(5, vec.size());
}

TEST(VectorTests, ElementAccess) {
    bd::vector<std::string> vec;

    vec.push_back("Hello");
    vec.push_back("World");

    EXPECT_EQ("Hello", vec.front());
    EXPECT_EQ("World", vec.back());

    std::string* data = vec.data();
    EXPECT_EQ("Hello", *data);
    EXPECT_EQ("World", *(data + 1));
}

TEST(VectorTests, ResizeBehavior) {
    bd::vector<std::string> vec;

    vec.push_back("The");
    vec.push_back("Lord");
    vec.push_back("of");
    vec.push_back("the");
    vec.push_back("Rings");

    EXPECT_EQ("The", vec.front());
    EXPECT_EQ(5, vec.size());

    // resize larger
    vec.resize(10);
    EXPECT_EQ(10, vec.size());
    EXPECT_EQ(std::string(), vec.back());

    // resize same
    vec.resize(10);
    EXPECT_EQ(10, vec.size());
    EXPECT_EQ(std::string(), vec.back());

    // resize smaller
    vec.resize(3);
    EXPECT_EQ(3, vec.size());
    EXPECT_EQ("of", vec.back());
}

TEST(VectorTests, ConstructWithDefaultSizeAndPushBack) {
    bd::vector<int> vec(10);
    std::vector<int> stdVec(10);

    EXPECT_EQ(stdVec.capacity(), vec.capacity());
    EXPECT_EQ(stdVec.size(), vec.size());
    EXPECT_EQ(stdVec[3], vec[3]);

    vec.push_back(10);
    EXPECT_EQ(20, vec.capacity());
}

TEST(VectorTests, ConstructEmptyAndReserve) {
    bd::vector<std::string> vec;
    std::vector<std::string> stdVec;

    constexpr int RESIZE_VALUE{ 1000 };
    vec.reserve(RESIZE_VALUE);
    stdVec.reserve(RESIZE_VALUE);

    EXPECT_EQ(stdVec.size(), vec.size());
    EXPECT_EQ(stdVec.capacity(), vec.capacity());
}

TEST(VectorTests, ConstructsWithParamValue) {
    bd::vector<int> vec(10, 5);
    std::vector<int> stdVec(10, 5);

    ASSERT_EQ(stdVec.capacity(), vec.capacity());
    ASSERT_EQ(stdVec.size(), vec.size());
    ASSERT_EQ(stdVec[3], vec[3]);

    vec.push_back(10);
    EXPECT_EQ(20, vec.capacity());
}

TEST(VectorTests, ConstructWithInitalizerList) {
    bd::vector<int> vec{ 1, 2, 3 };
    bd::vector<std::string> svec{ "Vikas", "is", "a", "toilet" };

    EXPECT_EQ(3, vec.size());
    EXPECT_EQ(4, svec.size());

    ASSERT_EQ(vec[0], 1);
    ASSERT_EQ(svec[0], "Vikas");
}

TEST(VectorTests, CompareOperators) {
    bd::vector<int> a{ 1, 2, 3 };
    bd::vector<int> b{ 1, 2, 3 };
    bd::vector<int> c{ 1, 2, 4 };
    bd::vector<int> d{ 1, 2 };
    bd::vector<int> e{};

    // equality
    ASSERT_TRUE(a == b);
    ASSERT_TRUE(a != c);
    ASSERT_TRUE(a != d);

    // lexicographic ordering
    ASSERT_TRUE(a < c);
    ASSERT_TRUE(d < a);
    ASSERT_TRUE(e < d);
    ASSERT_TRUE(!(a < b) && !(b < a));
    ASSERT_TRUE(c > a && a <= b && a >= b);
}
