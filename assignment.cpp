// Homework #9
// By Shepherd Tate
// Created April 25, 2015

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <math.h>
#include <stdio.h>

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
    void print_reverseorder();

    bool search(int);

private:

    void inorder(node*);
    void preorder(node*);
    void postorder(node*);
    void reverseorder(node*);

    bool search_element(node*, int val);

};

btree::btree() {
    root = NULL;
}

bool btree::isEmpty()
{
    if (root == NULL) {
        return true;
    } else {
        return false;
    }
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
            if (c->data > d) {
                p = c;
                c = c->left;
            } else {
                p = c;
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
    node *p = NULL;
    node *c = root;
    if (isEmpty() == true)
    {
        cout << "Tree is empty.";
        return;
    }
    if (search(d) == true)
    {
        while (c != NULL && d != c->data)
        {
            if (c->data > d)
            {
                p = c;
                c = c->left;
            } else
            {
                p = c;
                c = c->right;
            }
        }

        if (c->right == NULL && c->left == NULL)
        {
            if (p == NULL)
            {
                root = NULL;
                return;
            } else if (c == p->left)
            {
                p->left = NULL;
                delete c;
                return;
            } else if (c == p->right)
            {
                p->right = NULL;
                delete c;
                return;
            }
        } else if (c->left != NULL && c->right == NULL)
        {
            if (c == root)
            {
                root = c->left;
                return;
            } else if (c == p->left)
            {
                p->left = c->left;
                delete c;
                return;
            } else if (c == p->right)
            {
                p->right = c->left;
                delete c;
                return;
            }
        } else if (c->left == NULL && c->right != NULL)
        {
            if (c == root)
            {
                root = c->right;
                return;
            } else if (c == p->left)
            {
                p->left = c->right;
                delete c;
                return;
            } else if (c == p->right)
            {
                p->right = c->right;
                delete c;
                return;
            }
        } else
        {
            node* gc = c->left;
            if (gc->left == NULL && gc->right == NULL) {
                c->data = gc->data;
                c->left = NULL;
                delete gc;
            } else if (gc->left != NULL && gc->right == NULL) {
                c->data = gc->data;
                c->left = gc->left;
                delete gc;
            } else {
                node* info = gc->right;
                node* info2 = gc;
                while (info->right != NULL) {
                    info2 = info;
                    info = info->right;
                }
                c->data = info->data;
                info2->right = info->left;
                delete info;
            }
        }
    } else {
        cout << "The number " << d << " does not exist in the tree.";
    }
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
    preorder(root);
}

void btree::preorder(node* p)
{
    if (p != NULL)
    {
        cout << p->data << " ";
        preorder(p->left);
        preorder(p->right);
    }
}


void btree::print_postorder()
{
    postorder(root);
}


void btree::postorder(node* p)
{
    if (p != NULL)
    {
        postorder(p->left);
        postorder(p->right);
        cout << p->data << " ";
    }
}

void btree::print_reverseorder()
{
    reverseorder(root);
}

void btree::reverseorder(node* p)
{
    if (p != NULL) {
        reverseorder(p->right);
        cout << p->data << " ";
        reverseorder(p->left);
    }
}

bool btree::search(int val)
{
    if (root == NULL)
    {
        return false;
    }

    if (search_element(root, val) == true)
    {
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

void open_input(ifstream &input, string filename)
{
    input.open(filename.c_str());
    if (!input.is_open())
    {
        cout << "Cannot open input file: "
             << filename
             << endl;
        return;
    }
}

int main(int argc, char* argv[])
{
    btree my_tree;

    int ch, tmp, tmp1;
    bool ans;

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (isalpha(argv[i][0]))
            {
                string filename = argv[i];
                ifstream inputfile;
                open_input(inputfile, filename);
                while (inputfile >> tmp)
                {
                    my_tree.insert(tmp);
                }
            } else {
                tmp = atoi(argv[i]);
                my_tree.insert(tmp);
            }
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
        cout << " 7. Reverse-Order Traversal " << endl;
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
        case 7:
            cout << endl;
            cout << " Reverse Order Traversal: " << endl << endl;
            my_tree.print_reverseorder();
            break;
        }
    }
}
