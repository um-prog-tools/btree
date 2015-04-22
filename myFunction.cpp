#include "myFunction.h"

bool is_integer(string text) {
    
    int len = static_cast<int>(text.length());

    for (int i = 0; i < len; i++) {
        if (!isdigit(text[i]) && !(text[i] == '-' && i == 0)) {
            return false;
        }
    }
    
    return true;
    
}