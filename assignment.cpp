// Created By Darin Nelson
// Homework #9

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <stdio.h>
#include <math.h>

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
	int  print_height();
	void print_totalnodes();
	void print_bylevels();

	bool search(int);

private:

	void inorder(node*);
	void preorder(node*);
	void postorder(node*);
	void reverseorder(node*);
	int  height(node*);
	void totalnodes(node*, int &total, int &interior, int &leaf);
	void bylevels(node*, int h);

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
	// This functions returns true if the tree is
	// empty and false if it is not empty. You just
	// need to look at the root.
}

void btree::insert(int d)
{

	node* child;
	node* parent;
	node* createnode;

	child = root;
	parent = NULL;
	createnode = new node;
	createnode->data = d;
	createnode->left = NULL;
	createnode->right = NULL;

	if (search(d) == false) {
		if (isEmpty() == true) {
			root = createnode;
		} else {
HERE:
			if (child != NULL) {
				parent = child;
				if (d < child->data) {
					child = child->left;
				} else {
					child = child->right;
				}
				goto HERE;
			}

			if (parent->data > d) {
				parent->left = createnode;
			} else {
				parent->right = createnode;
			}
		}
	} else {
		cout << "The Number " << d << " is already part of the existing tree.\n";
	}

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

	node *parent = NULL;
	node *child = root;
	node *bad;
	node *badParent;

	if (isEmpty() != true) {
		if (search(d) == true) {
HERE:
			if (child != NULL && d != child->data) {
				parent = child;
				if (d < child->data) {
					child = child->left;
					goto HERE;
				} else {
					child = child->right;
					goto HERE;
				}
			}

			if (child == NULL) {
				cout << "Number not in tree.\n";
				return;
			} else {
				if (child == root) {
					bad = root;
					badParent = NULL;
				} else {
					bad = child;
					badParent = parent;
				}
			}

			if (bad->right == NULL && bad->left == NULL)	{
				if (badParent == NULL) {
					root = NULL;
					return;
				} else if (bad == badParent->left) {
					badParent->left = NULL;
					delete bad;
					return;
				} else if (bad == badParent->right) {
					badParent->right = NULL;
					delete bad;
					return;
				}
			} else if (bad->left != NULL && bad->right == NULL) {
				if (bad == root) {
					root = bad->left;
					return;
				} else if (bad == badParent->left) {
					badParent->left = bad->left;
					delete bad;
					return;
				} else if (bad == badParent->right) {
					badParent->right = bad->left;
					delete bad;
					return;
				}
			} else if (bad->left == NULL && bad->right != NULL) {
				if (bad == root) {
					root = bad->right;
					return;
				} else if (bad == badParent->left) {
					badParent->left = bad->right;
					delete bad;
					return;
				} else if (bad == badParent->right) {
					badParent->right = bad->right;
					delete bad;
					return;
				}
			} else {
				node* next = bad->left;
				if (next->left == NULL && next->right == NULL) {
					bad->data = next->data;
					bad->left = NULL;
					delete next;
				} else if (next->left != NULL && next->right == NULL) {
					bad->data = next->data;
					child->left = next->left;
					delete next;
				} else {
					node* info = next->right;
					node* info2 = next;
					while (info->right != NULL) {
						info2 = info;
						info = info->right;
					}
					bad->data = info->data;
					info2->right = info->left;
					delete info;

				}

			}

		} else {
			cout << "The number " << d << " does not exist in the tree.";
		}
	} else {
		cout << "The tree is empty.";
	}


	// Case 2: Deleting node with two children

	// Find the replacement value.  Locate the node
	// containing the largest value smaller than the
	// key of the node being deleted.

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

	inorder(root);

	// this function must call the private inorder(node*)
	// function passing the root as the parameter
}

void btree::inorder(node* p)
{

	if (p != NULL) {
		inorder(p->left);
		cout << p->data << " ";
		inorder(p->right);
	}

	// This function receives a node as parameter
	// then traverses the tree following the in-order
	// sequence. Every time it visits a node it will
	// print the data in the node to cout leaving a blank
	// space to separate from the next/previous value.
	// The function must use recursion.
}

void btree::print_preorder()
{

	preorder(root);

	// This function must call the private pre-order(node*)
	// function passing the root as the parameter
}

void btree::preorder(node* p)
{

	if (p != NULL) {
		cout << p->data << " ";
		preorder(p->left);
		preorder(p->right);
	}
	// This function receives a node as parameter
	// then traverses the tree following the pre-order
	// sequence. Every time it visits a node it will
	// print the data in the node to cout leaving a blank
	// space to separate from the next/previous value.
	// The function must use recursion.
}

void btree::print_postorder()
{

	postorder(root);

	// This function must call the private post-order(node*)
	// function passing the root as the parameter
}

void btree::postorder(node* p)
{

	if (p != NULL) {
		postorder(p->left);
		postorder(p->right);
		cout << p->data << " ";
	}

	// This function receives a node as parameter
	// then traverses the tree following the post-order
	// sequence. Every time it visits a node it will
	// print the data in the node to cout leaving a blank
	// space to separate from the next/previous value.
	// The function must use recursion.
}

void btree::print_reverseorder()
{

	reverseorder(root);

	// This function must call the private post-order(node*)
	// function passing the root as the parameter
}

void btree::reverseorder(node* p)
{

	if (p != NULL) {
		reverseorder(p->right);
		cout << p->data << " ";
		reverseorder(p->left);
	}

	// This function receives a node as parameter
	// then traverses the tree following the post-order
	// sequence. Every time it visits a node it will
	// print the data in the node to cout leaving a blank
	// space to separate from the next/previous value.
	// The function must use recursion.
}

int btree::print_height()
{

	return height(root);

}

int btree::height(node* p)
{

	if (p == NULL) {
		return 0;
	}

	int lefttree = height(p->left);
	int righttree = height(p->right);

	if (lefttree > righttree) {
		lefttree++;
		return lefttree;
	} else {
		righttree++;
		return righttree;
	}

}

void btree::print_totalnodes()
{
	int total = 0, interior = 0, leaf = 0;
	totalnodes(root, total, interior, leaf);

	cout << "Number of Nodes = " << total << endl;
	cout << "Number of Interior Nodes = " << interior << endl;
	cout << "Number of Leaf Node = " << leaf << endl;

}

void btree::totalnodes(node* p, int &total, int &interior, int &leaf)
{

	if (p == NULL) {
		return;
	} else {
		if (p->left == NULL && p->right == NULL) {
			total++;
			leaf++;
			return;
		} else {
			totalnodes(p->left, total, interior, leaf);
			totalnodes(p->right, total, interior, leaf);
			total++;
			interior++;
			return;
		}
	}

}

void btree::print_bylevels()
{

	int h = height(root);
	if (h == 0) {
		cout << "The tree is empty.\n";
		return;
	} else {
		for (int i = 1; i <= h; i++) {
			bylevels(root, i);
		}
	}

}

void btree::bylevels(node* p, int i)
{

	if (i == 1) {
//		cout << root->data;
		return;
	}

	int columns = i - 1;
	int rows = pow(2, i - 1);
	int totalcommands = rows * columns;
	int commands[totalcommands];

	int z = 0, toggle;
	int togcount = rows / 2;
	for (z = 1; z <= totalcommands; z++) {
		if (z % togcount == 0) {
			if (toggle == 0 || z == 1) {
				toggle = 1;
			} else {
				toggle = 0;
			}
			if (togcount != 1) {
				togcount = togcount / 2;
			}
		}
		commands[z] = toggle;
		cout  << commands[z] << "\n";
	}
}

bool btree::search(int val)
{

	if (search_element(root, val) == true) {
		return true;
	} else {
		return false;
	}

	// This function must call the private function
	// search_element(node*,int) passing the root and
	// the integer value val as parameters. The function
	// must use recursion.
}

bool btree::search_element(node* p, int val)
{
	if (p != NULL) {
		if (p->data == val) {
			return true;
		} else if (val < p->data && p->left != NULL) {
			p = p->left;
			if (search_element(p, val) == false) {
				return false;
			} else {
				return true;
			}
		} else if (val > p->data && p->right != NULL) {
			p = p->right;
			if (search_element(p, val) == false) {
				return false;
			} else {
				return true;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}

	// this function receives a node and an integer as
	// parameters and searches for the value val in the
	// data of the node. The function must be such that
	// if the value is never found, it returns false.
	// If the value is found, then it returns true.
	// The function must use recursion.
}

void open_input(ifstream &IF, string IF2)      // Opening input file
{
	IF.open(IF2.c_str());
	if ( !IF.is_open() )
	{
		cout << "Cannot open input file: "
			 << IF2
			 << endl;
		exit(EXIT_FAILURE);
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
	int ch, tmp, tmp1;
	bool ans;

	// if arguments are passed, then the program assumes the
	// arguments are a list of integers and it inserts one by
	// one into the tree.
	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			if (isalpha(argv[i][0])) {
				string IFN = argv[i];
				ifstream inputfile;
				open_input(inputfile, IFN);
				while (inputfile >> tmp) {
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
		cout << " 8. Height of the Tree " << endl;
		cout << " 9. Number of Nodes " << endl;
		cout << " 10. Print by Levels " << endl;
		// ***************************************************
		// If you decide to implement the extra credit options
		// this is one place where you will need to add code
		// to provide the user with those extra functions
		// ***************************************************
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
		case 8:
			cout << endl;
			cout << " Height of the tree is: ";
			cout << my_tree.print_height();
			break;
		case 9:
			cout << endl;
			cout << " Node Counts: ";
			my_tree.print_totalnodes();
			break;
		case 10:
			cout << endl;
			cout << " Print by Levels: ";
			my_tree.print_bylevels();
			break;
			// ***************************************************
			// If you decide to implement the extra credit options
			// this is one place where you will need to add code
			// to provide the user with those extra functions
			// ***************************************************
		}
	}
}