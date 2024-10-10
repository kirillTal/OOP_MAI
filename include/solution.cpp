#include "solution.h" 
 
 
Four::Four() : _sz(1), _arr(new unsigned char[1]{0}) {} 
 
Four::Four(const size_t& n, unsigned char t) { 
    if (isInvalidDigit(t)) { 
        throw std::invalid_argument("Недопустимая четвертичная цифра."); 
    } 
    _sz = n; 
    _arr = new unsigned char[n]; 
    std::memset(_arr, t, n); 
} 
 
Four::Four(const std::initializer_list<unsigned char>& lst) { 
    if (!isValidFourInitList(lst)) { 
        throw std::invalid_argument("Список содержит недопустимые цифры."); 
    } 
    _sz = lst.size(); 
    _arr = new unsigned char[_sz]; 
    std::copy(lst.begin(), lst.end(), _arr); 
} 
 
Four::Four(const std::string& str) { 
    if (!isValidFourString(str)) { 
        throw std::invalid_argument("Строка содержит недопустимые символы."); 
    } 
    _sz = str.size(); 
    _arr = new unsigned char[_sz]; 
    for (size_t i = 0; i < _sz; ++i) { 
        _arr[i] = str[_sz - 1 - i] - '0'; 
        std::cout << _arr[i]; 
    } 
} 
 
Four::Four(const Four& other) : _sz(other._sz), _arr(new unsigned char[other._sz]) { 
    std::memcpy(_arr, other._arr, _sz); 
} 
 
Four::Four(Four&& other) noexcept : _sz(other._sz), _arr(other._arr) { 
    other._sz = 0; 
    other._arr = nullptr; 
} 
 
Four::~Four() noexcept { 
    delete[] _arr; 
} 
 
Four& Four::operator=(const Four& other) { 
    if (this != &other) { 
        delete[] _arr; 
        _sz = other._sz; 
        _arr = new unsigned char[_sz]; 
        std::memcpy(_arr, other._arr, _sz); 
    } 
    return *this; 
} 
 
Four& Four::operator=(Four&& other) noexcept { 
    if (this != &other) { 
        delete[] _arr; 
        _sz = other._sz; 
        _arr = other._arr; 
        other._sz = 0; 
        other._arr = nullptr; 
    } 
    return *this; 
} 
 
Four& Four::operator+=(const Four& other) { 
    *this = *this + other; 
    return *this; 
} 
 
Four& Four::operator-=(const Four& other) { 
    *this = *this - other; 
    return *this; 
} 
 
Four operator+(const Four& a, const Four& b) { 
    size_t max_sz = std::max(a._sz, b._sz); 
    unsigned char *result = new unsigned char[max_sz + 1]{0}; 
     
    unsigned char carry = 0; 
    unsigned char digit_sum = 0; 
    for (size_t i = 0; i < max_sz || carry; ++i) { 
        digit_sum = carry; 
        if (i < a._sz) digit_sum += a._arr[i]; 
        if (i < b._sz) digit_sum += b._arr[i]; 
         
        result[i] = digit_sum % 4; 
        carry = digit_sum / 4; 
    } 
     
    size_t result_sz = (carry > 0) ? max_sz + 1 : max_sz; 
    Four sum; 
    sum._sz = result_sz; 
    sum._arr = result; 
     
    return sum; 
} 
 
Four operator-(const Four& a, const Four& b) { 
    if (a < b) { 
        throw std::invalid_argument("Result would be negative."); 
    } 
 
    size_t maxSize = std::max(a._sz, b._sz); 
    unsigned char *resultArr = new unsigned char[maxSize]{}; 
    int borrow = 0; 
    int aDigit, bDigit, diff = 0; 
 
    for (size_t i = 0; i < maxSize; ++i) { 
        aDigit = (i < a._sz) ? a._arr[i] : 0;  
        bDigit = (i < b._sz) ? b._arr[i] : 0;  
 
        diff = aDigit - bDigit - borrow; 
 
        if (diff < 0) { 
            diff += 4; 
            borrow = 1; 
        } else { 
            borrow = 0; 
        } 
 
        resultArr[i] = static_cast<unsigned char>(diff); 
    } 
 
    Four result(maxSize); 
    std::memcpy(result._arr, resultArr, maxSize); 
    delete[] resultArr; 
    return result; 
} 
 
bool operator==(const Four& a, const Four& b) { 
    if (a._sz != b._sz) return false; 
    return std::memcmp(a._arr, b._arr, a._sz) == 0; 
} 
 
bool operator!=(const Four& a, const Four& b) { 
    return !(a == b); 
} 
 
bool operator<(const Four& a, const Four& b) { 
    if (a._sz != b._sz) return a._sz < b._sz; 
    for (size_t i = a._sz; i > 0; --i) { 
        if (a._arr[i - 1] != b._arr[i - 1]) return a._arr[i - 1] < b._arr[i - 1]; 
    } 
    return false; 
} 
 
bool operator>(const Four& a, const Four& b) { 
    return b < a; 
} 
 
bool operator<=(const Four& a, const Four& b) { 
    return !(a > b); 
} 
 
bool operator>=(const Four& a, const Four& b) { 
    return !(a < b); 
} 
 
std::ostream& operator<<(std::ostream& os, const Four& num) { 
    for (size_t i = num._sz; i > 0; --i) { 
        os << static_cast<int>(num._arr[i - 1]); 
    } 
    return os; 
} 
 
size_t Four::getSize() const { 
    return _sz; 
} 
 
std::string Four::toString() const { 
    std::string str; 
    for (size_t i = _sz; i > 0; --i) { 
        str += (static_cast<char>(_arr[i - 1] + '0')); 
    } 
    return str; 
} 
 
bool Four::isInvalidDigit(unsigned char c) { 
    return c > 3; 
} 
 
bool Four::isValidFourInitList(const std::initializer_list<unsigned char>& lst) { 
    for (unsigned char c : lst) { 
        if (isInvalidDigit(c)) return false; 
    } 
    return true; 
} 
 
bool Four::isValidFourString(const std::string& str) { 
    for (char c : str) { 
        if (c < '0' || c > '3') return false; 
    } 
    return true; 
}