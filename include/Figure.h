#ifndef FIGURE_H 
#define FIGURE_H 
 
#include "bFigure.h" 
#include "Point.h" 
#include <memory> 
#include <array> 
#include <initializer_list> 
#include <cmath> 
#include <stdexcept> 
 
namespace Shape { 
 
template <typename T, size_t PntCnt> 
class Figure : public bFigure { 
protected: 
    std::array<std::unique_ptr<Point<T>>, PntCnt> vertices; 
 
public: 
    Figure() { 
        for (size_t i = 0; i < PntCnt; ++i) { 
            vertices[i] = std::make_unique<Point<T>>(0, i * i);  
        } 
    } 
 
    Figure(std::initializer_list<Point<T>> points) { 
        if (points.size() != PntCnt) { 
            throw std::invalid_argument("Incorrect number of points provided"); 
        } 
 
        auto it = points.begin(); 
        for (size_t i = 0; i < PntCnt; ++i, ++it) { 
            vertices[i] = std::make_unique<Point<T>>(it->x, it->y); 
        } 
    } 
 
    Figure(const Figure<T, PntCnt>& other) { 
        for (size_t i = 0; i < PntCnt; ++i) { 
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]); 
        } 
    } 
 
    Figure& operator=(const Figure<T, PntCnt>& other) { 
        if (this == &other) return *this; 
 
        for (size_t i = 0; i < PntCnt; ++i) { 
            vertices[i] = std::make_unique<Point<T>>(*other.vertices[i]); 
        } 
 
        return *this; 
    } 
 
    double area() const override { 
        double result = 0; 
        for (size_t i = 0; i < PntCnt; ++i) { 
            const Point<T>& p1 = *vertices[i]; 
            const Point<T>& p2 = *vertices[(i + 1) % PntCnt]; 
            result += p1.x * p2.y - p2.x * p1.y; 
        } 
        return std::abs(result) / 2.0; 
    } 
 
    Point<T> center() const { 
        Point<T> sum(0, 0); 
        for (size_t i = 0; i < PntCnt; ++i) { 
            sum = sum + *vertices[i]; 
        } 
        return sum / static_cast<T>(PntCnt); 
    } 
 
    void print(std::ostream& out) const override { 
        out << "Vertices: "; 
        for (size_t i = 0; i < PntCnt; ++i) { 
            out << "(" << vertices[i]->x << ", " << vertices[i]->y << ") "; 
        } 
        out << "\n"; 
    } 
}; 
 
}  
 
#endif