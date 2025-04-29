# Spooky KD Trees

## Overview
******** write about why kd trees use a splitting plane*********************
I wanted to implement a KD tree that could be used for 2 dimensional searches.
In this project, a list and coordinates of Colorado ghost towns are put into a KD tree. The KD tree is used to search for the nearest neighbor and returns the closest ghost town coordinates to a given point.

## KD Tree Intro
KD trees are very similar to BSTs, except they contain dimensions. The dimensions are used as a "splitting plane", so instead of easy searches that BSTs use where they just follow which point is lower or higher, KD trees must compare the point on that plane. For instance, if we are adding a point to the tree, the point gets compared on the x plane first (using the modulo) and goes left if it is smaller and right if it is bigger. Then the same process is done but compared on the y plane, and this continues switching until the end of the tree is reached or the point is placed.

I thought this process was pretty confusing until I drew it out myself. This excellent [video](https://www.youtube.com/watch?v=BK5x7IUTIyU) helps demonstrate how KD trees are built.

### KD invariant
The invariants are generally similar to the BSTs except for the splitting plane. All the invariants are based on multiple dimensions, whereas BSTs are only based on one.

## Methods
The only necessary functions to my program are initoate node, insert, and search. I thought that since this was so similar to BSTs, it wouldn't be too hard (and would be good practice) to implement the rest for KD trees.

### Initiate node
Coordinates can be inserted into this function to return a new node. The node structure has a string label, array<float, 2> coordinates, kd_node *left, and kd_node *right.

### Insert
Insert adds a node to the tree. If the tree is null, the node becomes the pointer. If not, then it starts at the 0 splitting plane (x) and sees if it is bigger or smaller than the current node. It moves left if smaller and right if bigger. If the left or right is empty, then the node moves there. If not, it looks at the 1 splitting plane (y) and does the same process again. This repeats on the planes 2 (x), 3 (y), until a nullptr is reached and the node is inserted.

### Remove
Remove was extremely tricky, but very similar to BSTs. The only major difference was the splitting plane, which gets changed on each recursion. I used three helper functions that all start out by finding the node.
If it has no children, the node is removed and its parent pointer is set to null where the deletion node was.
If it has one child, it looks for which direction the child node is at. Once that is located, the node is deleted and the node's parent points to its child.
Remove two children is similar to one child, except the new node gets chosen based on the smallest value. Then the tree is updated where the new node takes place of the deleted node to keep the invariant.

### Search
Search was the most important function for my end goal. Search (actually called knn) consists of three functions: search, knn, and distanceb.

Search uses euclidean distance to find the distance between the search point and the current point. If that distance is better than the current distance, then it is saved. Then, it continues on this subtree switching planes. Now this part was confusing, but the other side needs to be checked. I watched this [video](https://www.youtube.com/watch?v=mxrUFkdXaR8) to help me understand the logic behind it. Since it's a two dimensional plane, the point on the other side of the tree could be closer than our current point. A lot of videos used a xy coordinate plane as an example, like if one point was at 1,4 and our closest point was 2,5, 1,3 could be on the other side of the tree and be closer. Once we recurse up the "bad" tree, we will have our final point. I used the helper function distanceb to calculate the Euclidean distance.

Lastly, the search function gets used in the knn function. The knn function initializes the best node to null and the best distance to a max large distance so anything we have will be smaller. Then the search function is called and the closest node is returned.

### Get node
Get node was is simple and similar to BSTs except that the recursion is done on the splitting plane. So the first iteration is done on the x axis, then is swtiches to y until the point is found.

### Contains
### Size