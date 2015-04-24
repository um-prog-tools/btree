/**
 * @short H9 Program
 * To Translate Knowledge about Trees into a tangible Code;
 * And to Learn How to Interact with a main Repository with No Push Permission.
 * @author Shima Azizzadeh-Roodpish
 * 22 April 2015
 * No Copyright
 * Github account: https://github.com/Shima63/btree.git
 * @return 0 on Success, 1 on Failure
 */
 
/// External Libraries
#include <iostream>
#include <cstdlib>

/// Additional Libraries
#include <queue>

using namespace std;

class btree ///< Brief description after the member
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
    void print_reverse_order_traversal();
    void print_Height();
    
    bool search(int);

private:

    void inorder(node*);
    void preorder(node*);
    void postorder(node*);
    void reverse_order_traversal(node*);
    int Height(node*);

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
    if ( root == NULL ) 
    { 
        return true;
    }
    else
    {
        return false;
    }         
}

void btree::insert(int d)
{
    // this function must insert the value d in the tree

    node *temp, *parent;
    
    // first of all, check if d already exists in the tree
    // you can do this by calling to the search(int) function
    
    bool check = btree::search(d);

    if ( !check )
    
    // if d is not in the tree already, create a new node with data equal d
     
    {
        if ( btree::isEmpty() )
        
        // if the tree is empty, set the root to the new node

        {
            root = new node;
            root->data = d;
            root->left = NULL;
            root->right = NULL;
            temp = root;
        }
        else
        
        // if the tree is not empty, look for the right place where to insert d
        // in order to do this, you may need to keep track of the potential
        // parent node to which the new node will be attached as a child
        
        {
            temp=root;
            while (temp!=NULL) {
                if ( d < temp->data )
                {
                    parent = temp;
                    temp=temp->left;
                }
                else if ( d > temp->data )
                {
                    parent =temp;
                    temp=temp->right;
                }               
            }   
            node *newNode = new node;
            newNode->data = d;
            newNode->left = NULL;
            newNode->right = NULL;

            //Now insert the new node BELOW parent
            if(d <= parent->data)
            {
                parent->left = newNode;
            }   
            else
            {
                parent->right = newNode;
            }    
        }
    }
    else
    {
        return;
    }    
}

void btree::remove(int d)
{
    // this function must remove the node that has the value d
    node *temp1, *temp2;
    bool check = false, found = false;
    
    if ( btree::isEmpty() ) // first of all, check if the tree is empty
    {
        return;
    }
    else
    // if it is not, then locate the element with the value
    {
        check = btree::search(d);
        if ( !check ) 
        {
            cout << " There Is No Element Equal to That";
        }       
        else
        {
            temp1 = root;
            temp2 = root;
            while ( ( temp1 != NULL ) && ( !found ) )
            {
                if ( temp1->data == d )
                {
                    found = true;
                }
                else
                {
                    temp2 = temp1;
                    if ( temp1->data > d )
                    {
                        temp1 = temp1->left;
                    }
                    else
                    {
                        temp1 = temp1->right;
                    }
                }
            }
            // once you know the location, that is, you have the pointer to the node
            // with the value you want to eliminate, you will have three cases:
            // make sure you can handle all three cases. 
            if ( found )
            {
                if ( temp1 == root )
                {
                    node *current, *trailCurrent, *temp;

	                if (root->left == NULL && root->right == NULL)
	                {
		                temp = root;
		                root = NULL;
		                delete temp;
	                }
	                else if (root->left == NULL)
	                {
		                temp = root;
		                root = temp->right;
		                delete temp;
	                }
	               else if (root->right == NULL)
	               {
		                temp = root;
		                root = temp->left;
		                delete temp;
	               }
	               else
	               {
		                current = root->left;
		                trailCurrent = NULL;

		                while (current->right != NULL)
		                {
			                trailCurrent = current;
			                current = current->right;
		                }

		                root->data = current->data;

		                if (trailCurrent == NULL)
		                {
			                root->left = current->left;
			            }    
		                else
		                {
			                trailCurrent->right = current->left;
			            }    

		                delete current;
		            }    
                }
                else if ( temp2->data > d)
                {
                    node *current, *trailCurrent, *temp;

	                if (temp2->left->left == NULL && temp2->left->right == NULL)
	                {
		                temp = temp2->left;
		                temp2->left = NULL;
		                delete temp;
	                }
	                else if (temp2->left->left == NULL)
	                {
		                temp = temp2->left;
		                temp2->left = temp->right;
		                delete temp;
	                }
	               else if (temp2->left->right == NULL)
	               {
		                temp = temp2->left;
		                temp2->left = temp->left;
		                delete temp;
	               }
	               else
	               {
		                current = temp2->left->left;
		                trailCurrent = NULL;

		                while (current->right != NULL)
		                {
			                trailCurrent = current;
			                current = current->right;
		                }

		                temp2->left->data = current->data;

		                if (trailCurrent == NULL) 
		                {
			                temp2->left->left = current->left;
			            }    
		                else
		                {
			                trailCurrent->right = current->left;
			            }    

		                delete current;
		            }    
                    }
                else
                {
                    node *current, *trailCurrent, *temp;

	                if (temp2->right->left == NULL && temp2->right->right == NULL)
	                {
		                temp = temp2->right;
		                temp2->right = NULL;
		                delete temp;
	                }
	                else if (temp2->right->left == NULL)
	                {
		                temp = temp2->right;
		                temp2->right = temp->right;
		                delete temp;
	                }
	               else if (temp2->right->right == NULL)
	               {
		                temp = temp2->right;
		                temp2->right = temp->left;
		                delete temp;
	               }
	               else
	               {
		                current = temp2->right->left;
		                trailCurrent = NULL;

		                while (current->right != NULL)
		                {
			                trailCurrent = current;
			                current = current->right;
		                }

		                temp2->right->data = current->data;

		                if (trailCurrent == NULL)
		                {
			                temp2->right->left = current->left;
			            }    
		                else
		                {
			                trailCurrent->right = current->left;
			            }    

		                delete current;
		            }                    }
            }
        }               
    }
}

void btree::print_inorder()
{
    // this function must call the private inorder(node*)
    // function passing the root as the parameter
    btree::inorder(root);
    return;
}

void btree::inorder(node* p)
{
    // This function receives a node as parameter
    // then traverses the tree following the in-order
    // sequence. Every time it visits a node it will
    // print the data in the node to cout leaving a blank
    // space to separate from the next/previous value.
    // The function must use recursion.
    if ( p != NULL )
    {  // (Otherwise, there's nothing to print.)
        inorder( p->left );    // Print items in left subtree.
        cout << p->data << " ";     // Print the Value.
        inorder( p->right );   // Print items in right subtree.
    }
}

void btree::print_preorder()
{
    // This function must call the private pre-order(node*)
    // function passing the root as the parameter
    btree::preorder(root);
    return;
}

void btree::preorder(node* p)
{
    // This function receives a node as parameter
    // then traverses the tree following the pre-order
    // sequence. Every time it visits a node it will
    // print the data in the node to cout leaving a blank
    // space to separate from the next/previous value.
    // The function must use recursion.
    if ( p != NULL )
    {  // (Otherwise, there's nothing to print.)
        cout << p->data << " ";      // Print the value.
        preorder( p->left );    // Print items in left subtree.
        preorder( p->right );   // Print items in right subtree.
    }
}

void btree::print_postorder()
{
    // This function must call the private post-order(node*)
    // function passing the root as the parameter
    btree::postorder(root);
    return;
}

void btree::postorder(node* p)
{
    // This function receives a node as parameter
    // then traverses the tree following the post-order
    // sequence. Every time it visits a node it will
    // print the data in the node to cout leaving a blank
    // space to separate from the next/previous value.
    // The function must use recursion.
    if ( p != NULL )
    {  // (Otherwise, there's nothing to print.)
        postorder( p->left );    // Print items in left subtree.
        postorder( p->right );   // Print items in right subtree.
        cout << p->data << " ";       // Print the value.
    }
}

void btree::print_reverse_order_traversal()
{
    // this function must call the private reverse order(node*)
    // function passing the root as the parameter
    btree::reverse_order_traversal(root);
    return;
}

void btree::reverse_order_traversal(node* p)
{
    if ( p != NULL )
    {  // (Otherwise, there's nothing to print.)
        reverse_order_traversal( p->right );    // Print items in right subtree.
        cout << p->data << " ";     // Print the Value.
        reverse_order_traversal( p->left );   // Print items in left subtree.
    }
}

bool btree::search(int val)
{
    // This function must call the private function
    // search_element(node*,int) passing the root and
    // the integer value val as parameters. The function
    // must use recursion.
    if ( btree::search_element(root, val) )
    {
        return true;
    }
    else
    {
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
    if ( p == NULL )
    {
        // Tree is empty, so it certainly doesn't contain item.
        return false;
    }
    else if ( val == p->data )
    {
        // the item has been found in the root node.
        return true;
    }
    else if ( val < p->data )
    {
        // If the item occurs, it must be in the left subtree.
        return search_element( p->left, val );
    }
    else
    {
    // If the item occurs, it must be in the right subtree.
    return search_element( p->right, val );
    }
}

void btree::print_Height()
{
    // this function must call the private Height(node*)
    // function passing the root as the parameter
    int height = btree::Height(root);
    cout << height << " ";     // Print the height.
    return;
}

int btree::Height(node* p)
{
    // This function receives a node as parameter
    // then print the Height of that node
    // Base Case
    if (root == NULL)
    {
        return 0;
    }    
 
    // Create an empty queue for LEVEL ORDER tarversal
    queue<node *> q;
 
    // Enqueue Root and initialize height
    q.push(root);
    int height = 0;
 
    while (1)
    {
        // nodeCount (queue size) indicates NUMBER of nodes
        // at current lelvel.
        int nodeCount = q.size();
        if (nodeCount == 0)
            return height;
 
        height++;
 
        // Dequeue all nodes of current level and Enqueue all
        // nodes of next level
        while (nodeCount > 0)
        {
            node *node = q.front();
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
            nodeCount--;
        }
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
        cout << " 5. Removal "<< endl;
        cout << " 6. Search "<< endl;
        // ***************************************************
        // If you decide to implement the extra credit options
        // this is one place where you will need to add code
        // to provide the user with those extra functions
        // ***************************************************
        cout << " 7. Reverse-Order Traversal " << endl;
        cout << " 8. Height of the tree " << endl;
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
        case 7:
            cout << endl;
            cout << " Reverse-Order Traversal: " << endl << endl;
            my_tree.print_reverse_order_traversal();
            break;
        case 8:
            cout << endl;
            cout << " Height of the tree: " << endl << endl;
            my_tree.print_Height();
            break;    
        }
    }
}
