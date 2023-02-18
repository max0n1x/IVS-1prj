//======== Copyright (c) 2022, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     Maksym Podhornyi <xpodho08@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Maksym Podhornyi
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//

class EmptyMap : public ::testing::Test {
protected:
    hash_map_t* map;

    void SetUp() {

        map = hash_map_ctor();

    }

    void TearDown() {

        hash_map_dtor(map);

    }

};

class NonEmptyMap : public ::testing::Test {
protected:
    void SetUp() {

        map = hash_map_ctor();

        hash_map_put(map, "key1", 42);
        hash_map_put(map, "key2", 1337);
        hash_map_put(map, "key3", -1);
        hash_map_put(map, "key4", 0);
        hash_map_put(map, "key5", 123456789);
        hash_map_put(map, "key6", 987654321);
        hash_map_put(map, "key7", -100);
        hash_map_put(map, "key8", 43);

    }

    void TearDown() {

        hash_map_dtor(map);

    }

    hash_map_t* map;
};

class HashMapBoundaryTest : public ::testing::Test {
protected:

    void SetUp() {

        map = hash_map_ctor();

    }

    void TearDown() {

        hash_map_dtor(map);

    }

    hash_map_t* map;
};

TEST_F(EmptyMap, Size) {

    EXPECT_EQ(0, hash_map_size(map));

}

TEST_F(EmptyMap, Capacity) {

    EXPECT_EQ(8, hash_map_capacity(map));

}

TEST_F(EmptyMap, Contains) {

    EXPECT_FALSE(hash_map_contains(map, "key"));

}

TEST_F(EmptyMap, Get) {

    int value;
    EXPECT_EQ(KEY_ERROR, hash_map_get(map, "key", &value));

}

TEST_F(EmptyMap, Put) {

    EXPECT_EQ(OK, hash_map_put(map, "key", 1));
    EXPECT_EQ(1, hash_map_size(map));
    EXPECT_EQ(8, hash_map_capacity(map));
    EXPECT_TRUE(hash_map_contains(map, "key"));
    EXPECT_EQ(KEY_ALREADY_EXISTS, hash_map_put(map, "key", 2));

}

TEST_F(EmptyMap, Remove) {
    EXPECT_EQ(KEY_ERROR, hash_map_remove(map, "key"));
    EXPECT_EQ(0, hash_map_size(map));
    EXPECT_EQ(8, hash_map_capacity(map));
}

TEST_F(EmptyMap, Clear) {

    hash_map_clear(map);
    EXPECT_EQ(0, hash_map_size(map));
    EXPECT_EQ(8, hash_map_capacity(map));
}

TEST_F(EmptyMap, Pop) {

    int value;
    EXPECT_EQ(KEY_ERROR, hash_map_pop(map, "key", &value));
    EXPECT_EQ(0, hash_map_size(map));
    EXPECT_EQ(8, hash_map_capacity(map));

}

TEST_F(NonEmptyMap, Capacity) {

    int num_elements = hash_map_size(map);
    int expected_capacity = 8;
    double load_factor = (double) num_elements / expected_capacity;

    if (load_factor > HASH_MAP_REALLOCATION_THRESHOLD) {
        expected_capacity = (expected_capacity << 1);
    }

    EXPECT_EQ(expected_capacity, hash_map_capacity(map));

}

TEST_F(NonEmptyMap, Size) {

    EXPECT_EQ(8, hash_map_size(map));
}


TEST_F(NonEmptyMap, Contains) {

    EXPECT_TRUE(hash_map_contains(map, "key4"));
    EXPECT_TRUE(hash_map_contains(map, "key6"));
    EXPECT_TRUE(hash_map_contains(map, "key8"));
    EXPECT_FALSE(hash_map_contains(map, "key9"));

}

TEST_F(NonEmptyMap, Get) {

    int value;

    hash_map_put(map, "aaa", 1);
    hash_map_put(map, "bbb", 2);
    hash_map_put(map, "ccc", 3);

    ASSERT_EQ(hash_map_get(map, "aaa", &value), KEY_ERROR);
    ASSERT_EQ(hash_map_get(map, "bbb", &value), 2);
    ASSERT_EQ(hash_map_get(map, "ccc", &value), 3);
    ASSERT_EQ(hash_map_get(map, "key11", &value), KEY_ERROR);

}


TEST_F(NonEmptyMap, Put) {

    ASSERT_EQ(OK, hash_map_put(map, "key9", 1));
    ASSERT_EQ(9, hash_map_size(map));
    ASSERT_EQ(16, hash_map_capacity(map));
    ASSERT_TRUE(hash_map_contains(map, "key9"));
    ASSERT_EQ(KEY_ALREADY_EXISTS, hash_map_put(map, "key9", 2));

}

TEST_F(NonEmptyMap, Remove) {

    ASSERT_EQ(OK, hash_map_remove(map, "key7"));
    ASSERT_FALSE(hash_map_contains(map, "key7"));
    ASSERT_EQ(KEY_ERROR, hash_map_remove(map, "key7"));

}

TEST_F(NonEmptyMap, Clear) {
    hash_map_clear(map);

    ASSERT_EQ(0, hash_map_size(map));

    const char* keys[] = {"key1", "key2", "key3", "key4", "key5", "key6", "key7", "key8"};
    for (const char* key : keys) {
        int value;
        ASSERT_EQ(KEY_ERROR, hash_map_get(map, key, &value));
    }

}

TEST_F(NonEmptyMap, Pop) {
    int value;

    ASSERT_EQ(OK, hash_map_get(map, "key7", &value));
    ASSERT_EQ(-100, value);
    ASSERT_EQ(OK, hash_map_get(map, "key5", &value));
    ASSERT_EQ(123456789, value);

    ASSERT_EQ(OK, hash_map_pop(map, "key7", &value));
    ASSERT_EQ(-100, value);
    ASSERT_EQ(KEY_ERROR, hash_map_get(map, "key7", &value));

    ASSERT_EQ(OK, hash_map_pop(map, "key5", &value));
    ASSERT_EQ(123456789, value);
    ASSERT_EQ(KEY_ERROR, hash_map_get(map, "key5", &value));

    ASSERT_EQ(KEY_ERROR, hash_map_pop(map, "key9", &value));

}


TEST_F(HashMapBoundaryTest, CollisionSameHash) {

    hash_map_put(map, "aaa", 1);
    hash_map_put(map, "bbb", 2);

    int value1, value2;

    ASSERT_EQ(OK, hash_map_get(map, "aaa", &value1));
    ASSERT_EQ(1, value1);
    ASSERT_EQ(OK, hash_map_get(map, "bbb", &value2));
    ASSERT_EQ(2, value2);

    size_t hash1 = std::hash<std::string>()("aaa");
    size_t hash2 = std::hash<std::string>()("bbb");

    size_t idx1 = hash1 % map->allocated;
    size_t idx2 = hash2 % map->allocated;

    ASSERT_EQ(4, idx1);
    ASSERT_EQ(2, idx2);

}

TEST_F(HashMapBoundaryTest, CollisionDifferentHash) {

    hash_map_put(map, "aaa", 1);
    hash_map_put(map, "bbb", 2);

    int value1, value2;
    ASSERT_EQ(OK, hash_map_get(map, "aaa", &value1));
    ASSERT_EQ(1, value1);
    ASSERT_EQ(OK, hash_map_get(map, "bbb", &value2));
    ASSERT_EQ(2, value2);

    size_t hash1 = std::hash<std::string>()("aaa");
    size_t hash2 = std::hash<std::string>()("bbb");
    size_t idx1 = hash1 % map->allocated;
    size_t idx2 = hash2 % map->allocated;

    ASSERT_NE(idx1, idx2);
}

/*** Konec souboru white_box_tests.cpp ***/
