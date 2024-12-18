#include <iostream> 
#include <string> 
 
bool isPalindrom(const std::string& word) { 
    int left = 0; 
    int right = word.length() - 1; 
    while (left < right) { 
        while (left < right && !isalnum(word[left])) { 
            ++left; 
        } 
        while (left < right && !isalnum(word[right])) { 
            --right; 
        } 
        if (tolower(word[left]) != tolower(word[right])) { 
            return false; 
        } 
 
        ++left; 
        --right; 
    } 
 
    return true; 
}