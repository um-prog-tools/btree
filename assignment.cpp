/**
* @Mainpage  Binary Search Tree implementation 
* This program have the following capabilities :
*
*   1. Insert a element to tree
*   2. Delete a element from the tree
*   3. It can traverse in different order
*   4. It search for a specific number
*   5. It can read element from an external file
*   6. It can give the highest length of the tree 
*/


/**
* @short  Main Program
* @file   sabber.cpp
* @author Sabber Ahamed
*/

#include <iostream>
#include <cstdlib>
#include <ctype.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class btree
/**
* @Class: Binary Search Tree 
* This class has all the functions that handles binary tree
*/


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
    void print_reverse_order();
    void print_preorder();
    void print_postorder();

    bool search(int);
    int findHeight();

private:

    void inorder(node*);
    void reverse_order(node*);
    void preorder(node*);
    void postorder(node*);

    bool search_element(node*, int);
    int findHeight(node*);

};

btree::btree() {
    /** 
    *   @Function  btree()
    *   This functions is the constructor of the class btree
    */
    root = NULL;
}

bool btree::isEmpty()
{
    /** 
    *   @Function  isEmpty()
    *   @param none
    *   @return bool
    *   This functions returns true if the tree is
    *   empty and false if it is not empty. You just
    *   need to look at the root.
    */

    bool isTrue = false;

    if (root == NULL) return isTrue = true;

    return isTrue;
}


void btree::insert(int d)
{
    /** 
    *   @Function  insert(int d)
    *   @param anyvalue d
    *   @return void
    *   This function must insert the value d in the tree
    *   first of all, check if d already exists in the tree
    *   you can do this by calling to the search(int) function
    *   if d is not in the tree already, create a new node with data equal d
    *   if the tree is empty, set the root to the new node
    *   if the tree is not empty, look for the right place where to insert d
    *   in order to do this, you may need to keep track of the potential
    *   parent node to which the new node will be attached as a child
    */

    node *temp, *parent;

    if (isEmpty()) {
        root = new node;
        root->data = d;
        root->right = NULL;
        root->left = NULL; 
        temp = root;
    }
    else if (search_element(root, d)) {
         cout << d << "  exists in the tree" << endl;
    }
    else {
        temp = root;
        while (temp != NULL) {

            if (d <= temp->data) {
                parent = temp;
                temp = temp->left;
            } else {
                parent = temp;
                temp = temp->right;
            }
        }

        node *newNode = new node;
        newNode->data = d;
        newNode->left = NULL;
        newNode->right = NULL;

        if (d <= parent->data)
            parent->left  = newNode;
        else
            parent->right = newNode;
    }
}


void btree::remove(int d)
{
    /** 
    *   @Function  remove(int d)
    *   @param anyvalue d
    *   @return void
    *   this function must remove the node that has the value d
    *   first of all, check if the tree is empty
    *   if it is not, then locate the element with the value
    *   once you know the location, that is, you have the pointer to the node
    *   with the value you want to eliminate, you will have three cases:
    *
    *      1. you're removing a leaf node
    *      2. you're removing a node with a single child
    *      3. you're removing a node with 2 children
    */

    if (root == NULL)
    {
        cout<<"Tree is empty"<<endl;
        return;

    } 
    // search if the number does not exist.
    if (!search(d)){

        std::cout <<  d << " is not found in the tree" << std::endl;
        return;
    } 
    //Case 1 : leaf node
    if (root->left == NULL && root->right == NULL){

        root = NULL;
        delete root;

    }
   // case 2 : one child
    else if (root->left != NULL && root->right == NULL){

         node *temp = root;
         root = root->left;
         delete temp;

    } else if (root->left == NULL && root->right != NULL) {

         node *temp = root;
         root = root->right;
         delete temp;

    } 
    // case 3 : two child
    // else (root->left != NULL && root->right != NULL) {
    // //int a;
    // //}
}

void btree::print_reverse_order()
{
   /** 
    *   @Function  print_reverse_order()
    *   @param none
    *   @return void
    *   This function print elements in reverse order
    */
    reverse_order(root);
}

void btree::reverse_order(node* p)
{
    /**  
    * 
    *   @Function  reverse_order(node* p)
    *   @param node*
    *   @return void
    *   This function receives a node as parameter
    *   then traverses the tree following the reverse order
    *   sequence. Every time it visits a node it will
    *   print the data in the node to cout leaving a blank
    *   space to separate from the next/previous value.
    *   The function must use recursion.
    */

    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    if (p != NULL)
    {
        reverse_order(p->right);
        cout << p->data <<"  ";
        reverse_order(p->left);
    }

}


void btree::print_inorder()
{
   /** 
    *   @Function  print_inorder()
    *   @param none
    *   @return void
    *   This function print elements in in order
    */
    inorder(root);
}

void btree::inorder(node* p)
{
    /**  
    * 
    *   @Function  inorder(node* p)
    *   @param node*
    *   @return void
    *   This function receives a node as parameter
    *   then traverses the tree following the in order
    *   sequence. Every time it visits a node it will
    *   print the data in the node to cout leaving a blank
    *   space to separate from the next/previous value.
    *   The function must use recursion.
    */

    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    if (p != NULL)
    {
        inorder(p->left);
        cout << p->data <<"  ";
        inorder(p->right);
    }

}

void btree::print_preorder()
{
   /** 
    *   @Function  print_preorder()
    *   @param none
    *   @return void
    *   This function print elements in pre order
    */
    preorder(root);
}

void btree::preorder(node* p)
{
    /**  
    * 
    *   @Function  preorder(node* p)
    *   @param node*
    *   @return void
    *   This function receives a node as parameter
    *   then traverses the tree following the pre order
    *   sequence. Every time it visits a node it will
    *   print the data in the node to cout leaving a blank
    *   space to separate from the next/previous value.
    *   The function must use recursion.
    */

    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    if (p != NULL)
    {
        cout << p->data << "  ";
        preorder(p->left);
        preorder(p->right);
    }
}

void btree::print_postorder()
{
   /** 
    *   @Function  print_postorder()
    *   @param none
    *   @return void
    *   This function print elements in post order
    */
    postorder(root);
}

void btree::postorder(node* p)
{
    /**  
    * 
    *   @Function  postorder(node* p)
    *   @param node*
    *   @return void
    *   This function receives a node as parameter
    *   then traverses the tree following the post order
    *   sequence. Every time it visits a node it will
    *   print the data in the node to cout leaving a blank
    *   space to separate from the next/previous value.
    *   The function must use recursion.
    */

    if (root == NULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    if (p != NULL)
    {
        postorder(p->left);
        postorder(p->right);
        cout << p->data << "  ";
    }

}

bool btree::search(int val)
{
    /** 
    *   @Function  search(int val)
    *   @param any value
    *   @return bool
    *   This function must call the private function
    *   search_element(node*,int) passing the root and
    *   the integer value val as parameters. The function
    *   must use recursion.
    */

    if(isEmpty()){
        std::cout << "The tree is empty, insert a number" << std::endl;
        return false;
    }
    if (search_element(root, val)) return true;
    else return false;

}

bool btree::search_element(node* p, int val) {

    /** 
    *   @Function  search_element(node* p, int val)
    *   @param node*, value
    *   @return bool
    *   This function receives a node and an integer as
    *   parameters and searches for the value val in the
    *   data of the node. The function must be such that
    *   if the value is never found, it returns false.
    *   If the value is found, then it returns true.
    *   The function must use recursion.
    */

    if (p != NULL){
        
        if (val == p->data) return true;
        else if (val < p->data) return search_element(p->left, val);
        else return search_element(p->right, val);
    }

    return false;
}
int btree::findHeight(node* root){

    /** 
    *   @Function  findHeight(node* root)
    *   @param node*
    *   @return int
    *   This function receives a node  as parameters and find
    *   the height of the tree
    */


    if (root == NULL) 
       return 0;
    else
    {
       /* compute the depth of each subtree */
       int lDepth = findHeight(root->left);
       int rDepth = findHeight(root->right);
 
       /* use the larger one */
       if (lDepth > rDepth) 
           return(lDepth+1);
       else return(rDepth+1);
    }

}
int btree::findHeight(){

   return findHeight(root);

}

int main(int argc, char* argv[])
{
    /** 
    * @Function (int argc, char* argv[])
    * @param argc, argv[]
    * @return int
    *
    * This is the main program.
    *
    * If the program is called without arguments, then
    *  the user is taken straight to the list of options
    *  if the program is called with parameters, the program
    *  assumes these parameters are a list of integers and
    *  inserts those into the tree.
    *
    *  Reading the program may help you understand how the
    *  class functions are called.
    *
    *  ********************** W A R N I N G **********************
    *  In general, you do not need to make any change in the main
    *  program.  The only case when you will need to make changes
    *  here is if you decide to implement the functions for extra
    *  credit. In which case, the place to make changes is indica-
    *  below.
    *  ***********************************************************
    */

    // instantiate the tree
    btree my_tree;

    // some auxiliary variables
    int ch,tmp,tmp1;
    bool ans;

    // if arguments are passed, then the program assumes the
    // arguments are a list of integers and it inserts one by
    // one into the tree.
    //char fileName = argv[1];
    if (argc  > 1) {


        if (isdigit(*argv[1])) {
            for (int i = 1; i < argc; i++) {
                tmp = atoi(argv[i]);
                my_tree.insert(tmp);
            }
        }
        else {           
            ifstream inputFile;
            inputFile.open(argv[1]);
            if (inputFile.fail()) {
                cout << "Error reading the file  " << endl;
                return 0;
            }
            else{

                int i = 0;
                string line;
                while (!inputFile.eof()){
                    getline(inputFile, line);
                    std::stringstream parse(line);
                    parse >> i;
                    my_tree.insert(i);
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
        cout << " 7. Height of the tree "<< endl;
        cout << " 8. Reverse Order Traversal "<< endl;
        // ***************************************************
        // If you decide to implement the extra credit options
        // this is one place where you will need to add code
        // to provide the user with those extra functions
        // ***************************************************
        cout << " 0. Exit "<< endl;
        cout << " Enter your choice : ";
        cin >> ch;
        switch(ch)
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
            cout << "Height of the tree : " << my_tree.findHeight() << endl;
            break;
        case 8:
            cout << endl;
            cout << " Reverse Order Traversal: " << endl << endl;
            my_tree.print_reverse_order();
            break;
        // ***************************************************
        // If you decide to implement the extra credit options
        // this is one place where you will need to add code
        // to provide the user with those extra functions
        // ***************************************************
        }
    }
}
