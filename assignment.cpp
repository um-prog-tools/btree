/**
* btree
* Amirhossein Naemi
* Avril, 2015
* GIT: https://github.com/amirhossein-naemi/btree/
*
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <list>

using namespace std;

class btree
{
private:

    int nnodes;

    struct node
    {
        node* left;
        node* right;
        int data;
    };
    node* root;

public:

    btree();
    bool isEmpty();

    void insert(int);
    void remove(int);

    void print_inorder();
    void print_preorder();
    void print_postorder();
    void printReverse();

    bool search(int);

    void printLevels();
    void printHeight();
    
    int getNumOfIntNodes() {
        return NodeIntCount(root);
    };
    int getNumOfLeaf(){
        return LeafCount(root);
    };
    int getNumOfNodes(){
        return LeafCount(root) + NodeIntCount(root);
    };

private:

    void inorder(node*);
    void preorder(node*);
    void postorder(node*);
    void reverse(node*);
    int NodeIntCount(node*);
    int LeafCount(node*);

    int height(node*);
    bool search_element(node*, int);

};

btree::btree() {
    // set the root to NULL
    root = NULL;
    nnodes = 0;
}

/** This functions returns true if the tree is
* empty and false if it is not empty. You just
* need to look at the root.
* @param none
* @return boolean value
*/
bool btree::isEmpty()
{
    if (root == NULL)
        return true;
    else
        return false;
}

/** this function must insert the value d in the tree
* @param integer number as an input
* @return nothing
*/
void btree::insert(int d)
{
    // this function must insert the value d in the tree

    nnodes++;

    // first of all, check if d already exists in the tree
    // you can do this by calling to the search(int) function

    if (search(d))
        return;

    // if d is not in the tree already, create a new node with data equal d

    node* n = new node;
    n->data = d;
    n->left = n->right = NULL;

    // if the tree is empty, set the root to the new node

    if (root == NULL)
    {
        root = n;
        return;
    }

    // if the tree is not empty, look for the right place where to insert d
    // in order to do this, you may need to keep track of the potential
    // parent node to which the new node will be attached as a child

    node *parent = NULL, *i = root;

    while (i != NULL){
        parent = i;

        if (d < i->data)
            i = i->left;
        else
            i = i->right;
    }

    if (d < parent->data)
        parent->left = n;
    else
        parent->right = n;
}

/** this function must insert the value d in the tree
* @param integer number as an input
* @return nothing
*/
void btree::remove(int d)
{
    // this function must remove the node that has the value d

    // first of all, check if the tree is empty
    if (root == NULL) 
        return;

    node * nod = root; 
    node * old_node = NULL;

    // if it is not, then locate the element with the value
    while (nod != NULL && d != nod->data) {
        old_node = nod;
        if (d < nod->data) 
            nod = nod->left;
        else 
            nod = nod->right;
    }

    if (nod == NULL)
        return;

    // once you know the location, that is, you have the pointer to the node
    // with the value you want to eliminate, you will have three cases:

    //    1. you're removing a leaf node
    if (nod->left == NULL && nod->right == NULL) {
        if (nod == root) {
            root = NULL;
        }
        else {
            if (old_node->left == nod) {
                old_node->left = NULL;
            }
            else {
                old_node->right = NULL;
            }
        }

        delete nod;
        return;
    }

    //    2. you're removing a node with a single child
    if (nod->left != NULL && nod->right == NULL) {
        if (nod == root) {
            root = nod->left;
        }
        else {
            if (old_node->left == nod) 
                old_node->left = nod->left;
            else 
                old_node->right = nod->left;
        }

        delete nod;
        return;
    }

    if (nod->left == NULL && nod->right != NULL) {
        if (nod == root) {
            root = nod->right;
        }
        else {
            if (old_node->left == nod) 
                old_node->left = nod->right;
            else 
                old_node->right = nod->right;
        }

        delete nod;
        return;
    }

    //    3. you're removing a node with 2 children
    if (nod->left != NULL && nod->right != NULL) {
        node * nextNod = nod->right;

        if (nextNod->left == NULL && nextNod->right == NULL) {
            nextNod->left = nod->left;
            delete nextNod;
        }
        else {
            if (nextNod->left != NULL) {
                node * lnod = nextNod->left;
                node * left_old = nextNod;

                while (lnod->left != NULL) {
                    left_old = lnod;
                    lnod = lnod->left;
                }

                nod->data = lnod->data;
                delete lnod;
                left_old->left = NULL;
            }
            else {
                nod->data = nextNod->data;
                nod->right = nextNod->right;
                delete nextNod;
            }
        }

        return;
    }

}

/**
* @short Returns the number of interior nodes
* @param n start node for traversal
* @return Number of interior nodes
*
* Returns the number of interior nodes of the tree
*/
int btree::NodeIntCount(node* n){

    // Leave if the node is Null
    if (n == NULL)
        return 0;

    if (n->right == NULL && n->left == NULL)
        return 0;
    else
        return NodeIntCount(n->right) + NodeIntCount(n->left) + 1;

}

/**
* @short Returns the number of leaf nodes
* @param n start node for traversal
* @return Number of leaf nodes
*
* Returns the number of leaf nodes of the tree
*/
int btree::LeafCount(node* n){

    if (n == NULL)
        return 0;
    
    if (n->left == NULL && n->right == NULL)
        return 1;
    else
        return LeafCount(n->right) + LeafCount(n->left);
}

/** this function must call the private inorder(node*)
* function passing the root as the parameter
* @param nothing
* @return nothing
*/
void btree::print_inorder()
{
    inorder(root);
}


/**
* This function receives a node as parameter
* then traverses the tree following the in-order
* sequence. Every time it visits a node it will
* print the data in the node to cout leaving a blank
* space to separate from the next/previous value.
* The function must use recursion.
*
* @param n start node for traversal
* @return nothing
*/
void btree::inorder(node* n)
{
    if (n == NULL)
        return;

    inorder(n->left);
    cout << " " << n->data;
    inorder(n->right);
}

/**
* @short printing the preorder sequence of tree
* @param nothing
* @return nothing
* This function must call the private pre-order(node*)
* function passing the root as the parameter
*/
void btree::print_preorder()
{
    preorder(root);
}

/**
* @short Preorder Traversal
* @param n start node for traversal
* @return nothing
*
* This function receives a node as parameter
* then traverses the tree following the pre-order
* sequence. Every time it visits a node it will
* print the data in the node to cout leaving a blank
* space to separate from the next/previous value.
* The function must use recursion.
*/
void btree::preorder(node* n)
{
    if (n == NULL)
        return;

    cout << " " << n->data;
    preorder(n->left);
    preorder(n->right);

}

/**
* @short printing the postorder sequence
* @param nothing
* @return nothing
*
* This function must call the private post-order(node*)
* function passing the root as the parameter
*/
void btree::print_postorder()
{
    postorder(root);
}

/**
* @short Postorder Traversal
* @param n start node for traversal
* @return nothing
*
* This function receives a node as parameter
* then traverses the tree following the post-order
* sequence. Every time it visits a node it will
* print the data in the node to cout leaving a blank
* space to separate from the next/previous value.
* The function must use recursion.
*/
void btree::postorder(node* n)
{
    if (n == NULL)
        return;

    postorder(n->left);
    postorder(n->right);
    cout << " " << n->data;
}

/**
* @short Calculate the height of the tree
* @param n start node for traversal
* @return nothing
*
* Calculate the height of the tree
*/
void btree::printHeight(){

    cout << height(root) << endl;

}

int btree::height(node* n){
    
    if (n == NULL)
        return -1;

    if (height(n->left) > height(n->right))
        return height(n->left) + 1;
    else
        return height(n->right) + 1;
}

void btree::printReverse()
{
    reverse(root);
}

/**
* @short reverseorder traversal
* @param n a node from which the traversal start
* @return none
*
* This function receives a node as parameter then
* traverses the tree following the reverse-order sequence.
*/
void btree::reverse(node* n)
{
    if (n == NULL)
        return;

    reverse(n->right);
    cout << n->data << ' ';
    reverse(n->left);
}

/**
* @short search for an integer value in the tree
* @param val the integer to be searched in the tree
* @return bool
*
* This function must call the private function
* search_element(node*,int) passing the root and
* the integer value val as parameters and returning
* the same answer it gets from search_element()
* back to the main program.
*/
bool btree::search(int val)
{
    return search_element(root, val);
}

/*
* @short searches for a value in the tree
* @param n the start node for traversal
* @param val the integer to be searched in the tree
* @return bool
*
* this function receives a node and an integer as
* parameters and searches for the value val in the
* data of the node. The function must be such that
* if the value is never found, it returns false.
* If the value is found, then it returns true.
* The function must use recursion.
*/
bool btree::search_element(node* n, int val) {

    if (n == NULL) {
        return false;
    }
    else {
        if (val == n->data) return(true);
        else {
            if (val < n->data)
                return(search_element(n->left, val));
            else
                return(search_element(n->right, val));
        }
    }
}

/* 
* @short Print by levels
* @param nothing
* @return nothing
*
* Print the tree in by levels of the tree
*/
void btree::printLevels() {

    if (root == NULL)
        return;

    //printSides(root);
    node *i;
    int lev = 0;

    std::list<node*> lstNode;
    lstNode.push_back(root);
    lstNode.push_back(NULL);

    cout << endl << "Level 0 nodes: ";

    while (!lstNode.empty()) {
        i = lstNode.front();
        lstNode.pop_front();

        if (i == NULL)
        {
            if (!lstNode.empty()) {
                lstNode.push_back(NULL);
                cout << endl;
                cout << "Level " << ++lev << " nodes: ";
            }
        }
        else {
            if (i->left != NULL)
                lstNode.push_back(i->left);
            if (i->right != NULL)
                lstNode.push_back(i->right);

            cout << i->data << " ";
        }
    }

}


/**
*@short main Program
*@param arguments, which are the integer numbers to be inserted in the tree
*
* If the program is called without arguments, then
* the user is taken straight to the list of options
* if the program is called with parameters, the program
* assumes these parameters are a list of integers and
* inserts those into the tree.
*
* Reading the program may help you understand how the
* class functions are called.
*/
int main(int argc, char* argv[])
{
    // ********************** W A R N I N G **********************
    // In general, you do not need to make any change in the main
    // program.  The only case when you will need to make changes
    // here is if you decide to implement the functions for extra
    // credit. In which case, the place to make changes is indica-
    // below.
    // ***********************************************************

    // instantiate the tree
    btree my_tree;

    // some auxiliary variables
    int ch, tmp, tmp1;
    bool ans;

    // if arguments are passed, then the program assumes the
    // arguments are a list of integers and it inserts one by
    // one into the tree.
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            tmp = atoi(argv[i]);
            my_tree.insert(tmp);
        }
    }

    while (1)
    {
        cout << endl << endl;
        cout << " Binary Tree Operations " << endl;
        cout << " 1. Insertion/Creation " << endl;
        cout << " 2. In-Order Traversal " << endl;
        cout << " 3. Pre-Order Traversal " << endl;
        cout << " 4. Post-Order Traversal " << endl;
        cout << " 5. Removal " << endl;
        cout << " 6. Search " << endl;
        cout << " 7. Print Tree by Levels" << endl;
        cout << " 8. Print the Height of the Tree" << endl;
        cout << " 9. Print Number of Nodes in the Tree" << endl;
        cout << " 10. Print Reverse Order Traversal" << endl;
        // ***************************************************
        // If you decide to implement the extra credit options
        // this is one place where you will need to add code
        // to provide the user with those extra functions
        // ***************************************************
        cout << " 0. Exit " << endl;
        cout << " Enter your choice : ";
        cin >> ch;
        switch (ch)
        {
        case 0:
            return 0;
        case 1:
            cout << " Enter Number to be inserted: ";
            cin >> tmp;
            my_tree.insert(tmp);
            break;
        case 2:
            cout << endl;
            cout << " In-Order Traversal: " << endl << endl;
            my_tree.print_inorder();
            break;
        case 3:
            cout << endl;
            cout << " Pre-Order Traversal: " << endl << endl;
            my_tree.print_preorder();
            break;
        case 4:
            cout << endl;
            cout << " Post-Order Traversal: " << endl << endl;
            my_tree.print_postorder();
            break;
        case 5:
            cout << " Enter data to be deleted: ";
            cin >> tmp1;
            my_tree.remove(tmp1);
            break;
        case 6:
            cout << " Enter data to be searched: ";
            cin >> tmp1;
            ans = my_tree.search(tmp1);
            if (ans) cout << tmp1 << " was found!!!" << endl;
            else cout << tmp1 << " was not found" << endl;
        case 7:
            cout << " Printing Tree Levels Traverse: " << endl;
            my_tree.printLevels();
            break;
        case 8:
            cout << endl << "Height of the tree is : ";
            my_tree.printHeight();
            break;
        case 9:
            cout << endl << endl
                << "Total Number of Nodes in the Tree is " 
                << my_tree.getNumOfNodes()
                << " which contains of " 
            << my_tree.getNumOfIntNodes()
            << " interior nodes, and "
            << my_tree.getNumOfLeaf() << "leaf.";
            break;
        case 10:
            cout << "Reverse Order Traversal : " << endl;
            my_tree.printReverse();

            break;
            // ***************************************************
            // If you decide to implement the extra credit options
            // this is one place where you will need to add code
            // to provide the user with those extra functions
            // ***************************************************
        }
    }
}
