#include <iostream> 
#include <initializer_list> 
#include <string> 
#include <stdexcept> 
#include <cstring> 
#include <algorithm> 
 
class Four { 
public: 
    Four();   
    Four(const size_t &n, unsigned char t = 0);  
    Four(const std::initializer_list<unsigned char> &lst);   
    Four(const std::string &str);   
    Four(const Four &other);   
    Four(Four &&other) noexcept;   
    ~Four() noexcept;   
 
    Four &operator=(const Four &other);   
    Four &operator=(Four &&other) noexcept;   
 
    Four &operator+=(const Four &other); 
    Four &operator-=(const Four &other); 
 
    friend Four operator+(const Four &a, const Four &b); 
    friend Four operator-(const Four &a, const Four &b); 
 
    friend bool operator==(const Four &a, const Four &b); 
    friend bool operator!=(const Four &a, const Four &b); 
    friend bool operator<(const Four &a, const Four &b); 
    friend bool operator>(const Four &a, const Four &b); 
    friend bool operator<=(const Four &a, const Four &b); 
    friend bool operator>=(const Four &a, const Four &b); 
 
    friend std::ostream &operator<<(std::ostream &os, const Four &num); 
 
    size_t getSize() const; 
    std::string toString() const; 
 
private: 
    bool isInvalidDigit(unsigned char c);   
    bool isValidFourInitList(const std::initializer_list<unsigned char> &lst);   
    bool isValidFourString(const std::string &str);  
 
private: 
    size_t _sz; 
    unsigned char *_arr; 
};