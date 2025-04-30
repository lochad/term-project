/* Note: refer to the header file (KDTree.h) for documentation of each method. */

#include "KDTree.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>

KDTree::KDTree()
{
  root = new kd_node *;
  *root = NULL;
}

KDTree::~KDTree() {}

kd_node *KDTree::init_node(array<float, 2> points, string label)
{
  kd_node *ret(new kd_node);
  ret->coordinates = points;
  ret->left = nullptr;
  ret->right = nullptr;
  ret->label = label;
  return ret;
}

// deoth should normally be 0
void KDTree::insert(kd_node *new_node, int depth)
{
  if (*root == nullptr)
  {
    *root = new_node;
    return;
  }
  else
  {
    insert_helper(new_node, *root, depth);
  }
}

void KDTree::insert_helper(kd_node *new_node, kd_node *current, int depth)
{
  int lvl = depth % 2;
  if (new_node->coordinates[lvl] < current->coordinates[lvl])
  {
    if (current->left == nullptr)
    {
      current->left = new_node;
      return;
    }
    insert_helper(new_node, current->left, depth + 1);
  }
  else
  {
    if (current->right == nullptr)
    {
      current->right = new_node;
      return;
    }
    insert_helper(new_node, current->right, depth + 1);
  }
}

// depth should normally be 0
void KDTree::remove(array<float, 2> points, int depth)
{
  if (root == nullptr)
  {
    return;
  }
  remove_no_children(points, *root, *root, 0);
  remove_one_child(points, *root, *root, 0);
  remove_two_children(points, *root, depth);
}

// subt is the removal node
void KDTree::remove_no_children(array<float, 2> points, kd_node *subt, kd_node *parent, int depth)
{
  int lvl = depth % 2;
  if (subt == nullptr)
  {
    return;
  }
  // if we found the point and it has no children
  if ((subt->coordinates[0] == points[0]) && (subt->coordinates[1] == points[1]))
  {
    if (((subt)->left == nullptr) && ((subt)->right == nullptr))
    {
      delete subt;
      if (parent->left == subt)
      {
        parent->left = nullptr;
      }
      else
      {
        parent->right = nullptr;
      }
      return;
    }
  }
  // recurse until end of tree
  else if (subt->coordinates[lvl] > points[lvl])
  {
    remove_no_children(points, subt->left, subt, depth + 1);
  }
  else
  {
    remove_no_children(points, subt->right, subt, depth + 1);
  }
}

void KDTree::remove_one_child(array<float, 2> points, kd_node *subt, kd_node *parent, int depth)
{
  kd_node *current = subt;
  if (current == nullptr)
  {
    return;
  }
  int lvl = depth % 2;
  // if point is found and one of the chilren isn't null
  if ((current->coordinates[0] == points[0]) && (current->coordinates[1] == points[1]))
  {
    // if the current is left then update the parent's left, otherwise update parent's right
    if (((current)->left != nullptr) && ((current)->right == nullptr))
    {
      if (parent->left == current)
      {
        parent->left = current->left;
        delete current;
        return;
      }
      else
      {
        parent->right = current->left;
        delete current;
        return;
      }
    }
    // if the current is left then update the parent's left, otherwise update parent's right
    else if (((current)->right != nullptr) && ((current)->left == nullptr))
    {
      if (parent->left == current)
      {
        parent->left = current->right;
        delete current;
        return;
      }
      else
      {
        parent->right = current->right;
        delete current;
        return;
      }
    }
  }
  // recurse until null
  else if (current->coordinates[lvl] > points[lvl])
  {
    remove_one_child(points, current->left, current, depth + 1);
  }
  else
  {
    remove_one_child(points, current->right, current, depth + 1);
  }
}

void KDTree::remove_two_children(array<float, 2> points, kd_node *subt, int depth)
{
  if (subt == nullptr)
  {
    return;
  }
  int lvl = depth % 2;
  if (subt == nullptr)
  {
    return;
  }
  // if node is found and has two children
  if ((subt->coordinates[0] == points[0]) && (subt->coordinates[1] == points[1]))
  {
    if (((subt)->left != nullptr) && ((subt)->right != nullptr))
    {
      kd_node *successor = subt->right;
      kd_node *successorP = subt;
      // find last node in tree by searching the tree until successor coordinates are found
      if (successor->left != nullptr)
      {
        successor = successor->left;
        successorP = successor;
      }
      subt->coordinates = successor->coordinates;
      if (successorP->left == successor)
      {
        successorP->left = successor->left;
      }
      else
      {
        successorP->right = successor->right;
      }
      delete successor;
      return;
    }
  }
  // recurse until tree is null
  else if (subt->coordinates[lvl] > points[lvl])
  {
    remove_two_children(points, subt->left, depth + 1);
  }
  else if (subt->coordinates[lvl] > points[lvl])
  {
    remove_two_children(points, subt->right, depth + 1);
  }
}

// coordinates of starting point and target point
float KDTree::distanceb(float starting0, float starting1, array<float, 2> target)
{
  float euclidean = (pow((target[0] - starting0), 2)) + (pow((target[1] - starting1), 2));
  float distance = sqrt(euclidean);
  return distance;
}

vector<kd_node*> KDTree::search(kd_node *subt, array<float, 2> point, int depth, float &bestDistance, kd_node *&best, kd_node *&secondBestN, float &secondBestD)
{
  if (subt == nullptr)
  {
    return {best, secondBestN};
  }
  int lvl = depth % 2;
  // find euclidean's distance between current node and locating point
  float between = distanceb(subt->coordinates[0], subt->coordinates[1], point);
  
  // find new best if null or best distance is larger than current distance
if (best == nullptr || bestDistance > between)
{
    if (best != nullptr) {
        // updating second best with current best
        secondBestD = bestDistance;
        secondBestN = best;
    }
    bestDistance = between;
    best = subt;
  // find second best if second best is null or the new distance is less than the second distance AND the current distance is greater than the best distance
  // this helps account for when the current is worse than the current best but better than the second best
} else if ((secondBestN == nullptr || between < secondBestD) && between > bestDistance) {
    secondBestD = between;
    secondBestN = subt;
}
  kd_node *good;
  kd_node *bad;
  if (point[lvl] < subt->coordinates[lvl])
  {
    good = subt->left;
    bad = subt->right;
  }
  else
  {
    good = subt->right;
    bad = subt->left;
  }

  search(good, point, depth + 1, bestDistance, best, secondBestN, secondBestD);

  // figure out if there could be better points on the other side
  float distanceToSplittingPlane = abs(point[lvl] - subt->coordinates[lvl]);
  if (distanceToSplittingPlane < bestDistance)
  {
    search(bad, point, depth + 1, bestDistance, best, secondBestN, secondBestD);
  }
  return {best, secondBestN};
}
 // subt should be root or starting node and depth should be 0
kd_node *KDTree::knn(kd_node *subt, array<float, 2> point, int depth)
{
  // find very large distances so updated distances must be smaller
  float bestDistance = std::numeric_limits<float>::max();
  float secondBestD = std::numeric_limits<float>::max();
  kd_node *best = nullptr;
  kd_node *secondBestN = nullptr;
  return (search(subt, point, depth, bestDistance, best, secondBestN, secondBestD))[0];
}

// subt should be root or starting node and depth should be 0
kd_node *KDTree::secondBest(kd_node *subt, array<float, 2> point, int depth)
{
  // find very large distances so updated distances must be smaller
  float bestDistance = std::numeric_limits<float>::max();
  float secondBestD = std::numeric_limits<float>::max();
  kd_node *best = nullptr;
  kd_node *secondBestN = nullptr;
  return (search(subt, point, depth, bestDistance, best, secondBestN, secondBestD))[1];
}

bool KDTree::contains(kd_node *subt, array<float, 2> points)
{
  if (get_node(subt, points, 0) != NULL)
  {
    return true;
  }
  return false;
}

kd_node *KDTree::get_node(kd_node *subt, array<float, 2> points, int depth)
{

  if (subt != NULL)
  {
    if (points[0] == subt->coordinates[0] && points[1] == subt->coordinates[1])
    {
      return subt;
    }
    int lvl = depth % 2;
    if (points[lvl] < subt->coordinates[lvl])
    {
      return get_node(subt->left, points, depth + 1);
    }
    else
    {
      return get_node(subt->right, points, depth + 1);
    }
  }
  return nullptr;
}

int KDTree::size(kd_node *subt)
{
  if (subt == NULL)
  {
    return 0;
  }
  return 1 + size(subt->right) + size(subt->left);
}

kd_node *KDTree::get_root()
{
  if (*root == NULL)
    return NULL;
  return *root;
}

void KDTree::set_root(kd_node **new_root)
{
  *root = *new_root;
}
