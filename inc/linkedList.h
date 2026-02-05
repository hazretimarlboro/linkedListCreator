#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stddef.h>
#include <stdint.h>

typedef struct ListNode ListNode;

struct ListNode
{
    char* name;
    size_t size;
    uint8_t* data;
    ListNode* sibling;
    ListNode* parent;
    ListNode* children;
};

ListNode* createNode(char* name);
ListNode* findChild(char* name, ListNode* parent);
ListNode* findRoot(ListNode* node);
size_t    getSizeWithChildren(ListNode* node);
void      addChild(ListNode* parent, ListNode* newChild);
void      removeChild(ListNode* parent, char* name);
void      freeNode(ListNode* node);
void      traverseDFS(ListNode* node, void (*visitFunc)(ListNode*, void*),void* arg);
void      addData(ListNode* node, char* data);
void      addRawBytes(ListNode* node, uint8_t* data, size_t size);
void      printTree(ListNode* node, int depth);
void      renameNode(ListNode* node, char* newName);

#endif