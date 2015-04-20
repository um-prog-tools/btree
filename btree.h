#ifndef _BTREE_H_
#define _BTREE_H_

#include <iostream>

using namespace std;

class btree
{
private:

    struct node
    {
        node* left;
        node* right;
        int data;

        node():left(NULL),right(NULL){}
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

#endif