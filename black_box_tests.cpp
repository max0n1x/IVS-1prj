//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Maksym Podhornyi <xpodho08@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Maksym Podhornyi
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

    BinaryTree tree;

};

class TreeAxioms : public ::testing::Test
{
protected:

    BinaryTree tree1;
    BinaryTree tree2;

    virtual void SetUp()
    {
        tree1.InsertNode(3);
        tree1.InsertNode(8);
        tree1.InsertNode(158);
        tree1.InsertNode(1);
        tree1.InsertNode(23);
        tree1.InsertNode(46);
        tree1.InsertNode(14);
        tree1.InsertNode(432);
        tree1.InsertNode(0);
    }

};

TEST_F(EmptyTree, InsertNode) {
    int values[] = { 3, 45, 67, 433, 65, 677, 332, 26 };

    for (const auto value : values) {
        auto result = tree.InsertNode(value);
        EXPECT_EQ(result.first, true) << "Failed to insert value " << value;
    }
}

TEST_F(EmptyTree, DeleteNode){

    int values [] = { 3, 45, 67, 433, 65, 677, 332, 26, 67 };

    for (auto value : values){
        EXPECT_FALSE(tree.DeleteNode(value));
    }

}

TEST_F(EmptyTree, FindNode) {

    int values [] = { 3, 45, 67, 433, 65, 677, 332, 26, 67 };

    for (const auto value : values) {
        tree.InsertNode(value);
    }

    for (const auto value : values) {
        Node_t* node = tree.FindNode(value);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->key, value);
    }
}

TEST_F(NonEmptyTree, InsertNode) {

    int values[] = { 3, 45, 67, 433, 65, 677, 332, 26 };

    for (const auto value : values) {
        auto result = tree.InsertNode(value);
        EXPECT_EQ(result.first, true) << "Failed to insert value " << value;
    }
}

TEST_F(NonEmptyTree, DeleteNode) {

    std::vector<int> values = { 3, 8, 158, 1, 23, 46, 14, 432, 0 };

    for (const auto& value : values) {
        tree.InsertNode(value);
    }

    for (const auto& value : values) {
        bool deleted = tree.DeleteNode(value);
        EXPECT_TRUE(deleted);
        EXPECT_EQ(tree.FindNode(value), nullptr);
    }

    for (const auto& value : values) {
        bool deleted = tree.DeleteNode(value);
        EXPECT_FALSE(deleted);
        EXPECT_EQ(tree.FindNode(value), nullptr);
    }

}

TEST_F(NonEmptyTree, FindNode) {

    std::vector<int> values = { 3, 8, 158, 1, 23, 46, 14, 432, 0 };

    for (const auto& value : values) {
        tree.InsertNode(value);
    }

    for (const auto& value : values) {
        Node_t* node = tree.FindNode(value);
        EXPECT_NE(node, nullptr);
        EXPECT_EQ(node->key, value);
    }

    int missingValue = 999;
    Node_t* missingNode = tree.FindNode(missingValue);
    EXPECT_EQ(missingNode, nullptr);
}

TEST_F(TreeAxioms, Axiom1){

    std::vector<Node_t *> nodes;
    tree1.GetLeafNodes(nodes);

    bool result = std::all_of(nodes.begin(), nodes.end(),
                              [](Node_t* node) { return node->color == BLACK; });

    EXPECT_TRUE(result);
}

TEST_F(TreeAxioms, Axiom2) {

    std::vector<Node_t*> nonLeafNodesTree1;
    tree1.GetNonLeafNodes(nonLeafNodesTree1);

    std::vector<Node_t*> nonLeafNodesTree2;
    tree2.GetNonLeafNodes(nonLeafNodesTree2);

    std::vector<Node_t*> allNodesTree1;
    tree1.GetAllNodes(allNodesTree1);

    std::vector<Node_t*> allNodesTree2;
    tree2.GetAllNodes(allNodesTree2);

    for (auto node : nonLeafNodesTree1) {
        if (node->color == RED) {
            EXPECT_NE(node->pLeft, nullptr);
            EXPECT_NE(node->pRight, nullptr);
            EXPECT_EQ(node->pLeft->color, BLACK);
            EXPECT_EQ(node->pRight->color, BLACK);
        }
    }

    for (auto node : nonLeafNodesTree2) {
        if (node->color == RED) {
            EXPECT_NE(node->pLeft, nullptr);
            EXPECT_NE(node->pRight, nullptr);
            EXPECT_EQ(node->pLeft->color, BLACK);
            EXPECT_EQ(node->pRight->color, BLACK);
        }
    }

    for (auto node : allNodesTree1) {
        if (node->color == RED) {
            EXPECT_NE(node->pLeft, nullptr);
            EXPECT_NE(node->pRight, nullptr);
            EXPECT_EQ(node->pLeft->color, BLACK);
            EXPECT_EQ(node->pRight->color, BLACK);
        }
    }

    for (auto node : allNodesTree2) {
        if (node->color == RED) {
            EXPECT_NE(node->pLeft, nullptr);
            EXPECT_NE(node->pRight, nullptr);
            EXPECT_EQ(node->pLeft->color, BLACK);
            EXPECT_EQ(node->pRight->color, BLACK);
        }
    }

}

TEST_F(TreeAxioms, Axiom3) {

    std::vector<Node_t*> leafNodesTree1;
    tree1.GetLeafNodes(leafNodesTree1);

    std::vector<Node_t*> leafNodesTree2;
    tree2.GetLeafNodes(leafNodesTree2);

    for (auto node : leafNodesTree1) {
        int blackNodes = 0;
        Node_t *p = node;
        while (p != nullptr) {
            if (p->color == BLACK) {
                blackNodes++;
            }
            p = p->pParent;
        }
        int blackNodesFromRoot = 0;
        p = tree1.GetRoot();
        while (p != nullptr) {
            if (p->color == BLACK) {
                blackNodesFromRoot++;
            }
            p = p->pRight;
        }
        EXPECT_EQ(blackNodes, blackNodesFromRoot);
    }

    for (auto node : leafNodesTree2) {
        int blackNodes = 0;
        Node_t *p = node;
        while (p != nullptr) {
            if (p->color == BLACK) {
                blackNodes++;
            }
            p = p->pParent;
        }
        int blackNodesFromRoot = 0;
        p = tree2.GetRoot();
        while (p != nullptr) {
            if (p->color == BLACK) {
                blackNodesFromRoot++;
            }
            p = p->pRight;
        }
        EXPECT_EQ(blackNodes, blackNodesFromRoot);
    }

}













/*** Konec souboru black_box_tests.cpp ***/
