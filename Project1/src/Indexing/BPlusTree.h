//
// Created by Jia Ming Sim on 7/10/23.
//

#ifndef PROJECT1_BPLUSTREE_H
#define PROJECT1_BPLUSTREE_H

#pragma once

#include <vector>
#include "Storage/Address.h"

using namespace std;

const int nodeSize = 22;

struct Key
{
    float val;
    void *address;
};

class Node
{
public:
    bool is_leaf;
    int size;
    Key keys[nodeSize + 1];
    Node *children[nodeSize + 2];

    Node()
    {
        is_leaf = true;
        size = 0;
        for (int i = 0; i <= nodeSize; i++)
        {
            children[i] = nullptr;
            keys[i].val = 0;
            keys[i].address = nullptr;
        }
        children[nodeSize + 1] = nullptr;
    }
};

class BPlusTree {
public:
    BPlusTree();

    void insert(float val, void *address);
    void insertRecursive(Node *current, float val, void *address);
    void splitLeaf(Node *leaf);
    void insertIntoParent(Node *leftChild, float val, Node *rightChild);
    void splitParent(Node *parent);
    Node* findParent(Node *current, Node *child);

    void getRootValue();
    int getNumberOfLevels();
    int countLevels(Node *node);
    int getNumberOfNodes();
    int countNodes(Node *node);
    int countLeafNodes(Node *node);
    void printTree();
    void resetCounters();

    bool search(float val);
    bool searchRecursive(Node *current, float val);
    int getIndexNodeAccessCount() const;
    int getNumOfIndexNodeAccessed(float start, float end);
    vector<Address *> retrieveRange(float start, float end, int &rangeIndexNodesAccessed) const;

    void remove(float val);
    bool removeRecursive(Node *current, float val);
    void handleLeafUnderflow(Node *leaf);
    void handleNonLeafUnderflow(Node *nonLeafNode, int index);
    void removeLessThanOrEqual(float key);

    long long timeTakenToRemove(float key);
    long long timeTakenToRetrieveRecords(float start, float end, int &rangeIndexNodesAccessed) const;
};

#endif //PROJECT1_BPLUSTREE_H
