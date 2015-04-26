/****************************************************************************************************
* Programming Tools for  Engineers and Scientists - HW9
* by Golnaz Sarram
* April 20th, 2015

* Github Repoitory: https://github.com/Golnaz15/btree/tree/Golnaz

* Homework Description:
* This code will translate knowledge about trees into a tangible code
* and gives us this opportunity to learn how to interact with a main repository
****************************************************************************************************/

#include <iostream>
#include <cstdlib>

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

private:

	void inorder(node*);
	void preorder(node*);
	void postorder(node*);

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
	if (root == NULL) return true;
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

	node *pnewnode, *tree;
	pnewnode->data = d;

	if ( isEmpty) {
		root = new node;
		root->data = pnewnode->data;
		root->left = NULL;
		root->right = NULL;
		cout << "Root is created" << endl;
		return;
	} else {
		if (search(d)) {
			cout << "Element already exist in the tree" << endl;
		} else {
			if (tree->data > pnewnode->data) {
				if (tree->left != NULL) {
					insert(d);
				} else {
					tree->left = pnewnode;
					(tree->left)->left = NULL;
					(tree->left)->right = NULL;
					cout << "New node added to the left" << endl;
				}
			} else {
				if (tree->right != NULL) {
					insert(d);
				} else { 
					tree->right = pnewnode;
					(tree->right)->left = NULL;
					(tree->right)->right = NULL;
					cout << "New node added to the right" <<endl;
					return;
				}
			}
		}
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
		search_element(root, val);
	}

	bool btree::search_element(node* p, int val) {
		// this function receives a node and an integer as
		// parameters and searches for the value val in the
		// data of the node. The function must be such that
		// if the value is never found, it returns false.
		// If the value is found, then it returns true.
		// The function must use recursion.

		bool found = false;
		node *ptraverse;
		if (val == root->data) {
			p = root;
			found = true;
			return;
		} 
		else { 
			if (val < root->data) {
				p = root->left
					//ptraverse = root;
			} 
			else {
				p = root->right;
				//ptraverse = root;
			}
		}
		while (p != NULL) {
			search_element(p, val);
		}
		/*
		if (val == p->data) {
		return true;
		}
		if (val < p->data) {
		p = p->left;
		} 
		else {
		p = p->right;
		}
		} */
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
			cout << " 5. Removal "<< endl;
			cout << " 6. Search "<< endl;
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
				// ***************************************************
				// If you decide to implement the extra credit options
				// this is one place where you will need to add code
				// to provide the user with those extra functions
				// ***************************************************
			}
		}
	}
