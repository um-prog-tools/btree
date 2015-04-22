#include <iostream>
#include <cstdlib>
#include "btree.h"
#include "myFunction.h"

using namespace std;

int main(int argc, char* argv[]) {
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
    string tmp_str;
    bool ans;

    // if arguments are passed, then the program assumes the
    // arguments are a list of integers and it inserts one by
    // one into the tree. If an argument is not an integer, I
    // assume it is a file contains a sequence of integers
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
                    while (input_file >> tmp_str) {
                        if (is_integer(tmp_str)) {
                            tmp = atoi(tmp_str.c_str());
                            my_tree.insert(tmp);
                        } else {
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