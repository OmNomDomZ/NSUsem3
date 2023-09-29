#include "flat_map.h"
#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv)
{
    ::testing:: InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

std::vector<std::vector<std::string>> TestCase1
{
    {"key1", "value1"},
    {"key2", "value2"},
    {"key3", "value3"},
    {"key4", "value4"},
    {"key5", "value5"}
};

std::vector<std::vector<std::string>> TestCase2
{
    {"key5", "value5"},
    {"key4", "value4"},
    {"key3", "value3"},
    {"key2", "value2"},
    {"key1", "value1"}
};

std::vector<std::vector<std::string>> TestCase3
{
    {"key1", "value1"},
    {"key5", "value5"},
    {"key2", "value2"},
    {"key4", "value4"},
    {"key3", "value3"}
};

TEST(FlatMapTest, EmptyMap)
{
    FlatMap map;
    EXPECT_EQ(map.size(), 0);
}

TEST(FlatMapTest, Erase1)
{
    FlatMap map;
    for (const auto& param : TestCase1)
    {
        map[param[0]] = param[1];
    }

    for (const auto& param : TestCase1)
    {
        EXPECT_EQ(map.erase(param[0]), 1);
        EXPECT_FALSE(map.contains(param[0]));
    }
    EXPECT_EQ(map.size(), 0);
}

TEST(FlatMapTest, Erase2)
{
    FlatMap map;
    for (const auto& param : TestCase2)
    {
        map[param[0]] = param[1];
    }

    for (const auto& param : TestCase2)
    {
        EXPECT_EQ(map.erase(param[0]), 1);
        EXPECT_TRUE(map.contains(param[0]));
    }
    EXPECT_EQ(map.size(), 0);
}

TEST(FlatMapTest, Erase3)
{
    FlatMap map;
    for (const auto& param : TestCase3)
    {
        map[param[0]] = param[1];
    }

    for (const auto& param : TestCase3)
    {
        EXPECT_EQ(map.erase(param[0]), 1);
        EXPECT_FALSE(map.contains(param[0]));
    }
    EXPECT_EQ(map.size(), 0);
}

TEST(FlatMapTest, Insert1)
{
    FlatMap map;
    for (const auto& param : TestCase1)
    {
        map[param[0]] = param[1];
    }

    for (const auto& param : TestCase1)
    {
        EXPECT_EQ(map[param[0]], param[1]);
    }
}

TEST(FlatMapTest, Insert2)
{
    FlatMap map;
    for (const auto& param : TestCase2)
    {
        map[param[0]] = param[1];
    }

    for (const auto& param : TestCase2)
    {
        EXPECT_EQ(map[param[0]], param[1]);
    }
}

TEST(FlatMapTest, Insert3)
{
    FlatMap map;
    for (const auto& param : TestCase3)
    {
        map[param[0]] = param[1];
    }

    for (const auto& param : TestCase3)
    {
        EXPECT_EQ(map[param[0]], param[1]);
    }
}
