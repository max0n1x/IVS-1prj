//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//


class NonEmptyTree : public ::testing::Test {
protected:
    BinaryTree *binaryTree;
    virtual void SetUp() {
        binaryTree = new BinaryTree();
        binaryTree->InsertNode(3);
        binaryTree->InsertNode(8);
        binaryTree->InsertNode(12);
    }

    virtual void TearDown() {
        delete binaryTree;

    }

    BinaryTree tree;
};

class EmptyTree : public ::testing::Test {
protected:
    BinaryTree *emptyTree;
    virtual void SetUp() {
        emptyTree = new BinaryTree();
    }

    virtual void TearDown() {

    }

    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode){
    std::vector<int> values = { 10, 5, 4, 7, 8, 90, -23, 100, 54, 32, 45, 232, -5 , 0 };

    for(auto value : values){
        auto result = tree.InsertNode(value);
        EXPECT_TRUE(result.first);
        EXPECT_EQ(result.second->key, value);
    }

    for(auto value : values){
        auto result1 = tree.InsertNode(value);
        EXPECT_FALSE(result1.first);
        EXPECT_EQ(result1.second->key, value);
    }
}

TEST_F(EmptyTree, DeleteNode){
    int values [] = { 10, 5, 4, 7, 8, 90, -23, 100, 54, 32, 45, 232, -5 , 0 };

    for (auto value : values){
        EXPECT_FALSE(tree.DeleteNode(value));
    }
}



/*** Konec souboru black_box_tests.cpp ***/
