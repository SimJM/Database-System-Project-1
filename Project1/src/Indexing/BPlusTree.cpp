#include <iostream>
#include <queue>
#include <vector>

const int nodeSize = 3; // Define the node size (parameter) here

struct Key {
    float val;     // Value of the key
    void* address; // Address corresponding to the value
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
            // Inserting the value at the right place
            int i = current->size - 1;
            while (i >= 0 && val < current->keys[i].val) {
                current->keys[i + 1] = current->keys[i];
                i--;
            }

            current->keys[i + 1].val = val;
            current->keys[i + 1].address = address;
            current->size++;
            // Split the leaf node if necessary
            if (current->size > nodeSize) {
                splitLeaf(current);
            }
        }
        else {
            // Find the appropriate child node to insert the key using recursion
            int i = 0;
            while (i < current->size && val > current->keys[i].val) {
                i++;
            }
            insertRecursive(current->children[i], val, address);
        }
    }

    // Function to split a leaf node
    void splitLeaf(Node* leaf) {
        Node* newLeaf = new Node();
        newLeaf->is_leaf = true;
        int splitIndex = (nodeSize + 1) / 2;

        // Copying 2nd half of the original leaf to new leaf
        for (int i = splitIndex; i < leaf->size; i++) {
            newLeaf->keys[i - splitIndex] = leaf->keys[i];
        }

        newLeaf->size = leaf->size - splitIndex;
        leaf->size = splitIndex;

        // updating the rightmost pointer to keep in correct sequence
        newLeaf->children[nodeSize] = leaf->children[nodeSize];
        leaf->children[nodeSize] = newLeaf;

        insertIntoParent(leaf, newLeaf->keys[0].val, newLeaf);
    }

    // Function to insert a new child node into a parent node
    void insertIntoParent(Node* leftChild, float val, Node* rightChild) {
        if (root == leftChild) {
            // if the left child was the root itself, we need a new root
            Node* newRoot = new Node();
            newRoot->keys[0].val = val;
            newRoot->children[0] = leftChild;
            newRoot->children[1] = rightChild;
            newRoot->size = 1;
            root = newRoot;
            root->is_leaf = false;
        }
        else {
            // Find the parent node and insert val and rightChild into it
            Node* parent = findParent(root, leftChild);
            int i = 0;
            while (i < parent->size && val > parent->keys[i].val) {
                i++;
            }

            // Shift keys and children to make space for the new entry
            for (int j = parent->size; j > i; j--) {
                parent->keys[j] = parent->keys[j - 1];
                parent->children[j + 1] = parent->children[j];
            }

            parent->keys[i].val = val;
            parent->children[i + 1] = rightChild;
            parent->size++;

            // Split the parent if necessary
            if (parent->size > nodeSize) {
                splitParent(parent);
            }
        }
    }

    // Function to split a parent node
    void splitParent(Node* parent) {
        Node* newParent = new Node();
        int splitIndex = (nodeSize + 1) / 2;

        // Copying the 2nd half of keys and children to the new parent
        newParent->size = parent->size - splitIndex - 1;
        for (int i = splitIndex + 1, j = 0; i < parent->size; i++, j++) {
            newParent->keys[j] = parent->keys[i];
        }

        for (int i = splitIndex + 1, j = 0; i <= parent->size; i++, j++) {
            newParent->children[j] = parent->children[i];
        }
        // Update the sizes of the original parent and the new parent
        parent->size = splitIndex;
        newParent->is_leaf = false;

        // Insert the new parent into its parent node (recursively)
        insertIntoParent(parent, parent->keys[splitIndex].val, newParent);
    }

    // Function to find the parent node of a given child node
    Node* findParent(Node* current, Node* child) {
        if (current == nullptr) {
            return nullptr;
        }
        if (current->is_leaf) {
            return nullptr;
        }
        if (current == child) {
            std::cout << "error" << std::endl;
            return nullptr;//changed from child to nullptr //new
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

    // Function to get the root node's key value
    void getRootValue() {
        if (root == nullptr) {
            std::cerr << "Tree is empty." << std::endl;
            return;
        }

        std::cout << "Content of root - keys: [";
        for (int i = 0; i < root->size; i++) {
            std::cout << root->keys[i].val;
            // Add a space or comma if it's not the last value
            if (i < root->size - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }

    // Function to get the number of levels in the tree
    int getNumberOfLevels() {
        return countLevels(root);
    }

    // Function to count the levels of the tree
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

    // Function to get the number of nodes in the tree
    int getNumberOfNodes() {
        return countNodes(root);
    }

    // Function to count the nodes in the tree (used by getNumberOfNodes)
    int countNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        int count = 1; // Count the current node

        if (node->is_leaf== false) {
            for (int i = 0; i <= node->size; i++) {
                count += countNodes(node->children[i]); // Recursively count child nodes
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

        std::queue<Node*> q; //store pointers to nodes
        q.push(root); //push root into queue to begin traversal from root

        while (!q.empty()) {
            int nodeCount = (int) q.size();
            while (nodeCount > 0) {
                Node* node = q.front();
                q.pop();

                // Print keys of the current node
                std::cout << "[ ";
                for (int i = 0; i < node->size; i++) {
                    std::cout << node->keys[i].val << " ";
                }
                std::cout << "] ";

                // If it's not a leaf node, enqueue its children
                if (!node->is_leaf) {
                    for (int i = 0; i <= node->size; i++) {
                        q.push(node->children[i]);
                    }
                }

                nodeCount--;
            }
            std::cout << std::endl; // Newline after each level
        }
    }
    bool search(float val) {
        resetCounters();
        return searchRecursive(root, val);
    }

    // Reset the counters
    void resetCounters() {
        indexNodeAccessCount = 0;
    }

    // Recursive search function
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

    std::vector<void*> retrieveRange(float start, float end, int &rangeindexNodesAccessed) {
        rangeindexNodesAccessed = 0;
        std::vector<void*> recordAddresses;

        Node* current = root;

        // Go to the leaf node that should contain the start of the range
        while (!current->is_leaf) {
            rangeindexNodesAccessed++; // accessed an index node
            int i = 0;
            while (i < current->size && start > current->keys[i].val) {
                i++;
            }
            current = current->children[i];
        }
        // Current is now at the 1st leaf node
        while (current != nullptr) {
            bool shouldIncrement = false;
            for (int i = 0; i < current->size; i++) {
                if (current->keys[i].val >= start && current->keys[i].val <= end) {
                    recordAddresses.push_back(current->keys[i].address);
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

        while (removeRecursive(root, val)) { //keeping doing until removeRecursive is false
            // If the root node has 0 keys left, make its only child the new root
            if (root->size == 0 && !root->is_leaf) {
                Node* oldRoot = root;
                root = root->children[0];
                delete oldRoot;
            }
        }
    }

    bool removeRecursive(Node* current, float val) {
        int i = 0;
        while (i < current->size && val > current->keys[i].val) { //correct cos in leaf node key 0 has pointer[0] to its val
            i++; //find index to go to
        }

        if (current->is_leaf) {
            // If key is found in the leaf, remove it
            if (i < current->size && current->keys[i].val == val) {
                for (i; i < current->size - 1; i++) {
                    current->keys[i] = current->keys[i + 1];
                }
                current->size--;
                // Check for underflow in the leaf node
                if (current->size < (nodeSize+1) / 2 -0) { // SIZING change from -1 to 0
                    handleLeafUnderflow(current);
                }
                return true; //key removed
            }
            return false;//no more keys to remove or no key
        }
        else { // update internal node key ####I THINK ERROR IS HERE
            if (i < current->size && current->keys[i].val == val) {//change from i to i-1// if key is found in the c1
                // If the key is found in an internal node
                Node* successorNode = current->children[i+1]; //change from i+1 to i?c2
                while (!successorNode->is_leaf) {
                    successorNode = successorNode->children[0];// change from 0 to 1??c3
                }
                float successorVal = successorNode->keys[0].val;
                if (removeRecursive(current->children[i+1], successorVal)) { // i feel like the error is here
                    current->keys[i].val = successorNode->keys[0].val; //trying random things here //line feels correct
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
        //edited one below original seems to work better but idk
        /*for (int i = 0; i <= parent->size && indexInParent == -1; i++) {
            if (parent->children[i] == leaf) {
                indexInParent = i;

                // Handling left sibling
                if (i-1 >= 0) {
                    leftSibling = parent->children[i-1];
                }
                else {
                    leftSibling = nullptr;
                }
                // Handling right sibling
                if (i+1 <= parent->size) {
                    rightSibling = parent->children[i+1];
                }
                else {
                    rightSibling = nullptr;
                }
            }
        }*/

        // Borrow from the left sibling
        if (leftSibling && leftSibling->size > (nodeSize+1) / 2 + 0) { //SIZING change from -1 to +1 to 0
            // Shift all keys in the leaf node to the right
            for (int i = leaf->size; i > 0; i--) {
                leaf->keys[i] = leaf->keys[i - 1];
            }

            //leaf->keys[0] = parent->keys[indexInParent];
            //parent->keys[indexInParent] = leftSibling->keys[leftSibling->size - 1];

            //Replaced top with bottom
            leaf->keys[0] = leftSibling->keys[leftSibling->size - 1]; // Borrow the largest key from left sibling
            parent->keys[indexInParent] = leaf->keys[0];// Update the parent's key that points to the leaf node

            leaf->size++;
            leftSibling->size--;
        }
            // Borrow from the right sibling
        else if (rightSibling && rightSibling->size > (nodeSize+1) / 2 + 1) { //SIZING change from -1 to +1 to 0
            //leaf->keys[leaf->size] = parent->keys[indexInParent+1];
            //parent->keys[indexInParent+1] = rightSibling->keys[0];
            //replace top with bottom
            leaf->keys[leaf->size] = rightSibling->keys[0];
            parent->keys[indexInParent+1] = rightSibling->keys[0];
            // Shift all keys in the right sibling to the left
            for (int i = 0; i < rightSibling->size - 1; i++) {
                rightSibling->keys[i] = rightSibling->keys[i + 1];
            }
            leaf->size++;
            rightSibling->size--;
        }
            // Merge with the left sibling
        else if (leftSibling) {
            // Copy all keys from the current leaf node to the left sibling
            for (int i = 0, j = leftSibling->size; i < leaf->size; i++, j++) {
                leftSibling->keys[j] = leaf->keys[i];
            }
            leftSibling->size += leaf->size;
            leftSibling->children[nodeSize] = leaf->children[nodeSize];

            // update parent
            for (int i = indexInParent; i < parent->size - 1; i++) {
                parent->keys[i] = parent->keys[i + 1];
                parent->children[i + 1] = parent->children[i + 2];
            }
            parent->size--;

            delete leaf;
        }
            // Merge with the right sibling
        else if (rightSibling) {
            // Copy all keys from the right sibling to the current leaf node
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

    void handleNonLeafUnderflow(Node* nonLeafNode, int index) { //input is the parent pointer and its corresponding child index
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
            // Shift all keys and children in the child node to the right
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

            // Shift all keys and children in the right sibling to the left
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
            // Copy all keys and children from the child node to the left sibling
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
            // Copy all keys and children from the right sibling to the child node
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

/*    void removeRange(float startVal, float endVal) { //may not be correct copied from chatgpt
        Node* current = root;

        // Traverse to the leftmost leaf node in the range
        while (!current->is_leaf) {
            int i = 0;
            while (i < current->size && startVal > current->keys[i].val) {
                i++;
            }
            current = current->children[i];
        }

        // Traverse the leaves and delete the keys in the range
        while (current && current->keys[0].val <= endVal) {
            // Delete the keys in the current leaf that fall in the range
            for (int i = 0; i < current->size;) {
                if (current->keys[i].val >= startVal && current->keys[i].val <= endVal) {
                    // Shift keys to the left to fill the gap
                    for (int j = i; j < current->size - 1; j++) {
                        current->keys[j] = current->keys[j + 1];
                    }
                    current->size--;
                } else {
                    i++;
                }
            }
            // Handle underflow if needed
            if (current->size < (nodeSize + 1) / 2 - 1) {
                handleLeafUnderflow(current);
            }
            // Move to the next leaf
            current = current->children[nodeSize];
        }
    }*/
};
