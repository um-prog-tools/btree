/**
* btree
* Amirhossein Naemi
* Avril, 2015
* GIT: https://github.com/amirhossein-naemi/btree/
*
*/

#include <iostream>
#include <cstdlib>
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

    bool search(int);

    void printLevels();

private:

    void inorder(node*);
    void preorder(node*);
    void postorder(node*);

    bool search_element(node*, int);

};

btree::btree() {
    // set the root to NULL
    root = NULL;
    nnodes = 0;
}

bool btree::isEmpty()
{
    // This functions returns true if the tree is
    // empty and false if it is not empty. You just
    // need to look at the root.

    return true;
}

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

void btree::remove(int d)
{
    // this function must remove the node that has the value d

    // first of all, check if the tree is empty
    // if it is not, then locate the element with the value
    // once you know the location, that is, you have the pointer to the node
    // with the value you want to eliminate, you will have three cases:
    //    1. you're removing a leaf node
    //    2. you're removing a node with a single child
    //    3. you're removing a node with 2 children
    // make sure you can handle all three cases.
}

void btree::print_inorder()
{
    // this function must call the private inorder(node*)
    // function passing the root as the parameter
}

void btree::inorder(node* p)
{
    // This function receives a node as parameter
    // then traverses the tree following the in-order
    // sequence. Every time it visits a node it will
    // print the data in the node to cout leaving a blank
    // space to separate from the next/previous value.
    // The function must use recursion.
}

void btree::print_preorder()
{
    // This function must call the private pre-order(node*)
    // function passing the root as the parameter
}

void btree::preorder(node* p)
{
    // This function receives a node as parameter
    // then traverses the tree following the pre-order
    // sequence. Every time it visits a node it will
    // print the data in the node to cout leaving a blank
    // space to separate from the next/previous value.
    // The function must use recursion.
}

void btree::print_postorder()
{
    // This function must call the private post-order(node*)
    // function passing the root as the parameter
}

void btree::postorder(node* p)
{
    // This function receives a node as parameter
    // then traverses the tree following the post-order
    // sequence. Every time it visits a node it will
    // print the data in the node to cout leaving a blank
    // space to separate from the next/previous value.
    // The function must use recursion.
}

bool btree::search(int val)
{
    // This function must call the private function
    // search_element(node*,int) passing the root and
    // the integer value val as parameters and returning
    // the same answer it gets from search_element()
    // back to the main program.

    return search_element(root, val);
}

/*
// this function receives a node and an integer as
// parameters and searches for the value val in the
// data of the node. The function must be such that
// if the value is never found, it returns false.
// If the value is found, then it returns true.
// The function must use recursion.
*/
bool btree::search_element(node* p, int val) {

    if (p == NULL) {
        return false;
    }
    else {
        if (val == p->data) return(true);
        else {
            if (val < p->data)
                return(search_element(p->left, val));
            else
                return(search_element(p->right, val));
        }
    }
}

/* Print by levels */
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

int main(int argc, char* argv[])
{
    // This is the main program.

    // If the program is called without arguments, then
    // the user is taken straight to the list of options
    // if the program is called with parameters, the program
    // assumes these parameters are a list of integers and
    // inserts those into the tree.

    // Reading the program may help you understand how the
    // class functions are called.

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
            my_tree.printLevels();
            break;
            // ***************************************************
            // If you decide to implement the extra credit options
            // this is one place where you will need to add code
            // to provide the user with those extra functions
            // ***************************************************
        }
    }
}
