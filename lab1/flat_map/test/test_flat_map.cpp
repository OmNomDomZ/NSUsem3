#include "flat_map.h"
#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <iostream>

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

std::vector<std::vector<std::string>> TestCase4
    {
        {"key6", "value6"},
        {"key7", "value7"},
        {"key5", "value5"},
        {"key2", "value2"},
        {"key9", "value9"},
        {"key1", "value1"},
        {"key8", "value8"},
        {"key3", "value3"},
        {"key4", "value4"}
    };

std::vector<std::vector<std::string>> TestCase5
    {
        {"key", "first_value"},
        {"key", "second_value"}
    };

TEST(FlatMapTest, EmptyMap)
{
    FlatMap map;
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
      EXPECT_EQ(map[param[0]], param[1]) << param[0];
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
      EXPECT_EQ(map[param[0]], param[1]) << param[0];
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
      EXPECT_EQ(map[param[0]], param[1]) << param[0];
    }
}

TEST(FlatMapTest, Insert4)
{
    FlatMap map;
    for (const auto& param : TestCase4)
    {
      map[param[0]] = param[1];
    }

    for (const auto& param : TestCase4)
    {
      EXPECT_EQ(map[param[0]], param[1]) << param[0];
    }
}

TEST(FlatMapTest, UpdateElement)
{
    FlatMap map;
    map[TestCase5[0][0]] = TestCase5[0][1];
    EXPECT_EQ(map["key"], "first_value");
    EXPECT_EQ(map.size(), 1);

    map[TestCase5[1][0]] = TestCase5[1][1];
    EXPECT_EQ(map["key"], "second_value");
    EXPECT_EQ(map.size(), 1);
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
        EXPECT_FALSE(map.contains(param[0])) << param[0];
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
        EXPECT_FALSE(map.contains(param[0])) << param[0];
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
        EXPECT_FALSE(map.contains(param[0])) << param[0];
    }
    EXPECT_EQ(map.size(), 0);
}

TEST(FlatMapTest, Erase4)
{
  FlatMap map;
  for (const auto& param : TestCase4)
    {
      map[param[0]] = param[1];
    }

  for (const auto& param : TestCase4)
    {
      EXPECT_EQ(map.erase(param[0]), 1);
      EXPECT_FALSE(map.contains(param[0])) << param[0];
    }
  EXPECT_EQ(map.size(), 0);
}


TEST(FlatMapTest, Clear)
{
    FlatMap map;
    for (const auto& param : TestCase4)
    {
        map[param[0]] = param[1];
    }
    EXPECT_EQ(map.size(), TestCase4.size());
    map.clear();
    for (const auto& param : TestCase4)
    {
        EXPECT_FALSE(map.contains(param[0])) << param[0];
    }
    EXPECT_EQ(map.size(), 0);
}

 TEST(FlatMapTest, CopyConstructor)
{
    FlatMap map1;
    FlatMap map2;
    map2 = map1;

    for (const auto& param : TestCase4)
    {
        map1[param[0]] = param[1];
    }
    for (const auto& param : TestCase4)
    {
        EXPECT_NE(map1[param[0]], map2[param[0]]);
    }
    map2 = map1;
    for (const auto& param : TestCase4)
    {
        EXPECT_EQ(map1[param[0]], map2[param[0]]);
    }
}

TEST(FlatMapTest, Find)
{
    FlatMap map;

    for (const auto& param : TestCase4)
    {
        map[param[0]] = param[1];
    }

    std::size_t count = 0;
    for( auto it = map.find("key1"); it != map.end(); ++it ) {
        count++;
    }
    EXPECT_EQ(count, 9);

    count = 0;
    for( auto it = map.find("key7"); it != map.end(); ++it ) {
        count++;
    }
    EXPECT_EQ(count, 3);

    count = 0;
    for( auto it = map.find("key9"); it != map.end(); ++it ) {
        count++;
    }
    EXPECT_EQ(count, 1);
}

