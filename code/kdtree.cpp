#include "kdtree.h"

KDTree::KDTree()
{
  root = new kd_node *;
  *root = NULL;
}

KDTree::~KDTree() {}

kd_node *KDTree::init_node(string label, float coordinates[2])
{
  kd_node *ret(new kd_node);
  ret->label = label;
  ret->coordinates[0] = coordinates[0];
  ret->coordinates[1] = coordinates[1];
  ret->left = nullptr;
  ret->right = nullptr;
  return ret;
}

//needs to insert closest to coordinates
void KDTree::insert(kd_node *new_node, kd_node *root)
{
  auto current = *root;

  if ((current)->data > new_node->data)
  {
    if ((current)->left == nullptr)
    {
      (current)->left = new_node;
      return;
    }
    else
    {
      insert(new_node, current->left);
    }
  }
  else if ((current)->data < new_node->data)
  {
    if ((current)->right == nullptr)
    {
      (current)->right = new_node;
      return;
    }
    else
    {
      insert(new_node, current->right);
    }
  }
  else if ((current)->data == new_node->data)
  {
    (current)->right = new_node;
    return;
  }
  else
  {
    return;
  }
}
