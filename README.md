Absolutely! Here's a clean, professional, and detailed **README** tailored for your `linkedList`-based tree structure library:

---

# Linked List Tree Library

A robust C library for managing hierarchical tree structures using linked list nodes. Each node can store data (text or binary), maintain parent-child-sibling relationships, and support recursive operations like traversal, addition, removal, and renaming. Ideal for building in-memory file systems, hierarchical data storage, or tree-based simulations.

---

## Features

* **Dynamic Tree Structure**

  * Parent, children, and sibling relationships for flexible tree representation.
  * Add or remove children dynamically.
  * Support for multiple root-level nodes.

* **Data Storage**

  * Store text or raw binary data within nodes.
  * Track size automatically for each node and its subtree.

* **Traversal**

  * Depth-First Search (DFS) traversal with user-defined callback functions.
  * Tree printing with indentation for visual representation.

* **Node Management**

  * Create, rename, and free nodes recursively.
  * Find nodes by name among children.
  * Compute total size including all descendants.

* **Memory Safety**

  * All allocations are dynamically managed.
  * Recursive freeing ensures no memory leaks.
  * Proper error handling for NULL pointers and empty inputs.

---

## Installation

1. Include the header:

```c
#include "linkedList.h"
```

2. Compile the source file with your project:

```bash
gcc -o your_program main.c linkedList.c
```

---

## API Reference

### Node Creation

```c
ListNode* createNode(char* name);
```

* Creates a new node with the given name.
* Returns `NULL` if name is invalid or memory allocation fails.

---

### Adding and Removing Children

```c
void addChild(ListNode* parent, ListNode* newChild);
void removeChild(ListNode* parent, char* name);
```

* `addChild`: Adds a node as a child of a parent node. Automatically detaches from previous parent if any.
* `removeChild`: Removes and frees a child node (by name) recursively.

---

### Data Management

```c
void addData(ListNode* node, char* data);
void addRawBytes(ListNode* node, uint8_t* data, size_t size);
size_t getSizeWithChildren(ListNode* node);
```

* `addData`: Adds textual data to the node.
* `addRawBytes`: Adds raw binary data to the node.
* `getSizeWithChildren`: Returns total size of a node including all children.

---

### Traversal & Printing

```c
void traverseDFS(ListNode* node, void (*visitFunc)(ListNode*, void*), void* arg);
void printTree(ListNode* node, int depth);
```

* `traverseDFS`: Depth-First Search traversal with a callback function.
* `printTree`: Prints the tree structure starting from a node with indentation representing depth.

---

### Utility Functions

```c
ListNode* findChild(char* name, ListNode* parent);
ListNode* findRoot(ListNode* node);
void renameNode(ListNode* node, char* newName);
void freeNode(ListNode* node);
```

* `findChild`: Searches for a child node by name under a given parent.
* `findRoot`: Returns the root of the tree containing the node.
* `renameNode`: Safely renames a node.
* `freeNode`: Recursively frees a node and all its descendants.

---

## Example Usage

```c
#include "linkedList.h"
#include <stdio.h>

int main() {
    // Create root node
    ListNode* root = createNode("root");

    // Add children
    ListNode* child1 = createNode("child1");
    addChild(root, child1);
    addData(child1, "Hello World!");

    ListNode* child2 = createNode("child2");
    addChild(root, child2);

    // Print the tree
    printTree(root, 0);

    // Traverse with callback
    traverseDFS(root, [](ListNode* node, void* arg){
        printf("Visited: %s\n", node->name);
    }, NULL);

    // Rename a node
    renameNode(child1, "newChild1");

    // Remove a child
    removeChild(root, "child2");

    // Free all nodes
    freeNode(root);
}
```

---

## Contributing

Contributions are welcome! Feel free to submit:

* Bug fixes
* Feature improvements
* Documentation enhancements

---

## License

MIT License – free for personal and commercial use.

---

If you want, I can also **make a visually structured version of this README with a “Tree Diagram Example” and ASCII illustration of `children-sibling-parent` relationships**. It would make the library way easier to understand at a glance.

Do you want me to do that?
