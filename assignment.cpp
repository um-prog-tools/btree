
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <fstream>

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
	void display(int);

	bool search(int);

private:

	void inorder(node*);
	void preorder(node*);
	void postorder(node*);
	void reverseorder(node*);
	void display_levels(node*, int);

	bool search_element(node*, int);

};

btree::btree() {

	// set the root to NULL
	root = NULL;
}

bool btree::isEmpty()
{
	// This functions returns true if the tree is
	// empty and false if it is not empty. You just
	// need to look at the root.
	bool notempty = false;
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
	// if d is not in the tree already, create a new node with data equal d

	// if the tree is empty, set the root to the new node

	// if the tree is not empty, look for the right place where to insert d
	// in order to do this, you may need to keep track of the potential
	// parent node to which the new node will be attached as a child

	node *pnewnode = new node;
	node *ptrsave = NULL;
	node *tree = root;
	pnewnode->data = d;

	if ( isEmpty()) {
		root = new node;
		root->data = pnewnode->data;
		root->left = NULL;
		root->right = NULL;
		cout << "Root is created" << endl;
		return;
	}

	while (tree != NULL) {
		ptrsave = tree;
		if (tree->data > pnewnode->data) {
			tree = tree->left;
		} else {
			if (tree->data < pnewnode->data) {
				tree = tree->right;
			}
		}
	}
	if (ptrsave->data > pnewnode->data) {
		ptrsave->left = pnewnode;
		pnewnode->left = NULL;
		pnewnode->right = NULL;
		cout << "New node added to the left" << endl;
	} else {
		ptrsave->right = pnewnode;
		pnewnode->left = NULL;
		pnewnode->right = NULL;
		cout << "New node added to the right" <<endl;
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

	node *parent = NULL;
	node *location = root;

	if (isEmpty()) {
		return;
	}
	if (!search(d)) {
		cout << "Item not present in the tree" << endl;
		return;
	}

	// first finding the location of d and the parent

	while (location != NULL && d != location->data) {
		parent = location;
		if (d < location->data) {
			location = location->left;
		} else {
			location = location->right;
		}
	}

	// case_1_leaf:

	if (location->left == NULL && location->right == NULL) {

		if (parent == NULL) {
			root = NULL;
		} else {
			if (location == parent->left) {
				parent->left = NULL;
			} else {
				parent->right = NULL;
			}
		}
		free(location);
		return;
	}

	// case_2_single_child:

	if ((location->left != NULL && location->right == NULL) ||
		(location->left == NULL && location->right != NULL)) {

			node *child;
			if (location->left != NULL) {
				child = location->left;
			} else {
				child = location->right;
			}
			if (parent = NULL) {
				root = child;
			} else {
				if (location == parent->left) {
					parent->left = child;
				} else {
					parent->right = child;
				}
			}
			free(location);
			return;
	}

	// case_3_two children:

	if (location->left != NULL && location->right != NULL) {

		node *ptrsave = location;
		node *ptr = location->right;

		while (ptr->left != NULL) {
			ptrsave = ptr;
			ptr = ptr->left;
		}

		node *grand_child = ptr;
		node *pargrand_child = ptrsave;

		if (grand_child->left == NULL && grand_child->right == NULL) {
			if (pargrand_child == NULL) {
				root = NULL;
			} else {
				if (grand_child == pargrand_child->left) {
					pargrand_child->left = NULL;
				} else {
					pargrand_child->right = NULL;
				}
			}
		} else {
			node *child;
			if (grand_child->left != NULL) {
				child = grand_child->left;
			} else {
				child = grand_child->right;
			}
			if (pargrand_child = NULL) {
				root = child;
			} else {
				if (grand_child == pargrand_child->left) {
					pargrand_child->left = child;
				} else {
					pargrand_child->right = child;
				}
			}
		}
		if (parent == NULL) {
			root = grand_child;
		} else {
			if (location == parent->left) {
				parent->left = grand_child;
			} else {
				parent->right = grand_child;
			}
		}
		grand_child->left = location->left;
		grand_child->right = location->right;
		free(location);
		return;
	}
}

void btree::print_inorder()
{
	// this function must call the private inorder(node*)
	// function passing the root as the parameter
	inorder (root);
}

void btree::inorder(node* p)
{
	// This function receives a node as parameter
	// then traverses the tree following the in-order
	// sequence. Every time it visits a node it will
	// print the data in the node to cout leaving a blank
	// space to separate from the next/previous value.
	// The function must use recursion.

	//node *ptraverse;

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
		preorder(p->left);
		preorder(p->right);
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
		postorder(p->left);
		postorder(p->right);
		cout << p->data << " ";
	}
}

void btree::print_reverseorder()
{
	// this function must call the private inorder(node*)
	// function passing the root as the parameter
	reverseorder(root);
}

void btree::reverseorder(node* p)
{
	// This function receives a node as parameter
	// then traverses the tree following the in-order
	// sequence. Every time it visits a node it will
	// print the data in the node to cout leaving a blank
	// space to separate from the next/previous value.
	// The function must use recursion.

	//node *ptraverse;

	if (p != NULL) {

		reverseorder(p->right);
		cout << p->data << " ";
		reverseorder(p->left);
	}
}

bool btree::search(int val)
{
	// This function must call the private function
	// search_element(node*,int) passing the root and
	// the integer value val as parameters. The function
	// must use recursion.

	if (search_element(root, val)) {
		return true;
	} else { 
		return false;
	}
}

bool btree::search_element(node* p, int val) {
	// this function receives a node and an integer as
	// parameters and searches for the value val in the
	// data of the node. The function must be such that
	// if the value is never found, it returns false.
	// If the value is found, then it returns true.
	// The function must use recursion.

	//bool found = true;
	int num_of_occurance = 0;
	node *location, *ptrsave; //*parent, 
	location = p;
	ptrsave = NULL;

	if (val == location->data) {
		num_of_occurance++;
		cout << "Item was found with occurence of " << num_of_occurance << " times" << endl;
		return true;
	} else { 
		if (val < location->data) {
			ptrsave = location;
			location = location->left;
		} else {
			ptrsave = location;
			location = location->right;
		}
	}
	if (location != NULL) {
		search_element(location, val);
	} else {
		return false;
	}
}

void btree::display(int level) {
	// This function must call the private function
	// search_element(node*,int) passing the root and
	// the integer value val as parameters. The function
	// must use recursion.

	display_levels(root, level);
}

void btree::display_levels(node* p, int level) {
	int i;
    if (p != NULL) {
        display_levels(p->right, level+1);
        cout << endl;
        if (p == root) {
            cout << "Root->:  ";
		} else {
            for (i = 0; i < level; i++)
                cout<<"   ";
	}
        cout << p->data ;
        display_levels(p->left, level+1);
    }
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
	int ch,tmp,tmp1;
	bool ans;

	// if arguments are passed, then the program assumes the
	// arguments are a list of integers and it inserts one by
	// one into the tree.
	if (argc > 1) {
		for (int i=1; i < argc; i++) {
			tmp = atoi(argv[i]);
			my_tree.insert(tmp);
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
		cout << " 5. Reverse-Order Traversal " << endl;
		cout << " 6. Removal "<< endl;
		cout << " 7. Search "<< endl;
		cout << " 8. Display "<< endl;
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
			cout << endl;
			cout << " Reverse Traversal: " << endl << endl;
			my_tree.print_reverseorder();
			break;
		case 6:
			cout << " Enter data to be deleted: ";
			cin >> tmp1;
			my_tree.remove(tmp1);
			break;
		case 7:
			cout << " Enter data to be searched: ";
			cin >> tmp1;
			ans = my_tree.search(tmp1);
			if (ans) cout << tmp1 << " was found!!!" << endl;
			else cout << tmp1 << " was not found" << endl;
			break;
		case 8:
			cout<<"Enter the level to display:"<<endl;
			cin >> tmp1;
			my_tree.display(tmp1);
			cout<< endl;
			break;
			// ***************************************************
			// If you decide to implement the extra credit options
			// this is one place where you will need to add code
			// to provide the user with those extra functions
			// ***************************************************
		}
	}
}
