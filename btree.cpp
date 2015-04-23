#include "btree.h"

btree::btree() {
    // set the root to NULL

    root = NULL;
    numberOfNodes = 0;

}

bool btree::isEmpty()
{
    // This functions returns true if the tree is
    // empty and false if it is not empty. You just
    // need to look at the root.

    if (root == NULL) {
        return true;
    } else {
        return false;
    }

}

void btree::insert(int d)
{
    // this function must insert the value d in the tree

    // first of all, check if d already exists in the tree
    // you can do this by calling to the search(int) function
    // I didn't implement this using search, but using if statment below

    // if d is not in the tree already, create a new node with data equal d
    node * new_node = new node;
    new_node->data = d;

    // if the tree is empty, set the root to the new node

    // if the tree is not empty, look for the right place where to insert d
    // in order to do this, you may need to keep track of the potential
    // parent node to which the new node will be attached as a child

    node * current_node = root;  // the node we are now dealing with
    node * old_node = NULL;   // the parent of current_node

    // find right place to insert
    while (current_node != NULL) {
        old_node = current_node;
        if (new_node->data < current_node->data) {
            current_node = current_node->left;
        } else if (new_node->data > current_node->data) {
            current_node = current_node->right;
        } else {
            return;
        }
    }

    // insert the node
    if (old_node == NULL) {
        root = new_node;
    } else {
        if (new_node->data < old_node->data) {
            old_node->left = new_node;
        } else {
            old_node->right = new_node;
        }
    }

    numberOfNodes++;
    return;
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

    if (root == NULL) {
        return;
    } 

    node * current_node = root;  // the node we are now dealing with
    node * old_node = NULL;  // the parent of current_node

    // find the node to delete
    while (current_node != NULL && d != current_node->data) {
        old_node = current_node;
        if (d < current_node->data) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }

    // return if we didn't find the node need to be removed
    if (current_node == NULL) {
        return;
    }

    // change the number nodes
    numberOfNodes--;

    // case 1: removing a leaf code
    if (current_node->left == NULL && current_node->right == NULL) {
        if (current_node == root) {
            root = NULL;
        } else {
            if (old_node->left == current_node) {
                old_node->left = NULL;
            } else {
                old_node->right = NULL;
            }
        }

        delete current_node;
        return;
    }

    // case 2(a): removing a node with a single left child
    if (current_node->left != NULL && current_node->right == NULL) {
        if (current_node == root) {
            root = current_node->left;
        } else {
            if (old_node->left == current_node) {
                old_node->left = current_node->left;
            } else {
                old_node->right = current_node->left;
            }
        }

        delete current_node;
        return;
    }

    // case 2(b): removing a node with a single right child
    if (current_node->left == NULL && current_node->right != NULL) {
        if (current_node == root) {
            root = current_node->right;
        } else {
            if (old_node->left == current_node) {
                old_node->left = current_node->right;
            } else {
                old_node->right = current_node->right;
            }
        }

        delete current_node;
        return;
    }

    // case 3: removing a node with two children
    if (current_node->left == NULL && current_node->right != NULL) {
        node * next_node = current_node->right; // use to check the status of the next node

        if (next_node->left == NULL && next_node->right == NULL) {
            next_node->left = current_node->left;
            delete next_node;
        } else {
            if (next_node->left != NULL) {
                node * left_current = next_node->left;
                node * left_old = next_node;

                while (left_current->left != NULL) {
                    left_old = left_current;
                    left_current = left_current->left;
                }

                current_node->data = left_current->data;
                delete left_current;
                left_old->left = NULL;
            } else {
                current_node->data = next_node->data;
                current_node->right = next_node->right;
                delete next_node;
            }
        }

        return;
    }
    
}

void btree::print_inorder()
{
    // this function must call the private inorder(node*)
    // function passing the root as the parameter

    inorder(root);

}

void btree::inorder(node* p)
{
    // This function receives a node as parameter
    // then traverses the tree following the in-order
    // sequence. Every time it visits a node it will
    // print the data in the node to cout leaving a blank
    // space to separate from the next/previous value.
    // The function must use recursion.

    if (p != NULL) {
        inorder(p->left);
        cout << p->data << " ";
        inorder(p->right);
    }

}

void btree::print_preorder()
{
    // This function must call the private pre-order(node*)
    // function passing the root as the parameter

    preorder(root);

}

void btree::preorder(node* p)
{
    // This function receives a node as parameter
    // then traverses the tree following the pre-order
    // sequence. Every time it visits a node it will
    // print the data in the node to cout leaving a blank
    // space to separate from the next/previous value.
    // The function must use recursion.

    if (p != NULL) {
        cout << p->data << " ";
        inorder(p->left);
        inorder(p->right);
    }

}

void btree::print_postorder()
{
    // This function must call the private post-order(node*)
    // function passing the root as the parameter

    postorder(root);

}

void btree::postorder(node* p)
{
    // This function receives a node as parameter
    // then traverses the tree following the post-order
    // sequence. Every time it visits a node it will
    // print the data in the node to cout leaving a blank
    // space to separate from the next/previous value.
    // The function must use recursion.

    if (p != NULL) {
        inorder(p->left);
        inorder(p->right);
        cout << p->data << " ";
    }

}

void btree::print_reveorder() {

    stack<int> treeStack;
    
    reveorder(root, treeStack);

    while(!treeStack.empty()) {
        cout << treeStack.top() << " ";
        treeStack.pop();
    }

}

void btree::reveorder(node* p, stack<int> &myStack) {

    if (p != NULL) {
        reveorder(p->left, myStack);
        myStack.push(p->data);
        reveorder(p->right, myStack);
    }

}

bool btree::search(int val)
{
    // This function must call the private function
    // search_element(node*,int) passing the root and
    // the integer value val as parameters. The function
    // must use recursion.

    return search_element(root, val);

}

bool btree::search_element(node* p, int val) {
    // this function receives a node and an integer as
    // parameters and searches for the value val in the
    // data of the node. The function must be such that
    // if the value is never found, it returns false.
    // If the value is found, then it returns true.
    // The function must use recursion.

    if (p != NULL) {
        if (val == p->data) {
            return true;
        } else if (val < p->data) {
            return search_element(p->left, val);
        } else {
            return search_element(p->right, val);
        }
    } else {
        return false;
    }

}

int btree::height() {

    return height(root);

}

int btree::height(node* p) {

    if (p == NULL) {
        return 0;
    }

    int leftHeight = height(p->left);
    int rightHeight = height(p->right);

    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;

}