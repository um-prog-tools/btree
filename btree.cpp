#include "btree.h"

btree::btree() {
    // set the root to NULL
}

bool btree::isEmpty()
{
    // This functions returns true if the tree is
    // empty and false if it is not empty. You just
    // need to look at the root.
}

void btree::insert(int d)
{
    // this function must insert the value d in the tree

    // first of all, check if d already exists in the tree
    // you can do this by calling to the search(int) function

    // if d is not in the tree already, create a new node with data equal d

    // if the tree is empty, set the root to the new node

    // if the tree is not empty, look for the right place where to insert d
    // in order to do this, you may need to keep track of the potential
    // parent node to which the new node will be attached as a child
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
    // the integer value val as parameters. The function
    // must use recursion.
}

bool btree::search_element(node* p, int val) {
    // this function receives a node and an integer as
    // parameters and searches for the value val in the
    // data of the node. The function must be such that
    // if the value is never found, it returns false.
    // If the value is found, then it returns true.
    // The function must use recursion.
}