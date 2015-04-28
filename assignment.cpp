/**
 * @mainpage   Binary Search Tree
 *
 * Prog Tools for Scits Engrs - CIVL 8903/7903 001
 * Prof. Ricardo Taborda
 *
 * @author Naeem Khoshnevis, nkhshnvs@memphis.edu
 * @date   Apr 26, 2015
 *
 * @section Homework
 *
 *  9
 *
 * @section GitHub
 * https://github.com/Naeemkh/btree.git
 *
 * @section LICENSE
 *
 * This program is written at the Center for Earthquake Research
 * and Information (CERI) at University of Memphis.
 * All rights reserved.
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

class btree {
private:
    
    struct node {
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
    void print_rorder();
    void print_height();
    void print_lorder();
    
    bool search(int);
    
private:
    
    void inorder(node*);
    void preorder(node*);
    void postorder(node*);
    void rorder(node*);
    int tree_height(node*);
    void lorder(node*);
    void level_print(node*, int);
    void level_print_all(node*);
    
    bool search_element(node*, int);
    
};

btree::btree() {
    /**
     * set the root to NULL
     */
    root = NULL;
}

bool btree::isEmpty() {
    /**
     * This functions returns true if the tree is
     * empty and false if it is not empty. You just
     * need to look at the root.
     * \return 1 empty
     * \return 0 not empty
     */
    
    if (root == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void btree::insert(int d) {
    
    /*
     * this function must insert the value d in the tree
     *
     * first of all, check if d already exists in the tree
     * you can do this by calling to the search(int) function
     *
     * if d is not in the tree already, create a new node with data equal d
     *
     * if the tree is empty, set the root to the new node
     *
     * if the tree is not empty, look for the right place where to insert d
     * in order to do this, you may need to keep track of the potential
     * parent node to which the new node will be attached as a child
     *
     * \return void
     */
    
    node *parent_node, *temp_root; /** Defining parent and temporal root */
    
    if (btree::isEmpty()) {
        
        root = new node;
        root->data = d;
        root->left = NULL;
        root->right = NULL;
        temp_root = root;
        
    } else if (btree::search(d) == 1) {
        
    } else {
        temp_root = root;
        while (temp_root != NULL) {
            if (d < temp_root->data) {
                parent_node = temp_root;
                temp_root = temp_root->left;
                
            } else if (d > temp_root->data) {
                parent_node = temp_root;
                temp_root = temp_root->right;
            }
        }
        node *temp_node = new node;
        temp_node->data = d;
        temp_node->left = NULL;
        temp_node->right = NULL;
        
        if (d <= parent_node->data) {
            parent_node->left = temp_node;
            
        } else {
            parent_node->right = temp_node;
            
        }
    }
    
}

void btree::remove(int d) {
    /**
     * this function must remove the node that has the value d
     * first of all, check if the tree is empty
     * if it is not, then locate the element with the value
     * once you know the location, that is, you have the pointer to the node
     * with the value you want to eliminate, you will have three cases:
     *    1. you're removing a leaf node
     *    2. you're removing a node with a single child
     *    3. you're removing a node with 2 children
     * make sure you can handle all three cases.
     */
    
    /**
     * Making sure that btree is not empty
     * first case, deleting leaf node.
     * first make sure that the value is in the tree.
     */
    
    bool d_exist = btree::search(d);
    
    if (d_exist == 1) {
        
        //finding the position of the number.
        
        node *temp_root1, *temp_root2, *temp_root_max, *temp_root_bmax;
        
        temp_root1 = root;
        temp_root2 = root;
        
        while (temp_root1->data != d) {
            if (d < temp_root1->data) {
                temp_root2 = temp_root1; // previous node;
                temp_root1 = temp_root1->left;
            } else if (d > temp_root1->data) {
                temp_root2 = temp_root1; // previous node;
                temp_root1 = temp_root1->right;
            } else {
            }
        }
        
        if ((temp_root1->right == NULL) && (temp_root1->left == NULL)
            && (temp_root1->data != root->data)) {
            
            // the number is on the leaf.
            
            if (temp_root1->data < temp_root2->data) {
                delete temp_root1;
                temp_root2->left = NULL; // if the leaf is in the left side of previous node, now it should point to null.
            } else {
                delete temp_root1;
                temp_root2->right = NULL; // if the leaf is in the right side of previous node, now it should point to null.
            }
            
            if (btree::isEmpty() == 1) {
                
                root = NULL;
            }
            
        } else if ((temp_root1->right == NULL) && (temp_root1->left != NULL)
                   && (temp_root1->data != root->data)) {
            
            // the node only has one child on left side.
            
            if (temp_root2->data < temp_root1->data) {
                
                temp_root2->right = temp_root1->left;
                delete temp_root1;
                
            } else {
                
                temp_root2->left = temp_root1->left;
                delete temp_root1;
                
            }
            
        } else if ((temp_root1->right != NULL) && (temp_root1->left == NULL)
                   && (temp_root1->data != root->data)) {
            
            // the node only has one child on right side.
            
            if (temp_root2->data < temp_root1->data) {
                
                temp_root2->right = temp_root1->right;
                delete temp_root1;
                
            } else {
                
                temp_root2->left = temp_root1->right;
                delete temp_root1;
                
            }
        } else if ((temp_root1->right != NULL) && (temp_root1->left == NULL)
                   && (temp_root1->data == root->data)) {
            
            node *fnode_handle;
            
            fnode_handle = temp_root1->right;
            
            temp_root1->data = fnode_handle->data;
            temp_root1->right = fnode_handle->right;
            temp_root1->left = fnode_handle->left;
            delete fnode_handle;
            
        } else if ((temp_root1->right == NULL) && (temp_root1->left != NULL)
                   && (temp_root1->data == root->data)) {
            
            node *fnode_handle;
            
            fnode_handle = temp_root1->left;
            
            temp_root1->data = fnode_handle->data;
            temp_root1->right = fnode_handle->right;
            temp_root1->left = fnode_handle->left;
            delete fnode_handle;
            
        } else if ((temp_root1->right == NULL) && (temp_root1->left == NULL)
                   && (temp_root1->data == root->data)) {
            
            delete root;
            root = NULL;
        } else {
            
            /**
             * need to find the maximum number in the left hand side.
             * put the maximum number instead of the node data.
             * remove the max number.
             */
            
            int temp_max = temp_root1->data;
            int k = 1; // check to see whether is the first node in the left or not.
            
            temp_root_max = temp_root1->left;
            
            while (temp_root_max->right != NULL) {
                
                temp_root_bmax = temp_root_max;
                temp_root_max = temp_root_max->right;
                
                k = k + 1;
                
            }
            
            if (k > 1) {
                
                temp_root1->data = temp_root_max->data;
                
                temp_root_bmax->right = NULL;
                delete temp_root_max;
                
            } else {
                temp_root1->data = temp_root_max->data;
                temp_root1->left = temp_root_max->left;
                
                if (temp_root_max->left == NULL) {
                    delete temp_root_max;
                    temp_root1->left = NULL; // the case that we have only child on the left side.
                } else {
                    delete temp_root_max; // the case that we have children just on left side on the left side.
                }
                
            }
            
        }
        
    } else if (d_exist == 0) {
        
        cout << "The number is not in the list." << endl;
        
    }
    
}

void btree::print_inorder() {
    /**
     * this function must call the private inorder(node*)
     * function passing the root as the parameter
     */
    btree::inorder(root);
}

void btree::inorder(node* p) {
    /**
     * This function receives a node as parameter
     * then traverses the tree following the in-order
     * sequence. Every time it visits a node it will
     * print the data in the node to cout leaving a blank
     * space to separate from the next/previous value.
     * The function must use recursion.
     */
    
    if (p != NULL) {
        inorder(p->left);
        cout << p->data << " ";
        inorder(p->right);
    }
    
}

void btree::print_preorder() {
    /**
     * This function must call the private pre-order(node*)
     * function passing the root as the parameter
     */
    btree::preorder(root);
}

void btree::preorder(node* p) {
    /**
     * This function receives a node as parameter
     * then traverses the tree following the pre-order
     * sequence. Every time it visits a node it will
     * print the data in the node to cout leaving a blank
     * space to separate from the next/previous value.
     * The function must use recursion.
     */
    
    if (p != NULL) {
        
        cout << p->data << " ";
        preorder(p->left);
        preorder(p->right);
    }
}

void btree::print_postorder() {
    /**
     * This function must call the private post-order(node*)
     * function passing the root as the parameter
     */
    
    btree::postorder(root);
}

void btree::postorder(node* p) {
    /**
     * This function receives a node as parameter
     * then traverses the tree following the post-order
     * sequence. Every time it visits a node it will
     * print the data in the node to cout leaving a blank
     * space to separate from the next/previous value.
     * The function must use recursion.
     */
    
    if (p != NULL) {
        
        postorder(p->left);
        postorder(p->right);
        cout << p->data << " ";
    }
}

bool btree::search(int val) {
    /**
     * This function must call the private function
     * search_element(node*,int) passing the root and
     * the integer value val as parameters. The function
     * must use recursion.
     * \return 1 (find the number)
     * \return 0 (not find the number)
     */
    
    return (btree::search_element(root, val));
}

bool btree::search_element(node* p, int val) {
    /**
     * this function receives a node and an integer as
     * parameters and searches for the value val in the
     * data of the node. The function must be such that
     * if the value is never found, it returns false.
     * If the value is found, then it returns true.
     * The function must use recursion.
     */
    
    if (p == NULL) {
        
        return 0;
    } else if (val == p->data) {
        
        return 1;
        
    } else if (val < p->data) {
        
        // search again
        
        return search_element(p->left, val);
    } else {
        // search again
        return search_element(p->right, val);
    }
}

void btree::print_rorder() {
    btree::rorder(root);
}

void btree::rorder(node* p) {
    if (p != NULL) {
        rorder(p->right);
        cout << p->data << " ";
        rorder(p->left);
    }
}

void btree::print_height() {
    int h = btree::tree_height(root);
    cout << " " << h + 1 << endl;
}

int btree::tree_height(node* p) {
    if (p == NULL) {
        return -1;
    }
    
    int left = tree_height(p->left);
    int right = tree_height(p->right);
    
    return 1 + max(left, right);
    
}

void btree::print_lorder() {
    btree::level_print_all(root);
}

void btree::lorder(node* p) {
    
    if (p != NULL) {
        lorder(p->right);
        cout << p->data << " ";
        lorder(p->left);
        cout << p->data << " ";
        cout << "\n" << endl;
    }
}

void btree::level_print_all(node* p) {
    int h = btree::tree_height(root) + 1;
    int i;
    for (i = 1; i <= h; i++) {
        level_print(p, i);
        cout << "\n";
    }
}

void btree::level_print(node* p, int level) {
    if (p == NULL)
        return;
    if (level == 1)
        cout << p->data << " ";
    else if (level > 1) {
        level_print(p->left, level - 1);
        level_print(p->right, level - 1);
    }
}

int main(int argc, char* argv[]) {
    /**
     * This is the main program.
     * If the program is called without arguments, then
     * the user is taken straight to the list of options
     * if the program is called with parameters, the program
     * assumes these parameters are a list of integers and
     * inserts those into the tree.
     *
     * Reading the program may help you understand how the
     * class functions are called.
     *
     * ********************** W A R N I N G **********************
     * In general, you do not need to make any change in the main
     * program.  The only case when you will need to make changes
     * here is if you decide to implement the functions for extra
     * credit. In which case, the place to make changes is indica-
     * below.
     * ***********************************************************
     */
    
    // instantiate the tree
    btree my_tree;
    
    // some auxiliary variables
    int ch, tmp, tmp1;
    bool ans;
    
    // if arguments are passed, then the program assumes the
    // arguments are a list of integers and it inserts one by
    // one into the tree.
    
    int nd = 0; //number of digits
    
    if (argc == 2) {
        
        string pfilename = argv[1]; // store the potential filename in the pfilename.
        int sn = pfilename.size();   // number of char of file name.
        
        // calculate the number of digits inside the char,
        
        for (int i = 0; i < sn; i++) {
            if ((isdigit(pfilename[i]) == 1)) {
                nd = nd + 1;
            }
            
        }
        
        // if it is negative number add +1 to nd.
        stringstream temp_intstr;
        int temp_int, int_holder;
        
        temp_intstr << pfilename;
        temp_intstr >> temp_int;
        
        if ((temp_int < 0) == 1) {
            nd = nd + 1;
        }
        
        if ((nd == 0) && (sn > 0)) {
            
            ifstream inputfile;
            string inputfilename;
            inputfilename = pfilename;
            inputfile.open(inputfilename.c_str());
            
            if (!inputfile.is_open()) {
                cout << "Cannot open input file: " << pfilename << endl;
                exit(1);
            }
            
            cout << pfilename << " was read successfully!" << endl;
            
            while (inputfile >> int_holder) {
                
                my_tree.insert(int_holder);
                
            }
            
        } else if (nd < sn) {
            
            cout
            << "File name is not valid! (file name may contain alphabetic chars and dot.) "
            << endl;
            exit(EXIT_FAILURE);
            
        } else if (sn == nd) {
            
            for (int i = 1; i < argc; i++) {
                tmp = atoi(argv[i]);
                my_tree.insert(tmp);
            }
        }
        
    } else if (argc > 2) {
        
        for (int i = 1; i < argc; i++) {
            tmp = atoi(argv[i]);
            my_tree.insert(tmp);
        }
    }
    
    while (1) {
        cout << endl << endl;
        cout << " Binary Tree Operations " << endl;
        cout << " 1. Insertion/Creation " << endl;
        cout << " 2. In-Order Traversal " << endl;
        cout << " 3. Pre-Order Traversal " << endl;
        cout << " 4. Post-Order Traversal " << endl;
        cout << " 5. Removal " << endl;
        cout << " 6. Search " << endl;
        cout << " 7. Reverse-Order Traversal " << endl;
        cout << " 8. Tree's Height " << endl;
        cout << " 9. Level-Order Traversal " << endl;
        // ***************************************************
        // If you decide to implement the extra credit options
        // this is one place where you will need to add code
        // to provide the user with those extra functions
        // ***************************************************
        cout << " 0. Exit " << endl;
        cout << " Enter your choice : ";
        cin >> ch;
        switch (ch) {
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
                if (ans)
                    cout << tmp1 << " was found!!!" << endl;
                else
                    cout << tmp1 << " was not found" << endl;
                break;
            case 7:
                cout << " Reverse-Order Traversal: " << endl << endl;
                my_tree.print_rorder();
                break;
                
            case 8:
                cout << " Tree's Height: " << endl << endl;
                my_tree.print_height();
                break;
                
            case 9:
                cout << " Level-Order Traversal: " << endl << endl;
                my_tree.print_lorder();
                break;
                
                // ***************************************************
                // If you decide to implement the extra credit options
                // this is one place where you will need to add code
                // to provide the user with those extra functions
                // ***************************************************
        }
    }
}
