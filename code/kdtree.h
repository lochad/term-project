#include <memory>
#include <string>
#include <vector>

using namespace std;

struct kd_node {
  string label;
  float coordinates[2];
  kd_node* left;
  kd_node* right;
};

class KDTree {
public:
  // The constructor initializes class variables and pointers here if needed.
  // Set root to null.
  KDTree();

  // deconstructor - use this to clean up all memory that the BST has allocated
  // but not returned with the 'delete' keyword.
  ~KDTree();

  // init_node initializes a new bst_node from the heap using the given
  // data, and two NULL children, and returns a pointer to it.
  kd_node* init_node(string label, float coordinates[2]);

  // insert places the new_node in a proper location in the tree while obeying
  // the invariant. On return, root points to the root of the tree.
  void insert(kd_node* new_node, kd_node* root);

  void remove(int data);

  kd_node* nearest(kd_node* subt, int data);

private:
  // this double pointer always will point to the root pointer of the tree
  kd_node** root;
  // you can add add more private member variables and member functions here if
  // you need
};