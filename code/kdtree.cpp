#include "kdtree.h"

KDTree::~KDTree() {
  root = new kd_node *;
  *root = NULL;
}

kd_node* buildKDTree(vector<array<float, 2>>& points, int depth){
  if (points.empty()) {
        return nullptr;
    }
  int axis = depth % 2;
  sort(points.begin(), points.end(), [axis](const array<float,2>& a, const array<float, 2>& b) {
    return a[axis] < b[axis];
  });
  int median = points.size() / 2;
  string label = "placeholder";
  kd_node* root = new kd_node;
  root->label=label;
  root->coordinates[0]=points[median][0];
  root->coordinates[1]=points[median][1];
  root->left=nullptr;
  root->right=nullptr;

  vector<array<float, 2>> leftPoints(points.begin(), points.begin() + median);
  vector<array<float, 2>> rightPoints(points.begin() + median + 1, points.end());

  root->left = buildKDTree(leftPoints, depth + 1);
  root->right = buildKDTree(rightPoints, depth + 1);

  return root;
}
