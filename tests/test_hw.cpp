#include "../code/KDTree.h"
#include <gtest/gtest.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class test_KD : public ::testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

kd_node *HandBuildNode(array<float, 2> points, string label)
{
  kd_node *ret(new kd_node);
  ret->coordinates[0] = points[0];
  ret->coordinates[1] = points[1];
  ret->left = nullptr;
  ret->right = nullptr;
  ret->label = label;
  return ret;
}

kd_node *HandBuildTree()
{
  array<float, 2> p1 = {494.0f, 271.0f};
  array<float, 2> p2 = {219.0f, 304.0f};
  array<float, 2> p3 = {391.0f, 411.0f};
  array<float, 2> p4 = {137.0f, 174.0f};
  array<float, 2> p5 = {328.0f, 123.0f};
  array<float, 2> p6 = {173.0f, 212.0f};

  kd_node *top = HandBuildNode(p1, "1");
  top->left = HandBuildNode(p2, "2");
  top->left->right = HandBuildNode(p3, "3");
  top->left->left = HandBuildNode(p4, "4");
  top->left->left->right = HandBuildNode(p5, "5");
  top->left->left->right->right = HandBuildNode(p6, "6");

  return top;
}

TEST_F(test_KD, TestConstructor)
{
  KDTree tree;
  ASSERT_FALSE(tree.get_root());
}

TEST_F(test_KD, TestInit)
{
  KDTree tree;
  array<float, 2> p1 = {2.0f, 3.0f};
  kd_node *nodeptr = tree.init_node(p1, "1");
  ASSERT_TRUE(nodeptr);
  ASSERT_EQ(p1[0], nodeptr->coordinates[0]);
  ASSERT_EQ(p1[1], nodeptr->coordinates[1]);
  ASSERT_FALSE(nodeptr->left);
  ASSERT_FALSE(nodeptr->right);
}

TEST_F(test_KD, TestInsert)
{
  kd_node *top(new kd_node());
  top->coordinates[0] = 263.0f;
  top->coordinates[1] = 109.0f;
  top->left = NULL;
  top->right = NULL;
  kd_node *one(new kd_node());
  one->coordinates[0] = 486.0f;
  one->coordinates[1] = 147.0f;
  one->left = NULL;
  one->right = NULL;
  kd_node *three(new kd_node());
  three->coordinates[0] = 129.0f;
  three->coordinates[1] = 136.0f;
  three->left = NULL;
  three->right = NULL;
  kd_node *four(new kd_node());
  four->coordinates[0] = 455.0f;
  four->coordinates[1] = 96.0f;
  four->left = NULL;
  four->right = NULL;

  KDTree tree;
  tree.insert(top, 0);
  tree.insert(one, 0);
  tree.insert(three, 0);
  tree.insert(four, 0);
  ASSERT_EQ(one, top->right);
  ASSERT_EQ(three, top->left);
  ASSERT_EQ(four, top->right->left);
}

TEST_F(test_KD, TestSize)
{
  kd_node *top = HandBuildTree();
  KDTree tree;
  ASSERT_EQ(6, tree.size(top));
}

TEST_F(test_KD, TestContains)
{
  kd_node *top = HandBuildTree();
  KDTree tree;
  array<float, 2> p2 = {219.0f, 304.0f};
  array<float, 2> p3 = {391.0f, 411.0f};
  array<float, 2> p4 = {137.0f, 174.0f};
  array<float, 2> f2 = {32.0f, 12.0f};
  array<float, 2> f3 = {17.0f, 21.0f};

  ASSERT_TRUE(tree.contains(top, p2));
  ASSERT_TRUE(tree.contains(top, p3));
  ASSERT_TRUE(tree.contains(top, p4));
  ASSERT_FALSE(tree.contains(top, f2));
  ASSERT_FALSE(tree.contains(top, f3));
}

TEST_F(test_KD, TestGetNode)
{
  // test getting a node from empty tree
  {
    array<float, 2> p1 = {2.0f, 3.0f};
    KDTree tree;
    kd_node *empty(NULL);
    kd_node *result = tree.get_node(empty, p1, 0);
    ASSERT_FALSE(result);
  }
  // tests getting nodes that we know are NOT there.
  {
    array<float, 2> p2 = {21.0f, 30.0f};
    array<float, 2> p3 = {39.0f, 41.0f};
    KDTree tree;
    kd_node *top = HandBuildTree();
    kd_node *result = tree.get_node(top, p2, 0);
    ASSERT_FALSE(result);
    ASSERT_FALSE(tree.get_node(top, p3, 0));
  }
  // tests getting nodes that we know are there.
  {
    kd_node *top = HandBuildTree();
    KDTree tree;
    array<float, 2> p2 = {219.0f, 304.0f};
    array<float, 2> p3 = {391.0f, 411.0f};
    ASSERT_EQ(tree.get_node(top, p2, 0), top->left);
    ASSERT_EQ(tree.get_node(top, p3, 0), top->left->right);
  }
}

TEST_F(test_KD, TestKNN)
{
  kd_node *top = HandBuildTree();
  KDTree tree;
  array<float, 2> p2 = {220.0f, 304.0f};
  ASSERT_EQ(tree.knn(top, p2, 0), top->left);
}

TEST_F(test_KD, TestRemoveNoChildren)
{
  kd_node *top = HandBuildTree();
  KDTree tree;
  tree.set_root(&top);
  array<float, 2> p3 = {391.0f, 411.0f};
  tree.remove(p3, 0);
  ASSERT_FALSE(top->left->right);
}

TEST_F(test_KD, TestRemoveOneChild)
{
  kd_node *top = HandBuildTree();
  array<float, 2> p5 = {328.0f, 123.0f};
  KDTree tree;
  tree.set_root(&top);
  tree.remove(p5, 0);
  ASSERT_FALSE(top->left->left->right->right);
  ASSERT_EQ(173.0f, top->left->left->right->coordinates[0]);
}

TEST_F(test_KD, TestRemoveRootWithTwoChildren)
{
  array<float, 2> p1 = {494.0f, 271.0f};
  array<float, 2> p4 = {137.0f, 174.0f};
  kd_node *top = HandBuildTree();
  KDTree tree;
  tree.set_root(&top);
  // Remove a node with two children (root)
  tree.remove(p1, 0);
  cout << "your number was : " << top << endl;
  ASSERT_EQ(p4, tree.get_root()->coordinates);
}

TEST_F(test_KD, TestRemoveInnerWithTwoChildren)
{
  kd_node *top = HandBuildTree();
  KDTree tree;
  tree.set_root(&top);
  array<float, 2> p1 = {494.0f, 271.0f};
  array<float, 2> p2 = {219.0f, 304.0f};
  tree.remove(p2, 0);
  ASSERT_EQ(391, top->left->coordinates[0]);
  ASSERT_EQ(p1, top->coordinates);
  ASSERT_FALSE(top->left->right);
}