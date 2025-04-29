# Spooky KD Trees

## Overview
I wanted to implement a KD tree that could be used for 2 dimensional searches.
In this project, a list and coordinates of Colorado ghost towns are put into a KD tree. The KD tree is used to search for the nearest neighbor and returns the closest ghost town coordinates to a given point.

## KD Tree Intro
KD trees are very similar to BSTs, except they contain dimensions. The dimensions are used as a "splitting plane", so instead of easy searches that BSTs use where they just follow which point is lower or higher, KD trees must compare the point on that plane. For instance, if we are adding a point to the tree, the point gets compared on the x plane first (using the modulo number of dimensions % current depth) and goes left if it is smaller and right if it is bigger. The same process is done but compared on the y plane, and this continues switching until the end of the tree is reached or the point is placed. I thought this process was pretty confusing until I drew it out myself. This excellent [video](https://www.youtube.com/watch?v=BK5x7IUTIyU) helps demonstrate how KD trees are built.

KD trees have a lot of cool applications, like analyzing point cloud data, finding clusters, and finding similar songs on Spotify. I assumed this would be a similar data structure to what Google Maps uses, but they use Dijkstra's algorithm which makes sense since they need to analyze networks.

### Splitting plane
I struggled to understand the beenfits of a splitting plane. The splitting plane helps minimize the amount of searching we are doing by partioning the space and helps to balance the tree. Since BSTs only have one dimension, they are only being searched once. Splitting on the current plane allows the KD tree to focus on one point at a time, like if it was a BST. If the tree focued on all the dimensions at once, it would take a lot longer and be less efficient. 

### KD invariant
The invariants are similar to the BSTs except for the splitting plane. All the invariants are based on multiple dimensions, whereas BSTs are only based on one.

# KD Node
The node structure has a:
* `string label`
* `array<float, 2> coordinates`
* `kd_node *left`
* `kd_node *right`

# KD Tree class
The only necessary functions to my program are initiate node, insert, and search. I thought that since this was so similar to BSTs, it wouldn't be too hard (and would be good practice) to implement the rest for KD trees.

## `init_node`
Coordinates can be inserted into this function to return a new node.

## `insert`
Insert adds a node to the tree. If the tree is null, the node becomes the pointer. If not, then it starts at the 0 splitting plane (x) and sees if it is bigger or smaller than the current node. It moves left if smaller and right if bigger. If the left or right is empty, then the node moves there. If not, it looks at the 1 splitting plane (y) and does the same process again. This repeats on the planes 2 (x), 3 (y), until a nullptr is reached and the node is inserted. It uses a helper function called `insert_helper`.

## `remove`
Remove was extremely tricky, but very similar to BSTs. The only major difference was the splitting plane, which gets changed on each recursion. I used three helper functions that all start out by finding the node. My remove function is very complex, but I spent days on it and could not get it to work in a less complex matter.
* In `remove_no_children`, the node is removed and its parent pointer is set to null where the deletion node was.
* `remove_one_child` looks for which direction the child node is at. Once that is located, the node is deleted and the node's parent points to its child.
* `remove_two_children` is similar to one child, except the new node gets chosen based on the smallest value. Then the tree is updated where the new node takes place of the deleted node to keep the invariant.

## `knn`
Search was the most important function for my end goal. Search (actually called knn) consists of three functions: `search`, `knn`, and `distanceb`.

`search` uses euclidean distance to find the distance between the search point and the current point. If that distance is better than the current distance, then it is saved. Then, it continues on this subtree switching planes. Now this part was confusing, but the other side needs to be checked. I watched this [video](https://www.youtube.com/watch?v=mxrUFkdXaR8) to help me understand the logic behind it. Since it's a two dimensional plane, the point on the other side of the tree could be closer than our current point. A lot of videos used a xy coordinate plane as an example, like if one point was at 1,4 and our closest point was 2,5, 1,3 could be on the other side of the tree and be closer. Once we recurse up the "bad" tree, we will have our final point. I used the helper function `distanceb` to calculate the Euclidean distance.

I used `secondBest` to get the second best node so I could display multiple options. This function completes the search function, but focuses on the return of the second best instead of the best node. The recursion was slightly trickier since a point could be second best recursing up the tree so we had to search for everything and couldn't use the same logic as finding the best. All it took was a few extra if statements to make sure the best distance would be smaller and that the previous best could become the new second best.

Lastly, the `search` function gets used in the `knn` function. `knn` initializes the best node to null and the best distance to a max large distance so anything we have will be smaller. Then `search` is called and the closest node is returned.

## `get_node`
Get node was is simple and similar to BSTs except that the recursion is done on the splitting plane. So the first iteration is done on the x axis, then is swtiches to y until the point is found.

## `contains`
Contains returns true if get_node returns a node and false if it doesn't.

## `size`
Size counts up the points by adding 1 for each recursion and then returns that number.

# Running the program
1. delete the build folder.
2. create a new build folder by running mkdir build
3. navigate to the build folder by running cd build
4. now run cmake ..
5. run make && ./run_app to run the demo.
6. add your x coordinate and press enter
7. add your y coordinate and press enter
8. the program will return the closest ghost town to you.

# Challenges and stretch goals
I have never made a c++ project before, so that took a lot longer than I wanted it to. I did learn lots of valuable lessons like what cmake files actually are and what they look at. Having previous homeworks was extremely useful for this.

Another challenge was understand a KD tree. It was hard since we have had lectures for all the other data structures, but I watched many, many videos and interactive KD tree constructions, and I feel like I understand KD trees really well.

A last challenge I had was creating less complex algorithms. Removal from a KD tree is generally O(log)n. I think my function is closer to O(n) since it uses multiple removal calls.

A stretch goal I have is to upload a file (like a CSV) to the program and have it injest it. I was overconfident in my c++ abilities. I know I could do this in Python relatively quickly, but it took me 30 minutes to learn how to print nicely in c++, so I think this will be further down the road.

My other stretch goal was to return multiple points. I was pretty excited once I completed the search function because I realized how simple it would be. It did turn out slightly harder because I had to duplicate the node and distance and use a lot of if statements to make sure it didn't break its own rules, but it was an simpler part of the project. I had to change my return type to vector, but it was pretty easy to separate them in the knn and second best functions.

# Resources
Here are some of my favorite resources for exploring KD trees:
* [Interactive KD tree building](https://opendsa.cs.vt.edu/ODSA/AV/Development/kd-treeAV.html)
* [Removal in KD trees](https://www.geeksforgeeks.org/deletion-in-k-dimensional-tree/)
* [Great presentation about KD trees](https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/kdtrees.pdf)
* [Cool article about using KD tree in point cloud](https://medium.com/data-science/neighborhood-analysis-kd-trees-and-octrees-for-meshes-and-point-clouds-in-python-19fa96527b77)
* [Great walkthrough of search](https://yasenh.github.io/post/kd-tree/)