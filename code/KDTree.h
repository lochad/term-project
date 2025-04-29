#ifndef KDTree_H__
#define KDTree_H__

#include <memory>
#include <string>
#include <vector>
#include <optional>

using namespace std;

struct kd_node
{
  string label;
  array<float, 2> coordinates;
  kd_node *left;
  kd_node *right;
};

class KDTree
{
public:
  KDTree();
  ~KDTree();

  kd_node *init_node(array<float, 2> points, string label);

  void insert(kd_node *new_node, int depth);
  void insert_helper(kd_node *new_node, kd_node *root_, int depth);
  void remove(array<float, 2> points, int depth);
  void remove_no_children(array<float, 2> points, kd_node *subt, kd_node *parent, int depth);
  kd_node *find_min(kd_node *subt, int depth, int d);
  void remove_one_child(array<float, 2> points, kd_node *subt, kd_node *parent, int depth);
  void remove_two_children(array<float, 2> points, kd_node *subt, int depth);

  float distanceb(float starting0, float starting1, array<float, 2> target);
  kd_node *search(kd_node *subt, array<float, 2> point, int depth, float &bestDistance, kd_node *&best);
  kd_node *knn(kd_node *subt, array<float, 2> point, int depth);

  bool contains(kd_node *subt, array<float, 2> points);
  kd_node *get_node(kd_node *subt, array<float, 2> points, int depth);
  int size(kd_node *subt);
  kd_node *get_root();
  void set_root(kd_node **new_root);

private:
  kd_node **root;
};

#endif // KDTree_H__
