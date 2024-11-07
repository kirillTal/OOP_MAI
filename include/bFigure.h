#ifndef BFIGURE_H 
#define BFIGURE_H 
 
#include <iostream> 
 
namespace Shape { 
 
class bFigure { 
public: 
    virtual ~bFigure() = default; 
 
    virtual double area() const = 0;             
    virtual void print(std::ostream& out) const = 0;  
}; 
 
inline std::ostream& operator<<(std::ostream& os, const bFigure& figure) { 
    figure.print(os); 
    return os; 
} 
 
} 
 
#endif