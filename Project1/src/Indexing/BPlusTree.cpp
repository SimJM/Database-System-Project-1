#include <iostream>
#include <queue>
#include <vector>
#include "Storage/Address.h"

const int nodeSize = 22;

struct Key {
    float val;
    void* address;
};

class Node {
public:
    bool is_leaf;
    int size;
    Key keys[nodeSize+1];
    Node* children[nodeSize+2];

    Node() {
        is_leaf = true;
        size = 0;
        for (int i = 0; i <= nodeSize; i++) {
            children[i] = nullptr;
            keys[i].val = 0;
            keys[i].address = nullptr;
        }
        children[nodeSize+1] = nullptr;
    }
};

class BPlusTree {
public:
    int indexNodeAccessCount = 0;
    Node* root;

    BPlusTree() {
        root = nullptr;
    }

    void insert(float val, void* address) {
        if (root == nullptr) {
            root = new Node();
            root->keys[0].val = val;
            root->keys[0].address = address;
            root->size = 1;
        } else {
            insertRecursive(root, val, address);
        }
    }

    void insertRecursive(Node* current, float val, void* address) {
        if (current->is_leaf) {
            int i = current->size - 1;
            while (i >= 0 && val < current->keys[i].val) {
                current->keys[i + 1] = current->keys[i];
                i--;
            }

            current->keys[i + 1].val = val;
            current->keys[i + 1].address = address;
            current->size++;

            if (current->size > nodeSize) {
                splitLeaf(current);
            }
        }
        else {
            int i = 0;
            while (i < current->size && val > current->keys[i].val) {
                i++;
            }
            insertRecursive(current->children[i], val, address);
        }
    }

    void splitLeaf(Node* leaf) {
        Node* newLeaf = new Node();
        newLeaf->is_leaf = true;
        int splitIndex = (nodeSize + 1) / 2;

        for (int i = splitIndex; i < leaf->size; i++) {
            newLeaf->keys[i - splitIndex] = leaf->keys[i];
        }

        newLeaf->size = leaf->size - splitIndex;
        leaf->size = splitIndex;

        newLeaf->children[nodeSize] = leaf->children[nodeSize];
        leaf->children[nodeSize] = newLeaf;

        insertIntoParent(leaf, newLeaf->keys[0].val, newLeaf);
    }

    void insertIntoParent(Node* leftChild, float val, Node* rightChild) {
        if (root == leftChild) {
            Node* newRoot = new Node();
            newRoot->keys[0].val = val;
            newRoot->children[0] = leftChild;
            newRoot->children[1] = rightChild;
            newRoot->size = 1;
            root = newRoot;
            root->is_leaf = false;
        }
        else {
            Node* parent = findParent(root, leftChild);
            int i = 0;
            while (i < parent->size && val > parent->keys[i].val) {
                i++;
            }

            for (int j = parent->size; j > i; j--) {
                parent->keys[j] = parent->keys[j - 1];
                parent->children[j + 1] = parent->children[j];
            }

            parent->keys[i].val = val;
            parent->children[i + 1] = rightChild;
            parent->size++;

            if (parent->size > nodeSize) {
                splitParent(parent);
            }
        }
    }

    void splitParent(Node* parent) {
        Node* newParent = new Node();
        int splitIndex = (nodeSize + 1) / 2;

        newParent->size = parent->size - splitIndex - 1;
        for (int i = splitIndex + 1, j = 0; i < parent->size; i++, j++) {
            newParent->keys[j] = parent->keys[i];
        }

        for (int i = splitIndex + 1, j = 0; i <= parent->size; i++, j++) {
            newParent->children[j] = parent->children[i];
        }

        parent->size = splitIndex;
        newParent->is_leaf = false;
        insertIntoParent(parent, parent->keys[splitIndex].val, newParent);
    }

    Node* findParent(Node* current, Node* child) {
        if (current == nullptr) {
            return nullptr;
        }
        if (current->is_leaf) {
            return nullptr;
        }
        if (current == child) {
            std::cout << "error" << std::endl;
            return nullptr;
        }
        for (int i = 0; i <= current->size; i++) {
            if (current->children[i] == child) {
                return current;
            }
            else if (i == current->size || child->keys[0].val < current->keys[i].val) {
                return findParent(current->children[i], child);
            }
        }
        std::cout << "Error in findParent()" <<std::endl;
        return nullptr;
    }

    void getRootValue() {
        if (root == nullptr) {
            std::cerr << "Tree is empty." << std::endl;
            return;
        }

        std::cout << "Content of root - keys: [";
        for (int i = 0; i < root->size; i++) {
            std::cout << root->keys[i].val;
            if (i < root->size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    int getNumberOfLevels() {
        return countLevels(root);
    }

    int countLevels(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        if (node->is_leaf) {
            return 1;
        }

        int maxChildLevels = 0;
        for (int i = 0; i <= node->size; i++) {
            int childLevels = countLevels(node->children[i]);
            if (childLevels > maxChildLevels) {
                maxChildLevels = childLevels;
            }
        }

        return 1 + maxChildLevels;
    }

    int getNumberOfNodes() {
        return countNodes(root);
    }

    int countNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int count = 1;

        if (node->is_leaf== false) {
            for (int i = 0; i <= node->size; i++) {
                count += countNodes(node->children[i]);
            }
        }

        return count;
    }

    int countLeafNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        if (node->is_leaf) {
            return 1;
        }

        int count = 0;
        for (int i = 0; i <= node->size; i++) {
            count += countLeafNodes(node->children[i]);
        }
        return count;
    }

    void printTree() {
        if (root == nullptr) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int nodeCount = (int) q.size();
            while (nodeCount > 0) {
                Node* node = q.front();
                q.pop();
                std::cout << "[ ";
                for (int i = 0; i < node->size; i++) {
                    std::cout << node->keys[i].val << " ";
                }
                std::cout << "] ";

                if (!node->is_leaf) {
                    for (int i = 0; i <= node->size; i++) {
                        q.push(node->children[i]);
                    }
                }

                nodeCount--;
            }
            std::cout << std::endl;
        }
    }
    bool search(float val) {
        resetCounters();
        return searchRecursive(root, val);
    }

    void resetCounters() {
        indexNodeAccessCount = 0;
    }

    bool searchRecursive(Node* current, float val) {
        if (current == nullptr) {
            return false;
        }
        if (current->is_leaf) {
            indexNodeAccessCount++;
            for (int i = 0; i < current->size; i++) {
                if (current->keys[i].val == val) {
                    return true;
                }
            }
            return false;
        }
        else {
            indexNodeAccessCount++;
            int i = 0;
            while (i < current->size && val > current->keys[i].val) {
                i++;
            }
            return searchRecursive(current->children[i], val);
        }
    }


    int getIndexNodeAccessCount() const {
        return indexNodeAccessCount;
    }

    int getNumOfIndexNodeAccessed(float start, float end) {
        int rangeindexNodesAccessed = 0;
        retrieveRange(start, end, rangeindexNodesAccessed);
        return rangeindexNodesAccessed;
    }

    std::vector<Address*> retrieveRange(float start, float end, int &rangeindexNodesAccessed) {
        rangeindexNodesAccessed = 0;
        std::vector<Address*> recordAddresses;

        Node* current = root;

        while (!current->is_leaf) {
            rangeindexNodesAccessed++;
            int i = 0;
            while (i < current->size && start > current->keys[i].val) {
                i++;
            }
            current = current->children[i];
        }
        while (current != nullptr) {
            bool shouldIncrement = false;
            for (int i = 0; i < current->size; i++) {
                if (current->keys[i].val >= start && current->keys[i].val <= end) {
                    Address* addressPtr = static_cast<Address*> (current->keys[i].address);
                    recordAddresses.push_back(addressPtr);
                    shouldIncrement = true;
                }
                else if (current->keys[i].val > end) {
                    if (shouldIncrement) {
                        rangeindexNodesAccessed++;
                    }
                    return recordAddresses;
                }
            }
            if (shouldIncrement) {
                rangeindexNodesAccessed++;
            }
            current = current->children[nodeSize];
        }

        return recordAddresses;
    }

    void remove(float val) {
        if (root == nullptr){
            return;
        }

        while (removeRecursive(root, val)) {
            if (root->size == 0 && !root->is_leaf) {
                Node* oldRoot = root;
                root = root->children[0];
                delete oldRoot;
            }
        }
    }

    bool removeRecursive(Node* current, float val) {
        int i = 0;
        while (i < current->size && val > current->keys[i].val) {
            i++;
        }

        if (current->is_leaf) {
            if (i < current->size && current->keys[i].val == val) {
                for (i; i < current->size - 1; i++) {
                    current->keys[i] = current->keys[i + 1];
                    if(i==current->size -2){
                        current->keys[i+1].val = 0;
                    }
                }
                current->size--;
                if (current->size < (nodeSize+1) / 2 ) {
                    handleLeafUnderflow(current);
                }
                return true;
            }
            return false;
        }
        else {
            if (i < current->size && current->keys[i].val == val) {
                Node* successorNode = current->children[i+1];
                while (!successorNode->is_leaf) {
                    successorNode = successorNode->children[0];
                }
                float successorVal = successorNode->keys[0].val;
                if (removeRecursive(current->children[i+1], successorVal)) {
                    successorNode = current->children[i+1];
                    while (!successorNode->is_leaf) {
                        successorNode = successorNode->children[0];
                    }
                    current->keys[i].val = successorNode->keys[0].val;
                    return true;
                }
                else {
                    return false;
                }
            }

            if (removeRecursive(current->children[i], val)) {
                // Check for underflow in the internal node
                if (current->children[i]->size < (nodeSize+1) / 2 - 1) {
                    handleNonLeafUnderflow(current, i);
                }
                if (i < current->size && current->keys[i].val == val) { // This key in the internal node needs update
                    current->keys[i].val = current->children[i+1]->keys[0].val;
                }
                return true;
            }
            return false;
        }
    }


    void handleLeafUnderflow(Node* leaf) {
        Node* leftSibling = nullptr;
        Node* rightSibling = nullptr;
        Node* parent = findParent(root, leaf);

        int indexInParent = -1;
        for (int i = 0; i < parent->size && indexInParent == -1; i++) {
            if (parent->children[i+1] == leaf) {
                indexInParent = i;
                leftSibling = parent->children[i];

                if (i+2 <= parent->size) {
                    rightSibling = parent->children[i+2];
                } else {
                    rightSibling = nullptr;
                }
            }
        }
        // Borrow from the left sibling
        if (leftSibling && leftSibling->size > (nodeSize+1) / 2 ) {

            for (int i = leaf->size; i > 0; i--) {
                leaf->keys[i] = leaf->keys[i - 1];
            }

            leaf->keys[0] = leftSibling->keys[leftSibling->size - 1];
            parent->keys[indexInParent] = leaf->keys[0];

            leaf->size++;
            leftSibling->size--;
        }
            // Borrow from the right sibling
        else if (rightSibling && rightSibling->size > (nodeSize+1) / 2 ) {
            leaf->keys[leaf->size] = rightSibling->keys[0];
            parent->keys[indexInParent+1] = rightSibling->keys[0];
            for (int i = 0; i < rightSibling->size - 1; i++) {
                rightSibling->keys[i] = rightSibling->keys[i + 1];
            }
            leaf->size++;
            rightSibling->size--;
        }
            // Merge with the left sibling
        else if (leftSibling) {
            for (int i = 0, j = leftSibling->size; i < leaf->size; i++, j++) {
                leftSibling->keys[j] = leaf->keys[i];
            }
            leftSibling->size += leaf->size;
            leftSibling->children[nodeSize] = leaf->children[nodeSize];

            // update parent
            for (int i = indexInParent; i < parent->size - 1; i++) {
                parent->keys[i] = parent->keys[i + 1];
                parent->children[i + 1] = parent->children[i + 2];
                if(i == parent->size-2){
                    parent->keys[parent->size-1].val = 0;
                }
            }
            parent->size--;

            delete leaf;
        }
            // Merge with the right sibling
        else if (rightSibling) {
            for (int i = 0, j = leaf->size; i < rightSibling->size; i++, j++) {
                leaf->keys[j] = rightSibling->keys[i];
            }
            leaf->size += rightSibling->size;
            leaf->children[nodeSize] = rightSibling->children[nodeSize];

            // update parent key
            for (int i = indexInParent + 1; i < parent->size - 1; i++) {
                parent->keys[i] = parent->keys[i + 1];
                parent->children[i + 1] = parent->children[i + 2];
            }
            parent->size--;

            delete rightSibling;
        }
    }

    void handleNonLeafUnderflow(Node* nonLeafNode, int index) {
        Node* leftSibling;
        Node* rightSibling;

        if (index > 0) {
            leftSibling = nonLeafNode->children[index - 1];
        }
        else {
            leftSibling = nullptr;
        }

        if (index < nonLeafNode->size) {
            rightSibling = nonLeafNode->children[index + 1];
        }
        else {
            rightSibling = nullptr;
        }
        Node* child = nonLeafNode->children[index];

        // Borrow from the left sibling
        if (leftSibling && leftSibling->size > (nodeSize+1) / 2 - 1) {
            for (int i = child->size; i > 0; i--) {
                child->keys[i] = child->keys[i - 1];
                child->children[i + 1] = child->children[i];
            }
            child->children[1] = child->children[0];

            child->keys[0] = nonLeafNode->keys[index - 1];
            nonLeafNode->keys[index - 1] = leftSibling->keys[leftSibling->size - 1];
            child->children[0] = leftSibling->children[leftSibling->size];

            child->size++;
            leftSibling->size--;
        }
            // Borrow from the right sibling
        else if (rightSibling && rightSibling->size > (nodeSize+1) / 2 - 1) {
            child->keys[child->size] = nonLeafNode->keys[index];
            nonLeafNode->keys[index] = rightSibling->keys[0];
            child->children[child->size + 1] = rightSibling->children[0];

            for (int i = 0; i < rightSibling->size - 1; i++) {
                rightSibling->keys[i] = rightSibling->keys[i + 1];
                rightSibling->children[i] = rightSibling->children[i + 1];
            }
            rightSibling->children[rightSibling->size - 1] = rightSibling->children[rightSibling->size];

            child->size++;
            rightSibling->size--;
        }
            // Merge with the left sibling
        else if (leftSibling) {
            leftSibling->keys[leftSibling->size] = nonLeafNode->keys[index - 1];
            for (int i = 0, j = leftSibling->size + 1; i < child->size; i++, j++) {
                leftSibling->keys[j] = child->keys[i];
                leftSibling->children[j] = child->children[i];
            }
            leftSibling->children[leftSibling->size + child->size + 1] = child->children[child->size];
            leftSibling->size += child->size + 1;

            // update parent
            for (int i = index - 1; i < nonLeafNode->size - 1; i++) {
                nonLeafNode->keys[i] = nonLeafNode->keys[i + 1];
                nonLeafNode->children[i + 1] = nonLeafNode->children[i + 2];
            }
            nonLeafNode->size--;

            delete child;
        }
            // Merge with the right sibling
        else if (rightSibling) {
            child->keys[child->size] = nonLeafNode->keys[index];
            for (int i = 0, j = child->size + 1; i < rightSibling->size; i++, j++) {
                child->keys[j] = rightSibling->keys[i];
                child->children[j] = rightSibling->children[i];
            }
            child->children[child->size + rightSibling->size + 1] = rightSibling->children[rightSibling->size];
            child->size += rightSibling->size + 1;

            // update parent
            for (int i = index; i < nonLeafNode->size - 1; i++) {
                nonLeafNode->keys[i] = nonLeafNode->keys[i + 1];
                nonLeafNode->children[i + 1] = nonLeafNode->children[i + 2];
            }
            nonLeafNode->size--;

            delete rightSibling;
        }
    }
    void removeLessThanOrEqual(float key) {
        if (root == nullptr) {
            return;
        }
        while (root!=nullptr){
            Node* current = root;
            while (!current->is_leaf) {
                current=current->children[0];
            }
            if (current->keys[0].val > key) {
                return;
            }
            else{
                remove(current->keys[0].val);
            }
        }
    }
};
