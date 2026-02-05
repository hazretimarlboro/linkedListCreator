#include "../inc/linkedList.h"
#include <stdlib.h>
#include <string.h>


void freeNode(ListNode* node)
{
    // --------------------------------------
    // Step 0: Check for NULL
    // --------------------------------------
    if (!node) return;

    // --------------------------------------
    // Step 1: Recursively free all children
    // --------------------------------------
    ListNode* cur = node->children;
    while (cur)
    {
        ListNode* next = cur->sibling; // save next sibling before freeing
        freeNode(cur);                 // recursively free child subtree
        cur = next;                    // move to next sibling
    }

    // --------------------------------------
    // Step 2: Free this node's own data
    // --------------------------------------
    if (node->data)
        free(node->data);

    if (node->name)
        free(node->name);

    // --------------------------------------
    // Step 3: Free the node itself
    // --------------------------------------
    free(node);
}

ListNode* createNode(char* name)
{
    // --------------------------------------
    // Step 0: Input validation
    // --------------------------------------
    // Make sure the provided name is not NULL
    if (!name) return NULL;

    // Reject empty strings as invalid names
    if (strlen(name) == 0) return NULL;

    // --------------------------------------
    // Step 1: Allocate memory for the new node
    // --------------------------------------
    ListNode* listnode = malloc(sizeof(ListNode));
    if (!listnode) return NULL;  // malloc failed

    // --------------------------------------
    // Step 2: Allocate memory for the name string
    // --------------------------------------
    // +1 for the null terminator
    listnode->name = malloc(strlen(name) + 1);
    if (!listnode->name)
    {
        // If allocation fails, free previously allocated node memory to avoid leak
        free(listnode);
        return NULL;
    }

    // Copy the name into the node's name field
    strcpy(listnode->name, name);

    // --------------------------------------
    // Step 3: Initialize all other fields
    // --------------------------------------
    listnode->size = 0;        // size of data (no data yet)
    listnode->data = NULL;     // no data attached yet
    listnode->children = NULL; // no children yet
    listnode->parent   = NULL; // parent not set yet
    listnode->sibling  = NULL; // no siblings yet

    // --------------------------------------
    // Step 4: Return the newly created node
    // --------------------------------------
    return listnode;
}

ListNode* findChild(char* name, ListNode* parent)
{
    // --------------------------------------
    // Step 0: Input validation
    // --------------------------------------
    // Check that the name and parent pointers are valid
    // Also check that the name is not an empty string
    if (!name || !parent || strlen(name) == 0)
        return NULL;

    // --------------------------------------
    // Step 1: Start from the first child of the parent
    // --------------------------------------
    ListNode* cur = parent->children;

    // --------------------------------------
    // Step 2: Traverse the sibling list to find the matching child
    // --------------------------------------
    while (cur)
    {
        // Compare current child's name with the target name
        if (strcmp(cur->name, name) == 0)
        {
            // Match found: return the pointer to this child
            return cur;
        }

        // Move to the next sibling
        cur = cur->sibling;
    }

    // --------------------------------------
    // Step 3: Child not found
    // --------------------------------------
    // If we reached the end of the sibling list without a match, return NULL
    return NULL;
}

void addChild(ListNode* parent, ListNode* newChild)
{
    // Check for invalid input: parent or newChild cannot be NULL
    if (!parent || !newChild) return;

    // --------------------------------------
    // Step 1: Detach newChild from its current parent if it has one
    // --------------------------------------
    if (newChild->parent)
    {
        // Start from the first child of the current parent
        ListNode* cur = newChild->parent->children;
        ListNode* prev = NULL; // keeps track of the previous sibling

        // Traverse the sibling list to find newChild
        while (cur)
        {
            if (cur == newChild) // Found the node to detach
            {
                if (prev)
                    prev->sibling = cur->sibling; // bypass newChild in the sibling list
                else
                    newChild->parent->children = cur->sibling; // newChild was the first child

                break; // node detached, exit loop
            }

            prev = cur;       // move prev pointer forward
            cur = cur->sibling; // move cur pointer forward
        }
    }

    // --------------------------------------
    // Step 2: Add newChild to the new parent's children list
    // --------------------------------------
    newChild->parent = parent;            // set the new parent pointer
    newChild->sibling = parent->children; // insert at the front of the children list
    parent->children = newChild;          // update parent's children to point to newChild
}


void removeChild(ListNode* parent, char* name)
{
    // --------------------------------------
    // Step 0: Input validation
    // --------------------------------------
    // Make sure the parent node and name are valid
    if (!parent || !name || strlen(name) == 0)
        return;

    // --------------------------------------
    // Step 1: Initialize pointers to traverse the children list
    // --------------------------------------
    ListNode* prev = NULL;           // tracks previous child
    ListNode* cur = parent->children; // current child we are examining

    // --------------------------------------
    // Step 2: Traverse the children list
    // --------------------------------------
    while (cur)
    {
        // Check if the current child's name matches the target
        if (strcmp(cur->name, name) == 0)
        {
            // Remove current child from the sibling list
            if (prev)
                prev->sibling = cur->sibling; // bypass cur
            else
                parent->children = cur->sibling; // cur was the first child

            // Save pointer to free memory
            ListNode* tofree = cur;

            // Move cur to next sibling before freeing
            cur = cur->sibling;

            // Recursively free the node and all its descendants
            freeNode(tofree);

            // Exit after removing the first matching child
            return;
        }
        else
        {
            // Move prev and cur forward if no match
            prev = cur;
            cur = cur->sibling;
        }
    }

    // --------------------------------------
    // Step 3: If no child matches, function ends
    // --------------------------------------
}

void traverseDFS(ListNode* node, void (*visitFunc)(ListNode*, void*), void* arg)
{
    // --------------------------------------
    // Step 0: Input validation
    // --------------------------------------
    // If the node is NULL, there's nothing to traverse
    if (!node) return;

    // --------------------------------------
    // Step 1: Visit the current node
    // --------------------------------------
    // Call the user-provided function on this node
    // `arg` is a generic pointer that can carry extra information/context
    visitFunc(node, arg);

    // --------------------------------------
    // Step 2: Recursively traverse all children
    // --------------------------------------
    ListNode* child = node->children;
    while (child)
    {
        // Recursively traverse each child subtree
        traverseDFS(child, visitFunc, arg);

        // Move to the next sibling
        child = child->sibling;
    }

    // --------------------------------------
    // Step 3: Done
    // --------------------------------------
}

size_t getSizeWithChildren(ListNode* node)
{
    // --------------------------------------
    // Step 0: Input validation
    // --------------------------------------
    if (!node) return 0;

    // --------------------------------------
    // Step 1: Start with the current node's data size
    // --------------------------------------
    size_t size = node->size; // include this node's own data

    // --------------------------------------
    // Step 2: Recursively add sizes of all children
    // --------------------------------------
    for (ListNode* cur = node->children; cur; cur = cur->sibling)
    {
        size += getSizeWithChildren(cur); // recursively sum child sizes
    }

    // --------------------------------------
    // Step 3: Return total size
    // --------------------------------------
    return size;
}

void addData(ListNode* node, char* data)
{
    // --------------------------------------
    // Step 0: Input validation
    // --------------------------------------
    // Make sure the node and data pointers are valid
    // Also reject empty strings
    if (!node || !data || strlen(data) == 0)
        return;

    // --------------------------------------
    // Step 1: Free old data if it exists
    // --------------------------------------
    // Prevent memory leaks by freeing previous data
    if (node->data)
        free(node->data);

    // --------------------------------------
    // Step 2: Allocate memory for the new data
    // --------------------------------------
    size_t len = strlen(data);           // get length of string
    node->data = malloc(len + 1);        // +1 for null terminator
    if (!node->data) return;             // check malloc success

    // --------------------------------------
    // Step 3: Copy the data into the node
    // --------------------------------------
    memcpy(node->data, data, len + 1);   // copy including null terminator

    // --------------------------------------
    // Step 4: Update the node's size
    // --------------------------------------
    node->size = len;                    // store length of the data
}

void addRawBytes(ListNode* node, uint8_t* data, size_t size)
{
    // --------------------------------------
    // Step 0: Input validation
    // --------------------------------------
    // Ensure the node is valid, data is not NULL, and size is non-zero
    if (!node || !data || size == 0) return;

    // --------------------------------------
    // Step 1: Free any previously stored data
    // --------------------------------------
    if (node->data)
        free(node->data);  // prevent memory leaks

    // --------------------------------------
    // Step 2: Allocate memory for the new raw data
    // --------------------------------------
    node->data = malloc(size);   // allocate exactly 'size' bytes
    if (!node->data) return;     // check malloc success

    // --------------------------------------
    // Step 3: Copy the raw bytes into node->data
    // --------------------------------------
    memcpy(node->data, data, size); // copy binary data

    // --------------------------------------
    // Step 4: Update node size
    // --------------------------------------
    node->size = size;             // store the size of the raw data
}

void printTree(ListNode* node, int depth)
{
    // --------------------------------------
    // Step 0: Input validation
    // --------------------------------------
    if (!node) return; // nothing to print

    // --------------------------------------
    // Step 1: Print indentation based on depth
    // --------------------------------------
    for (int i = 0; i < depth; i++)
        printf("  "); // two spaces per level to visualize tree structure

    // --------------------------------------
    // Step 2: Print the node's name and size
    // --------------------------------------
    printf("%s (size=%zu)\n", node->name, node->size);

    // --------------------------------------
    // Step 3: Recursively print all children
    // --------------------------------------
    for (ListNode* c = node->children; c; c = c->sibling)
        printTree(c, depth + 1); // increase depth for proper indentation
}

ListNode* findRoot(ListNode* node)
{
    // --------------------------------------
    // Step 0: Input validation
    // --------------------------------------
    if (!node) return NULL;  // nothing to traverse

    // --------------------------------------
    // Step 1: Start from current node
    // --------------------------------------
    ListNode* cur = node;

    // --------------------------------------
    // Step 2: Climb up the parent chain until root
    // --------------------------------------
    while (cur->parent)        // while there is a parent
        cur = cur->parent;     // move up one level

    // --------------------------------------
    // Step 3: Return the root node
    // --------------------------------------
    return cur;
}

void renameNode(ListNode* node, char* newName)
{
    // --------------------------------------
    // Step 0: Input validation
    // --------------------------------------
    // Make sure the node and newName are valid
    if (!node || !newName || strlen(newName) == 0)
        return;

    // --------------------------------------
    // Step 1: Check if the name is already the same
    // --------------------------------------
    // If the current name equals the new name, no action needed
    if (node->name && strcmp(node->name, newName) == 0)
        return;

    // --------------------------------------
    // Step 2: Free the old name
    // --------------------------------------
    // Avoid memory leaks by freeing previously allocated string
    free(node->name);

    // --------------------------------------
    // Step 3: Allocate memory for the new name
    // --------------------------------------
    node->name = malloc(strlen(newName) + 1);  // +1 for null terminator
    if (!node->name) return;                   // check malloc success

    // --------------------------------------
    // Step 4: Copy the new name into the node
    // --------------------------------------
    strcpy(node->name, newName);              // copy including null terminator
}