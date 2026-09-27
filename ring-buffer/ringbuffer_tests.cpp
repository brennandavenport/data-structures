#include "ringbuffer.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

TEST(RingBufferTest, Builds) {
    bd::ringbuffer<std::string, 5> rb;
    EXPECT_EQ(0, rb.size());
    EXPECT_EQ(5, rb.capacity());
    EXPECT_TRUE(rb.isEmpty());
    EXPECT_FALSE(rb.isFull());
}

TEST(RingBufferTest, PushAndPop) {
    bd::ringbuffer<int, 5> rb;

    EXPECT_TRUE(rb.push(1));
    EXPECT_TRUE(rb.push(2));
    EXPECT_TRUE(rb.push(3));
    EXPECT_TRUE(rb.push(4));
    EXPECT_TRUE(rb.push(5));
    EXPECT_FALSE(rb.push(6));

    EXPECT_TRUE(rb.isFull());

    EXPECT_EQ(1, rb.peek());

    for (int i{}; i < 5; i++)
        rb.pop();

    EXPECT_TRUE(rb.isEmpty());

    EXPECT_THROW(rb.peek(), std::out_of_range);
    EXPECT_THROW(rb.pop(), std::out_of_range);
}

TEST(RingBufferTest, PushAndClear) {
    bd::ringbuffer<double, 3> rb;

    EXPECT_TRUE(rb.push(1.0));
    EXPECT_TRUE(rb.push(2.0));
    EXPECT_TRUE(rb.push(3.0));
    EXPECT_FALSE(rb.push(4.0));

    rb.clear();

    ASSERT_TRUE(rb.isEmpty());
    EXPECT_EQ(3, rb.capacity());
    EXPECT_EQ(0, rb.size());

    EXPECT_THROW(rb.peek(), std::out_of_range);
}

TEST(RingBufferTest, SingleThreadedTest) {
    bd::ringbuffer<int, 5> rb;

    int cases{ 1'000 };
    for (int i{}; i < cases; i++) {
        EXPECT_TRUE(rb.push(i));
        EXPECT_EQ(i, rb.pop());
    }
}
