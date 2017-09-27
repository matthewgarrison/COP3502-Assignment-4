# COP3502H (Computer Science 1 Honors) Assignment 4

### How to use this heap:

1. Download segfault_stars_heap.c and segfault_stars_heap.h and compile them.
2. Use the following commands: add n (inserts n into the heap), pull (removes and returns the minimum value in the heap), and peek (returns the minimum value in the heap). 

### Details:

This is a new implementation of a min-heap. To the best of our knowledge, this data structure is unique and a similar version does not exist elsewhere.

Runtimes:
* O(1) peek-min
* O(1) delete-min
* O(log(n)) average case insert
* O(n) worst case insert

We used empirical runtime analysis to determine the average case runtime. However, we are not experts at this, so our conclusions may be incorrect. 

This data structure has O(n) space complexity. However, it has a fairly high constant factor, because each node maintains 4 pointers to other nodes.

How insert works:
1. Start at the head of the list.
2. If the value you are inserting is greater than or equal to the value at the current node, go down a level (ie. look at the current node’s list of children).
3. Otherwise, look at the next node in that level.
4. If the node is NULL, then insert the value there.

How pull (peek-min and delete-min) works:
1. First, we find the value to pull. This is just grabbing the tail of the root’s list of children.
2. If the tail has siblings (i.e. the root has multiple children), we have two cases. If the tail has no children, we just remove it from the list. If it has children, we append them to the list of the root’s children.
3. Otherwise, we set the root’s head and tail pointers to the head and tail pointers of the children of the node we’re removing (if the node we’re removing has no children, then this just sets those to NULL).
4. Finally, we return the value of the node we pulled.

Future considerations:
* A key weakness of this heap is its O(n) worst case for insert - if a series of data is presented in sorted order, this will result in what is effectively a doubly-linked list, with no nodes containing any children.  A solution to this is to periodically employ a balancing algorithm, to maintain an O(log(n)) insert time.  This would also reduce sorting time to O(nlog(n)).
* Another area for exploration would be reduction of memory overhead.  Currently, each node requires knowledge of four other nodes - its previous sibling, its next sibling, and the head and tail of its list of children; in contrast, nodes in many other heaps have pointers to only two other nodes.  Eliminating pointers to other nodes would reduce memory usage and increase its practical speed.
