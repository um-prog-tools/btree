
/**
 * @mainpage The Binary Tree Practice Program
 */

 /**
 * @short   Homework 9
 * @file    assignment.cpp
 * @author  Yuan Zhou
 * @date    April 17th 2015
 *
 * This assignment has two main objectives:
 * (1) Understand the structure of binary tree and 
 *     implement the differnt functions operate with
 *     the structure of the tree.
 * (2) Learning how to interact with a main repository
 *     (with no push permission).
 * Extra objective:
 * (3) Try to use the right way to document the code,
 *     so that to run with the Documentation Generator.
 * Github Repository:  https://github.com/YuanZhou2015/btree/commits/Yuan
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
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
    //*********************************
    //    Bonus Functions prototype
    //*********************************
    void print_reverseorder();
    void print_height();
    void print_numberofinNode();
    void print_numberofLeaf();
    void print_totalNode();
    void print_LevelOrder();

private:

    void inorder(node*);
    void preorder(node*);
    void postorder(node*);
    bool search_element(node*, int);
    //*********************************** 
    //    Bonus Functions prototype
    //*********************************** 
    void reverseorder(node*);
    int height(node*);
    int l,r;
    int countinNode(node*);
    int countLeaf(node*);
    void LevelOrder(node*);
};

/** set the root to NULL */

btree::btree() {
    root = NULL;
}

/** This functions returns true if the tree is
 * empty and false if it is not empty.  
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

/** This functions insert the value d in the tree 
 * @param The integer number need to be inserted
 * @return boolean value
 */
void btree::insert(int d)
{
    node* insert_node = new node;
    insert_node->data = d;
    insert_node->left = NULL;
    insert_node->right = NULL;
    node* child_node = root;
    node* parent_node = NULL;

    // first of all, check if d already exists in the tree
    // if d is not in the tree already, create a new node 
    // with data equal d

    if(!search(d)){
        while (child_node != NULL){
            parent_node = child_node;
            if (insert_node->data < child_node->data){
                child_node = child_node->left;
            }
            else {
                child_node = child_node->right;
            }
        }
        
        // if the tree is empty, set the root to the new node
        
        if (parent_node == NULL){
            root = insert_node;
            root->left = NULL;
            root->right = NULL;
        }
        else{
            
            // if the tree is not empty, look for the right place where to insert d
            
            if (insert_node->data < parent_node->data)
                parent_node->left = insert_node;  
            else       
                parent_node->right = insert_node;
        }
    }
    else
        cout << "Number " << d << " is already in the tree.\n";        
}

/** This function must remove the node that has the value d
 * @param The integer need to be removed
 * @return none
*/

void btree::remove(int d)
{
    // first of all, check if the tree is empty

    if (root == NULL)
        return;

    // if it is not, then locate the element with the value

    node* child_node = root;
    node* parent_node = NULL;
    while(child_node != NULL && child_node->data != d){
        if (d < child_node->data){
            parent_node = child_node;
            child_node = child_node->left;
        }
        else{
            parent_node = child_node;
            child_node = child_node->right;
        }    
    }
    if (child_node == NULL){
        cout << "Number " << d << " is not in the tree.\n";
        return;
    }
    
    // once you know the location, that is, you have the pointer to the node
    // with the value you want to eliminate, you will have three cases:
    //    1. you're removing a leaf node

    if (child_node->left == NULL && child_node->right == NULL){
        if (child_node == root){
            root = NULL;
            cout << "Number " << d << " is deleted.\n";
            return;
        }
        if (child_node == parent_node->left){
            parent_node->left = NULL;
            cout << "Number " << d << " is deleted.\n";
        }
        else{
            parent_node->right = NULL;
            cout << "Number " << d << " is deleted.\n";
        }
        delete child_node;
        return;
    }

    //    2. you're removing a node with a single child
    // left leaf
    if (child_node->left != NULL && child_node->right == NULL){
        if (child_node == root){
            root = child_node->left;
            cout << "Number " << d << " is deleted.\n";
        }
        if (child_node == parent_node->left){
            parent_node->left = child_node->left;
            cout << "Number " << d << " is deleted.\n";
        }
        else{
            parent_node->right = child_node->left;
            cout << "Number " << d << " is deleted.\n";
        }
        delete child_node;
        return;
    }
    // right leaf
    if (child_node->left == NULL && child_node->right != NULL){
        if (child_node == root){
            root = child_node->right;
            cout << "Number " << d << " is deleted.\n";
            return;
        }
        if (child_node == parent_node->left){
            parent_node->left = child_node->right;
            cout << "Number " << d << " is deleted.\n";
        }
        else{
            parent_node->right = child_node->right;
            cout << "Number " << d << " is deleted.\n";
        }
        delete child_node;
        return;
    }

    //    3. you're removing a node with 2 children

    if (child_node->left != NULL && child_node->right != NULL){
        node* grandchild_node = child_node->left;
        if (grandchild_node->left == NULL && grandchild_node->right == NULL){
            child_node->data = grandchild_node->data;
            child_node->left = NULL;
            delete grandchild_node;
            cout << "Number " << d << " is deleted.\n";
        }
        else{
            if (grandchild_node->left != NULL && grandchild_node->right == NULL) {
                child_node->data = grandchild_node->data;
                child_node->left = grandchild_node->left;
                delete grandchild_node;
            }
            else{
                node* grc_right_node = grandchild_node->right;
                node* grc_rightP_node = grandchild_node;
                while (grc_right_node->right != NULL){
                    grc_rightP_node = grc_right_node;
                    grc_right_node = grc_right_node->right;
                }
                child_node->data = grc_right_node->data;
                grc_rightP_node->right = grc_right_node->left;
                delete grc_right_node;
                cout << "Number " << d << " is deleted.\n";
            }
        }
    }
}

/**
 * @short print out in inorder sequence
 * @param none
 * @return none
 *
 * Inorder traverse the binary from the root node 
 * by calling the function inorder(node*).
*/
void btree::print_inorder()
{
    inorder(root);
}

/** 
 * @short inorder traversal
 * @param p a node from which the traversal start
 * @return none
 *
 * This function receives a node as parameter then
 * traverses  the tree following the in-order sequence.
*/

void btree::inorder(node* p)
{
    if (p != NULL){
        inorder(p->left);
        cout << p->data << ' ';
        inorder(p->right);
    }
}
/**
 * @short print out in preorder sequence
 * @param none
 * @return none
 *
 * Preorder traverse the binary from the root node 
 * by calling the function preorder(node*).
*/
void btree::print_preorder()
{
    preorder(root);
}

/** 
 * @short preorder traversal
 * @param p a node from which the traversal start
 * @return none
 *
 * This function receives a node as parameter then
 * traverses the tree following the pre-order sequence.
*/
void btree::preorder(node* p)
{
    if (p != NULL){
        cout << p->data << ' ';
        preorder(p->left);
        preorder(p->right);
    }
}
/**
 * @short print out in postorder sequence
 * @param none
 * @return none
 *
 * Postorder traverse the binary from the root node 
 * by calling the functionpostorder(node*).
*/
void btree::print_postorder()
{
    postorder(root);
}

/** 
 * @short postorder traversal
 * @param p a node from which the traversal start
 * @return none
 *
 * This function receives a node as parameter then
 * traverses the tree following the post-order sequence.
*/
void btree::postorder(node* p)
{
    if(p !=NULL){
        postorder(p->left);
        postorder(p->right);
        cout << p->data <<' ';
    }

}
/**
 * @short search a integer in the tree
 * @param val the integer need to search
 * @return boolean value
 *
 * This function recieve a integer as parameter then
 * search the integer from the root node 
 * by calling the earch_element(node*,int).
*/
bool btree::search(int val)
{
    return search_element(root,val);
}

// this function receives a node and an integer as parameters and
// searches for the value val in the data of the node.
/** 
 * @short search an element in the tree
 * @param p a node from which the search start
 * @param val value of the integer need to search
 * @return boolean value
 *
 * This function receives a node and the value need to search 
 * as parameter, then look through the tree until find the node
 * which have the data with the same value.
*/
bool btree::search_element(node* p, int val) {
    if (p != NULL) {
        if (val == p->data) {
            return true;
        }
        else if (val < p->data){
                p = p->left;
                return search_element(p, val);
        }
        else{
                p = p->right;
                return search_element(p,val);
        }
    }
    else
    return false;
}

//*********************************************** 
//       Bonus Functions                          
//***********************************************

/**
 * @short print out in reverseorder sequence
 * @param none
 * @return none
 *
 * Reverseorder traverse the binary from the root node 
 * by calling the function reverseorder(node*).
*/
void btree::print_reverseorder()
{
    reverseorder(root);
} 

/** 
 * @short reverseorder traversal
 * @param p a node from which the traversal start
 * @return none
 *
 * This function receives a node as parameter then
 * traverses the tree following the reverse-order sequence.
*/
void btree::reverseorder(node* p)
{
    if (p != NULL){
        reverseorder(p->right);
        cout << p->data << ' ';
        reverseorder(p->left);
    }
}
void btree::print_height(){
    cout << height(root);
}
int btree::height(node* Height){
    if(Height == NULL){
        return 0;
    }
    else{
        return 1+max(height(Height->left),height(Height->right));
    }  
}

/**
 * @short Function to open input file
 * @param inputFile [in] the filestream to be open
 * @param fileName [in] the string of the input file name
 * @return boolean value 
 *
 * This function receives a ifstream and a string as
 * parameters. Then check if the inputfile is opened
 * successfully. Finally, return the result that the
 * file is open or not.
 */

bool openInput(ifstream &inputFile, string fileName) {

    inputFile.open(fileName.c_str());

    // perform sanity check it
    if (!inputFile.is_open()) {
        cout << "Cannot open input file: " + fileName + "\n";
        return false;
    }

    return true; 
}

void btree::print_numberofinNode(){
    cout << countinNode(root);
}

/** 
 * @short Function for counting the interior nodes
 * @param node the node from which start to count the node number
 * @return the number of the interior nodes
 *
 * This funciton recieves a node as a parameter 
 * from which it starts to count the interior node,
 * then return the number of the interior node.
*/

int btree::countinNode(node* node){
    if (node == NULL){
        return 0;
    }
    if (node->left == NULL && node->right == NULL){
        return 0;
    }
    else{
        return countinNode(node->left)+ countinNode(node->right) + 1;
    }
}

void btree::print_numberofLeaf(){
    cout << countLeaf(root);
}

/** 
 * @short Function for counting the leaf nodes
 * @param node the node from which start to count the leaf number
 * @return the number of the leaf nodes
 *
 * This funciton recieves a node as a parameter 
 * from which it starts to count the leaf node,
 * then return the number of the interior node.
*/

int btree::countLeaf(node* node){
    if (node == NULL){
        return 0;
    }
    if (node->left == NULL && node->right == NULL){
        return 1;
    }
    else{
        return countLeaf(node->left)+ countLeaf(node->right);
    }
}

/** 
 * @short Function for offering the total number of node
 * @param none
 * @return none
*/
void btree::print_totalNode(){
    cout << countLeaf(root) + countinNode(root);
}

/** 
 * @short Function for printing the tree in level order
 * @param none
 * @return none
 *
 * This funciton is to print the tree in level order 
 * from the root by calling the function LevelOrder(*).
*/
void btree::print_LevelOrder(){
    LevelOrder(root);
}
/** 
 * @short Print tree in level order
 * @param p the node from which start to print
 * @return none
 *
 * This funciton recieves a node as a parameter 
 * from which it starts to print the tree,
 * then print out the tree in the level order.
*/
void btree::LevelOrder(node* p){
    if (!p){
        cout << " The tree is empty.";
        return;
    }
    queue<node*> nodesQueue;
    int nodeinCurrentLevel = 1;
    int nodeinNextlevel = 0;
    nodesQueue.push(p);
    while (!nodesQueue.empty()) {
        node* currentNode = nodesQueue.front();
        nodesQueue.pop();
        nodeinCurrentLevel --;
        if (currentNode){
            cout << currentNode->data << ' ';
            nodesQueue.push(currentNode->left);
            nodesQueue.push(currentNode->right);
            nodeinNextlevel += 2;
        }
        if (nodeinCurrentLevel == 0){
            cout << endl;
            nodeinCurrentLevel = nodeinNextlevel;
            nodeinNextlevel = 0;
        }
    }    
} 

/**
 *@short Main Program
 *@param  integer numbers to input into the tree or a file name
 *@return  0 on success
 *
 * This program could take initial integer numbers by argument or 
 * reading them from a input file when the argument is alphabatic.
 * The program could store these numbers into a binary tree, then
 * it could accomplish the task asked by user when they choose the
 * corresponding option.
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

    /** instantiate the tree */
    btree my_tree;

    // some auxiliary variables
    int ch,tmp,tmp1;
    bool ans;

    /**
        If the program is called WITHOUT arguments, then
        the user is taken straight to the list of options
    */

    //***********************************************************  
    // Bonus for Reading numbers from an input file.
    //***********************************************************

    /**
        If an argument is passed to the program and that argument 
        is ALPHABETIC, the program will assume that it refers to 
        an input file and the input file will contain a sequence 
        of numbers which will be read and stored in the tree 
        before prompting the menu to the terminal.

        Else, then the program assumes the arguments are a list 
        of integers and it inserts one by one into the tree. 
    */

    if (argc > 1) {
        if (isalpha(*argv[1])){
            ifstream inputFile;
            int number;
            for (int i = 1; i < argc; i++) {
                openInput(inputFile, argv[i]);
                while(inputFile>>number){
                    my_tree.insert(number);
                }
            }
        }
        else{
            for (int i = 1; i < argc; i++) {
                tmp = atoi(argv[i]);
                my_tree.insert(tmp);
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

        // ***************************************************
        // provide the user with extra functions
        // ***************************************************
        cout << " 7. Reverse Order Traversal " << endl;
        cout << " 8. Provid the height of the tree " << endl;
        cout << " 9. Track the nodes in the tree" << endl;
        cout << "    (Number of Total, Interior and Leaf node)" << endl;
        cout << " 10. Print the tree by levels" << endl;
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
        //***************************************************
        //     Implement the extra credit options
        //***************************************************
        case 7:
            cout << endl;
            cout << " Reverse Order Traversal: " << endl << endl;
            my_tree.print_reverseorder();
            break;
        case 8:
            cout << endl;
            cout << " The height of this tree is: ";
            my_tree.print_height(); 
            break;
        case 9:
            cout << endl;
            cout << " The total number of node of this tree is: ";
            my_tree.print_totalNode();
            cout << endl << " Number of interior node is: ";
            my_tree.print_numberofinNode();
            cout << endl << " Number of leaf node is: ";
            my_tree.print_numberofLeaf();
            break;
        case 10:
            cout << endl;
            cout << " Printing the tree by levels: " << endl;
            my_tree.print_LevelOrder(); 
            break;
        }
    }
}
