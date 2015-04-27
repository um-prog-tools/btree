/**
 * @mainpage CIVL 8903/7903 Prog Tools for Scits Engrs Homework 9
 * 
 * This the homework 9 of CIVL 8903 which implements the basic functions
 * of the binary tree. The homewrok is done by interacting with a main
 * repository.
 */

#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>
#include <cctype>
#include <string>
#include <fstream>

using namespace std;

/**
   * @brief   This class to implement the basic function of binary tree
 */
class btree
{
private:

    /**
      * @brief   the struct of the node
      * contain left node, right node, data and its occurrence time
    */
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

    /**
      * @brief   the default constructor of this class
    */
    btree();

    /**
      * @brief   Check whether the tree is empty
      * @return  true if the tree is empty
    */
    bool isEmpty();

    /**
      * @brief   insert a number to the binary search tree
      * @param   d the number need inserting
    */
    void insert(int d);

    /**
      * @brief   delete a number in the binary search tree
      * @param   d the number need deleting
    */
    void remove(int d);

    /**
      * @brief   inorder tranversal public function
    */
    void print_inorder();

    /**
      * @brief   preorder tranversal public function
    */
    void print_preorder();

    /**
      * @brief   postorder tranversal public function
    */
    void print_postorder();

    /**
      * @brief   reverse order tranversal public function
    */
    void print_reveorder();

    /**
      * @brief   print out the tree by level public function
    */
    void print_level();

    /**
      * @brief   search function
      * @param   val the number need searching
      * @return  true if searched
    */
    int search(int val);

    /**
      * @brief   give the height of the tree public function
      * @return  the height of the tree
    */
    int height();

    /**
      * @brief   give the number of leaves in this tree
      * @return  the number of leaves in the tree
    */
    int get_number_of_leaves();

    /**
      * @brief   give the number of nodes in this tree
      * @return  the number of nodes in the tree
    */
    int get_number_of_nodes();

private:

    // some private function to help implement its public version
    void inorder(node*);
    void preorder(node*);
    void postorder(node*);
    void reveorder(node*, stack<node*> &);
    void print_node(node*);

    int height(node*);

    int search_element(node*, int);

    int number_of_leaves(node *);

    int numberOfNodes;

};

/**
   * @brief   This function check whether a given string is an integer
   * @param   text input string
   * @return  true on success
 */
bool is_integer(string text);

/**
   * @short   Main program
   * @file    assignment.cpp
   * @author  Yang Yang
   * @param   initial numbers or a file name in which contains a bunch of numbers
   * @return  0 on success
   * 
   * This program creat a user frienly interface to manipulate the function of class
   * btree. The btree is initialed with the numbers inputed as the the parameters when
   * running the program. Users can also insert, delete, trversal ... by the prompt.
 */
int main(int argc, char* argv[]) {

    /** 
      * If the program is called without arguments, then
      * the user is taken straight to the list of options
      * if the program is called with parameters, the program
      * assumes these parameters are a list of integers and
      * inserts those into the tree.
    */

    // instantiate the tree
    btree my_tree;

    // some auxiliary variables
    int ch,tmp,tmp1,ans;
    string tmp_str;

    /** 
      * arguments are passed, then the program assumes the
      * arguments are a list of integers and it inserts one by
      * one into the tree. If an argument is not an integer, I
      * assume it is a file contains a sequence of integers
    */
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (is_integer(argv[i])) {
                tmp = atoi(argv[i]);
                my_tree.insert(tmp);
            } else {
                ifstream input_file(argv[i]);

                if (!input_file.is_open()) {
                    cout << "Warning: file " << argv[i] << " doesn't exist!" << endl;
                    continue;
                } else {
                    cout << "Reading numbers in file " << argv[i] << endl;
                    while (input_file >> tmp_str) {
                        if (is_integer(tmp_str)) {
                            tmp = atoi(tmp_str.c_str());
                            my_tree.insert(tmp);
                        } else {
                            cout << "Warning: " << tmp_str << " is not a number! Skip it!" << endl;
                            continue;
                        }
                    }

                    input_file.close();
                }
            } 
            
        }
    }

    while(1)
    {
        cout << endl << endl;
        cout << " Binary Tree Operations " << endl;
        cout << " 1. Insertion/Creation " << endl;
        cout << " 2. In-Order Traversal " << endl;
        cout << " 3. Pre-Order Traversal " << endl;
        cout << " 4. Post-Order Traversal " << endl;
        cout << " 5. Removal "<< endl;
        cout << " 6. Search "<< endl;
        cout << " 7. Reverse-Order Traversal " << endl;
        cout << " 8. Display height of the tree " << endl;
        cout << " 9. By-Level Traversal " << endl;
        cout << " 10. Print number of Nodes " << endl;
        cout << " 0. Exit "<< endl;
        cout << " Enter your choice : ";

        cin >> ch;

        if (cin.fail()) {
            // if ch is not an int.
            cerr << "Please enter a correct choice!" << endl;
            cin.clear();
            std::cin.ignore(256,'\n');
            continue;
        }

        switch(ch)
        {
        case 0:
            return 0;
        case 1:
            cout << endl;
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
            cout << endl;
            cout << " Enter number to be deleted: ";
            cin >> tmp1;
            my_tree.remove(tmp1);
            break;
        case 6:
            cout << endl;
            cout << " Enter number to be searched: ";
            cin >> tmp1;
            ans = my_tree.search(tmp1);
            if (ans) cout << tmp1 << " was found with occurence times " << ans << "!!!" << endl;
            else cout << tmp1 << " was not found!!!" << endl;
            break;
        case 7:
            cout << endl;
            cout << "Reverse-Order Traversal: " << endl << endl;
            my_tree.print_reveorder();
            break;
        case 8:
            cout << endl;
            cout << "Height of the tree: " << my_tree.height();
            break;
        case 9:
            cout << endl;
            cout << " By-Level Traversal: " << endl << endl;
            my_tree.print_level();
            break;
        case 10:
            cout << endl;
            tmp = my_tree.get_number_of_nodes();
            tmp1 = my_tree.get_number_of_leaves();
            cout << "The tree has " << tmp << " total nodes." << endl;
            cout << tmp1 << " are leaves and " << tmp - tmp1 << " are interior nodes" << endl;
            break;
        default:
            cerr << "Please enter a correct choice!" << endl;
            break;
        }
    }
}

btree::btree() {

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

    // creat a node which data is d
    node * new_node = new node;
    new_node->data = d;

    // some auxiliary variables
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
            (current_node->occurrences)++;
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
    // first of all, check if the tree is empty
    if (root == NULL) {
        return;
    } 

    // some auxiliary variables
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
    if (current_node->occurrences > 1) {
        (current_node->occurrences)--;
        return;
    }

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
    if (current_node->left != NULL && current_node->right != NULL) {
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

    inorder(root);

}

void btree::inorder(node* p)
{
    // recursive alogorithm to implment in order tranversal

    if (p != NULL) {
        inorder(p->left);
        print_node(p);
        inorder(p->right);
    }

}

void btree::print_preorder()
{

    preorder(root);

}

void btree::preorder(node* p)
{
    // recursive alogorithm to implment pre order tranversal

    if (p != NULL) {
        print_node(p);
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
    // recursive alogorithm to implment post order tranversal
    if (p != NULL) {
        postorder(p->left);
        postorder(p->right);
        print_node(p);
    }

}

void btree::print_reveorder() {

    // use stack to store the result of in order traversal
    stack<node *> treeStack;
    
    reveorder(root, treeStack);

    while(!treeStack.empty()) {
        print_node(treeStack.top());
        treeStack.pop();
    }

}

void btree::reveorder(node* p, stack<node *> &myStack) {

    // recursive alogorithm to implment reverse order tranversal
    if (p != NULL) {
        reveorder(p->left, myStack);
        myStack.push(p);
        reveorder(p->right, myStack);
    }

}

void btree::print_level() {

    queue<node *> nodeQueue;

    if (root == NULL) {
        return;
    }

    node *tmp, *leftNode, *rightNode;

    nodeQueue.push(root);
    nodeQueue.push(NULL);

    int level = 0;

    cout << "level " << level << ": ";
    while(!nodeQueue.empty()) {
        tmp = nodeQueue.front();
        nodeQueue.pop();

        if (tmp != NULL) {
            print_node(tmp);

            leftNode = tmp->left;
            rightNode = tmp->right;
            if (leftNode != NULL) {
                nodeQueue.push(leftNode);
            }
            if (rightNode !=NULL ) {
                nodeQueue.push(rightNode);
            }
        } else {
            if (!nodeQueue.empty()) {
                level++;
                nodeQueue.push(NULL);
                cout << endl << "level " << level << ": ";;
            }
        }
    }

}

int btree::search(int val)
{
    // This function must call the private function
    // search_element(node*,int) passing the root and
    // the integer value val as parameters.

    return search_element(root, val);

}

int btree::search_element(node* p, int val) {
    // this function receives a node and an integer as
    // parameters and searches for the value val in the
    // data of the node. The function must be such that
    // if the value is never found, it returns false.
    // If the value is found, then it returns true.
    // The function must use recursion.

    if (p != NULL) {
        if (val == p->data) {
            return p->occurrences;
        } else if (val < p->data) {
            return search_element(p->left, val);
        } else {
            return search_element(p->right, val);
        }
    } else {
        return 0;
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

void btree::print_node(node* p) {

    if (p->occurrences == 1) {
        cout << p->data << " ";
    } else {
        cout << p->data << "(" << p->occurrences << ") ";
    }

}

int btree::get_number_of_leaves() {

    return number_of_leaves(root);

}

int btree::number_of_leaves(node *p) {

    if (p == NULL) {
        return 0;
    }

    if (p->left == NULL && p->right == NULL) {
        return 1;
    } else {
        return number_of_leaves(p->left) + number_of_leaves(p->right);
    }

}

int btree::get_number_of_nodes() {

    return numberOfNodes;

}

bool is_integer(string text) {
    
    int len = static_cast<int>(text.length());

    for (int i = 0; i < len; i++) {
        if (!isdigit(text[i]) && !(text[i] == '-' && i == 0) && !(text[i] == '+' && i == 0)) {
            return false;
        }
    }
    
    return true;
    
}