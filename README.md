# Red-Black-Tree
Overview
This project implements a Red-Black Tree, a self-balancing binary search tree. The tree maintains an efficient structure with a guaranteed logarithmic height to provide optimal performance for search, insertion, and deletion operations. This implementation includes several advanced features, such as node insertion, balancing via rotations, tree balance checking, and search operations.

Key Features:
Node Structure:

Each node in the tree contains a key, color (either RED or BLACK), and pointers to its left, right, and parent nodes.
Insertion with Fixing Violations:

The insert function ensures that nodes are inserted while preserving the binary search tree property. If any Red-Black Tree properties are violated, the tree rebalances itself using rotations and recoloring.
Rotation Operations:

The implementation includes left rotation and right rotation to maintain the tree's balance after insertion.
Search Operation:

Search for a node by key in O(log n) time.
Inorder Traversal:

Inorder traversal is implemented to print the elements of the tree in sorted order. The color of each node (RED or BLACK) is also displayed.
Tree Height and Balance Checking:

The program calculates and prints the height of the tree and checks if the Red-Black properties are maintained, ensuring the tree is balanced.
Future Enhancements:

Delete Operation: Delete nodes while maintaining balance (not yet implemented).
Multi-threading Support: Thread safety can be added for concurrent access.
Memory Pooling: Optimized memory allocation can be integrated for large datasets.
Unit Testing:

Ensure that the Red-Black Tree functions correctly with a series of unit tests.
Usage:
Inserting Nodes: Insert nodes into the Red-Black Tree using the insert function. The tree will automatically rebalance itself if necessary.

Search Nodes: Search for a node by its key using the search function.

Print the Tree: Perform an inorder traversal using inorderTraversal to see the sorted tree elements with their colors.

Check Tree Balance: The checkBalance function verifies that the Red-Black Tree properties hold true, ensuring the tree is balanced.
