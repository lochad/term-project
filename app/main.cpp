#include "../code/kdtree.h"
#include <iostream>

using namespace std;

int main() {

  std::vector<std::array<float, 2>> points = {
        {2.0, 3.0},
        {5.0, 4.0},
        {9.0, 6.0},
        {4.0, 7.0},
        {8.0, 1.0},
        {7.0, 2.0}
    };

    KDTree tree;
    tree.buildKDTree(points, 2);
    std::cout << "KD-Tree built successfully!" << std::endl;

}