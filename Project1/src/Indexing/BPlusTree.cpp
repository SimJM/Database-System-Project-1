#include<iostream>
#include<string>
#include<climits>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;

struct key_struct{

    float val;    // value of the key
    vector <void*> new_pointer;};   //pointer vector

class Tree;
int nodeSize; //Need to define this

class Node{
    int size;  //to keep track
    Node** ptr;
    bool is_leaf;
    friend class Tree;

public:
    Node(){
        key= new key_struct[nodeSize];
        ptr= new Node*[nodeSize+1];
        is_leaf=true;

        //To allocate memory whenever it is called. Again NodeSize needs to be defined
    }

    key_struct *key;
};

class Tree
{
public:
    Node *root;
    void insert_main(key_struct k, Node* cur, Node* child)
    {
        if (cur->size<nodeSize){  //see if need new node or not. Checks the current size of the cur.

            int i=0;
            while(k.val>cur->key[i].val && i<cur->size) //Where to add the key in the node
                i++;
            int j= cur->size;
            for (j; j>i; j--){

                cur->key[j]=cur->key[j-1];  // Shifting key values larger than k.val to right
            }
            j = cur->size+1;
            for(j ; j > i+1; j--)
            {
                cur->ptr[j] = cur->ptr[j-1]; //Shift pointers.
            }

            cur->key[i]= k;                 //after finding the right position within the node (i) assign the value.
            cur->size++;                    //Increment the size
            cur->ptr[i+1] = child;          // Assign the child pointer it'd point at, again according to the position determined
        }
        else{

            //Need New Node
            //So making another nodes with sets of keys.
            Node* n= new Node;
            key_struct img_key[nodeSize+1];
            Node* img_ptr[nodeSize+2];   // this is more like how a node would look if it could hole more than 1 allowed.
            //Purpose is just to get the order/position right and then split them.
            Node* new_ptr[nodeSize+2];
            for (int i=0; i<nodeSize; i++)         //copying all the values
                img_key[i]=cur->key[i];
            for (int i=0; i<nodeSize+1; i++)       //copying all the pointers
                img_ptr[i]=cur->ptr[i];

            int i=0, j=nodeSize+1;              //making space for key by comparing. Basically the same step we did in the if statement

            while(k.val>img_key[i].val && i<nodeSize+1) //using nodeSize+1 because it is an imaginary node, and is 1 more than the usual size.
                i++;
            for (j=nodeSize+2; j>i; j--)                // similarly using +2 here.
                img_key[j]=img_key[j-1];
            img_key[i]=k;

            //making space for pointers

            for(j=nodeSize+2;j>i+1;j--)
                img_ptr[j]=img_ptr[j-1];
            img_ptr[i+1]= child;

            n->is_leaf= false;

            //Now we split this big node into two nodes.

            cur->size = (nodeSize+1)/2;
            n->size= nodeSize-(nodeSize+1)/2;

            //again copy values and pointers to the new node after splitting
            i = 0;
            j = cur->size+1;
            for( i,j; i< n->size; i++, j++)
            {
                n->key[i] = img_key[j];    // Assigning keys to the new node (n) from the imaginary node we created
            }
            i=0;
            j=cur->size;
            for(i, j; i < n->size+1; i++, j++)
            {
                n->ptr[i] = img_ptr[j];    // Assigning pointers to the new node (n) from the imaginary node we created
            }

            //Recursion breaking case is when the cur is pointing to the root.
            if (cur==root)
            {
                Node* nr = new Node;
                nr->key[0] = cur->key[cur->size];
                nr->ptr[0] = cur;
                nr->ptr[1] = n;
                nr->is_leaf = false;
                nr->size = 1;
                root = nr;
            }

            else{


                //recursive case
                //finding until parent, that is the root is found
                insert_main(cur->key[cur->size],findParent(root,cur) ,n); // the child is the new node (n), the new cur is the parent.
            }
        }
    }



    Node* findParent(Node* cur, Node* child)
    {

        // use this function to find the parents

        Node* parent;
        if(cur->is_leaf)  // if it is leaf it cannot be a parent. Extra Note: cur here is the root passed out in the insert_main function
        {
            return NULL;
        }
        int i=0;
        for( i; i < cur->size+1; i++)
        {
            if(cur->ptr[i] == child)  //parent found
            {
                parent = cur;
                return parent;
            }
            else                       // recursive
            {
                parent = findParent(cur->ptr[i],child);
                if(parent!=NULL)
                    return parent;
            }
        }
        return parent;
    }
    Node *traversal(float k) {
        //search logic
        if (root == nullptr){
            //empty
        }
        else{
            Node *cursor = root;
            //in the following while loop, cursor will travel to the leaf node possibly consisting the key
            while (cursor->is_leaf == false) {
                for (int i = 0; i < cursor->size; i++) {
                    if (k < cursor->key[i].val) { // if x<key move to the left child pointer then break
                        cursor = cursor->ptr[i];
                        break;
                    }
                    if (i == cursor->size - 1) { // checking if we are at the last key in current node if we are move to rightmost node line
                        cursor = cursor->ptr[i + 1];
                        break;
                    }
                }
            }
            //in the following for loop, we search for the key if it exists
            //after this cursor is pointing to leaf node of where key is
            //in the leaf node, we search for the key
            for (int i = 0; i < cursor->size; i++) {
                if (cursor->key[i].val == k) { //if key is found
                    //cout<<"Found\n";
                }
                return cursor;
            }
        }
        //cout<<"Not found\n";
        return nullptr;
    }



    void insert(key_struct k)
    {
        //if tree is empty we start at this point.
        if(root==NULL)
        {
            root = new Node;
            root->key[0] = k;
            root->is_leaf = true;
            root->size = 1;} //set size to 1, as its the first one created.

            // if root exists, we move on to else
        else
        {
            Node* cur = root;
            Node* parent;

            Node* traversed_node;
            traversed_node = traversal(k.val);                     //design a traversal function giving me the pointer to the node where we need to insert
            if ( traversed_node != nullptr){  // if the result is not a NULL pointer
                for(int i = 0; i < traversed_node->size; i++)
                {
                    if(traversed_node->key[i].val == k.val)
                    {
                        traversed_node->key[i].new_pointer.push_back(k.new_pointer[0]);  // if the node searched has the same key value we are looking to insert
                        break;
                    }
                }
                return;
            }

            while(cur->is_leaf == false)           // while we have not reached the leaf node
            {
                parent = cur;                       //copying the current cur value
                for(int i = 0; i < cur->size; i++)
                {
                    if(k.val < cur->key[i].val)    // if the insert value is less than we use the cur pointer just before it for the next for loop.
                    {
                        cur = cur->ptr[i];
                        break;
                    }
                    if(i == cur->size - 1)          // if we reach the end of the node, we just use the last pointer to move to the next for loop
                    {
                        cur = cur->ptr[i+1];
                        break;
                    }
                }
            }
            // after the while loop terminates we have reached the leaf node, where we need to insert.


            if(cur->size < nodeSize)  // Check whether the leaf node found is within max size.
            {
                int i = 0;
                while(k.val > cur->key[i].val && i < cur->size) i++;              //same step to make space by shifting after finding the correct position
                int j = cur->size;
                for(j;j > i; j--)
                {
                    cur->key[j] = cur->key[j-1];
                }
                cur->key[i] = k;       //Assign
                cur->size++;           //increment
                cur->ptr[cur->size] = cur->ptr[cur->size-1]; //shifting
                cur->ptr[cur->size-1] = NULL;
            }
            else
            {

                // Node full, create another leaf node

                Node* new_leaf = new Node;

                // Basically the same process of splitting

                key_struct img_node[nodeSize+1];  //imaginary node
                int i = 0;
                for(i; i < nodeSize; i++)
                {
                    img_node[i] = cur->key[i];
                }
                i=0; int j=nodeSize+1;
                while(k.val > img_node[i].val && i < nodeSize) i++;
                for(j;j > i; j--)
                {
                    img_node[j] = img_node[j-1];
                }
                img_node[i] = k;
                new_leaf->is_leaf = true;  //This is a leaf node

                //split it into tw

                cur->size = (nodeSize+1)/2;
                new_leaf->size = nodeSize+1-(nodeSize+1)/2;


                cur->ptr[cur->size] = new_leaf;  // assigning cur to the new leaf

                new_leaf->ptr[new_leaf->size] = cur->ptr[nodeSize]; //assigning pointer of the new leaf node to the next leaf node.

                cur->ptr[nodeSize] = NULL;

                //Assigning keys to the new node by imaginary big node we created


                for(i = 0; i < cur->size; i++)
                {
                    cur->key[i] = img_node[i];
                }
                i = 0, j = cur->size;
                for(i,j; i < new_leaf->size; i++, j++)
                {
                    new_leaf->key[i] = img_node[j];
                }

                ///Once done we just modify the parents by recursion

                //special case to break the recursion, create a new root.
                if(cur == root)
                {
                    Node* nr = new Node;
                    nr->key[0] = new_leaf->key[0];
                    nr->ptr[0] = cur;
                    nr->ptr[1] = new_leaf;
                    nr->is_leaf = false;
                    nr->size = 1;
                    root = nr;
                }
                else
                {
                    insert_main(new_leaf->key[0],parent,new_leaf);      // if it is not the root, we basically the other insertion method to insert the key.
                }
            }
        }
    }};