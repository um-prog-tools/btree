#ifndef _BTREE_H_
#define _BTREE_H_

#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class btree
{
private:

    struct node
    {
        node* left;
        node* right;
        int data;
        int occurrences;

        node():left(NULL),right(NULL),occurrences(1){}
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
    void print_reveorder();
    void print_level();

    int search(int);

    int height();

private:

    void inorder(node*);
    void preorder(node*);
    void postorder(node*);
    void reveorder(node*, stack<node*> &);
    void print_node(node*);

    int height(node*);

    int search_element(node*, int);

    int numberOfNodes;

};

#endif