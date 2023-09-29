#include <iostream>
#include <queue>

const int nodeSize = 22; // Define the node size (parameter) here

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
        }
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
        if (current->is_leaf) {
            return nullptr;
        }
        if (current == child) {
            return child;
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
            // Todo: traverse the whole b+ tree
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

    // Getter functions to retrieve the count of index nodes and data blocks accessed
    int getIndexNodeAccessCount() const {
        return indexNodeAccessCount;
    }

};
