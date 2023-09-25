#include "FlatMap.h"
#include "gtest/gtest.h"

#include <iostream>
#include <string>
#include <vector>
#include <utility>

std::vector<std::vector<std::string>> TestCase1
{
    {"key1", "value1"},
    {"key2", "value2"},
    {"key3", "value3"},
    {"key4", "value4"},
    {"key5", "value5"}
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

    EXPECT_TRUE(map.contains(TestCase1[0][0]));
}
