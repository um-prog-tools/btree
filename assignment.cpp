
#include <iostream>
#include <cstdlib>

using namespace std;

class btree
{
private:

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

private:

    void inorder(node*);
    void preorder(node*);
    void postorder(node*);

    bool search_element(node*, int);

};

btree::btree() {
    root = NULL;
}

bool btree::isEmpty()
{
    if (root == NULL) return true;
    return false;
}

void btree::insert(int d)
{

    node* c;
    c = root;
    node* p;
    p = NULL;
    if (search(d) == true) {
        cout << "\n" << " The number " << d << " is already part of the existing tree.";
        return;
    }
    if (isEmpty() != false) {
        root = new node;
        root->data = d;
        root->left = NULL;
        root->right = NULL;
        cout << "\n" << " The number " << root->data << " was inserted into the tree.";
    } else {
        while (c != NULL) {
            p = c;
            if (c->data > d) {
                c = c->left;
            } else {
                c = c->right;
            }
        }
        if (p->data > d) {
            p->left = new node;
            p->left->data = d;
            p->left->left = NULL;
            p->left->right = NULL;
        } else {
            p->right = new node;
            p->right->data = d;
            p->right->left = NULL;
            p->right->right = NULL;
        }

        cout << "\n" << "The number " << d << " was inserted into the tree.";
    }
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
    inorder(root);
}


void btree::inorder(node* p)
{
    if (p != NULL)
    {
        inorder(p->left);
        cout << p->data << " ";
        inorder(p->right);
    }
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
    if (search_element(root, val) == true) {
        return true;
    } else {
        return false;
    }
}


bool btree::search_element(node* p, int val)
{
    if (p->data == val)
    {
        return true;
    } else if (val < p->data && p->left != NULL)
    {
        p = p->left;
        if (search_element(p, val) == true)
        {
            return true;
        }
    } else if (val > p->data && p->right != NULL)
    {
        p = p->right;
        if (search_element(p, val) == true)
        {
            return true;
        }
    } else
    {
        return false;
    }

    return false;
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
            break;
            // ***************************************************
            // If you decide to implement the extra credit options
            // this is one place where you will need to add code
            // to provide the user with those extra functions
            // ***************************************************
        }
    }
}
