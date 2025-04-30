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
  //constructor and destructor
  KDTree();
  ~KDTree();

  // creates the kd node
  kd_node *init_node(array<float, 2> points, string label);

  // inserts a given node into the tree
  void insert(kd_node *new_node, int depth);
  // does the bulk of the insert work and is used in the insert function
  void insert_helper(kd_node *new_node, kd_node *root_, int depth);

  // removes a node from the tree using the helper functions below
  void remove(array<float, 2> points, int depth);
  // removes a node with no children (leaf)
  void remove_no_children(array<float, 2> points, kd_node *subt, kd_node *parent, int depth);
  // removes a node with one child
  void remove_one_child(array<float, 2> points, kd_node *subt, kd_node *parent, int depth);
  // removes a node with two children
  void remove_two_children(array<float, 2> points, kd_node *subt, int depth);

  // calculates the euclidean distance
  float distanceb(float starting0, float starting1, array<float, 2> target);
  // runs the search function to find the closest two nodes to the given points
  vector<kd_node*> search(kd_node *subt, array<float, 2> point, int depth, float &bestDistance, kd_node *&best, kd_node *&secondBestN, float &secondBestD);
  // uses the search function to return the closest node
  kd_node *knn(kd_node *subt, array<float, 2> point, int depth);
  // uses the search function to return the second closest node
  kd_node *secondBest(kd_node *subt, array<float, 2> point, int depth);

  // checks if a given node is contained in the tree (uses get_node)
  bool contains(kd_node *subt, array<float, 2> points);
  // gets a node if it is in the tree and returns nullptr if not
  kd_node *get_node(kd_node *subt, array<float, 2> points, int depth);
  // gets the size of the tree
  int size(kd_node *subt);
  // gets the trees root
  kd_node *get_root();
  // sets the trees root
  void set_root(kd_node **new_root);

private:
  kd_node **root;
};

#endif // KDTree_H__
