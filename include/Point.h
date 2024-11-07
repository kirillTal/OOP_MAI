#ifndef POINT_H 
#define POINT_H 
 
namespace Shape { 
 
template <typename T> 
class Point { 
public: 
    T x, y; 
 
    Point() : x(0), y(0) {} 
    Point(T x, T y) : x(x), y(y) {} 
 
    Point operator+(const Point& other) const { 
        return Point(x + other.x, y + other.y); 
    } 
 
    Point operator/(T value) const { 
        return Point(x / value, y / value); 
    } 
 
    bool operator==(const Point& other) const { 
        return x == other.x && y == other.y; 
    } 
     
    friend std::ostream& operator<<(std::ostream& os, const Point& point) { 
            os << "(" << point.x << ", " << point.y << ")"; 
            return os; 
        } 
 
        friend std::istream& operator>>(std::istream& is, Point& point) { 
            is >> point.x >> point.y; 
            return is; 
        } 
}; 
 
}  
 
#endif