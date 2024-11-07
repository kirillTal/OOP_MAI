#ifndef OCTAGON_H 
#define OCTAGON_H 
 
#include "Figure.h" 
#include <cmath> 
#include <memory> 
#include <iostream> 
#include <stdexcept> 
 
namespace Shape { 
 
template <typename T> 
class Octagon : public Figure<T, 8> { 
private: 
    using Figure<T, 8>::vertices; 
 
public: 
 
    Octagon() : Figure<T, 8>({{0, 0}, {1, 0}, {1.5, 0.5}, {1.5, 1.5}, {1, 2}, {0, 2}, {-0.5, 1.5}, {-0.5, 0.5}}) {} 
 
 
    Octagon(std::initializer_list<Point<T>> points) : Figure<T, 8>(points) { 
        if (points.size() != 8) { 
            throw std::invalid_argument("Octagon должен иметь ровно 8 вершин."); 
        } 
    } 
 
 
    Octagon(const Point<T>& center, T radius) { 
        double pi = std::acos(-1); 
        for (size_t i = 0; i < 8; ++i) { 
            double angle = i * 2 * pi / 8; 
            vertices[i] = std::make_unique<Point<T>>( 
                center.x + radius * std::cos(angle), 
                center.y + radius * std::sin(angle) 
            ); 
        } 
    } 
 
 
    Octagon(const Octagon& other) : Figure<T, 8>(other) {} 
 
 
    Octagon(Octagon&& other) noexcept : Figure<T, 8>(std::move(other)) {} 
 
 
    Octagon& operator=(const Octagon& other) { 
        if (this != &other) { 
            Figure<T, 8>::operator=(other); 
        } 
        return *this; 
    } 
 
 
    Octagon& operator=(Octagon&& other) noexcept { 
        if (this != &other) { 
            Figure<T, 8>::operator=(std::move(other)); 
        } 
        return *this; 
    } 
 
 
    bool operator==(const Octagon& other) const { 
        for (size_t i = 0; i < 8; ++i) { 
            if (*this->vertices[i] != *other.vertices[i]) { 
                return false; 
            } 
        } 
        return true; 
    } 
 
 
    double area() const override { 
        double area = 0; 
        for (size_t i = 0; i < 8; ++i) { 
            const auto& [x1, y1] = *vertices[i]; 
            const auto& [x2, y2] = *vertices[(i + 1) % 8]; 
            area += static_cast<double>(x1) * y2 - static_cast<double>(x2) * y1; 
        } 
        return std::abs(area) / 2; 
    } 
 
 
    friend std::istream& operator>>(std::istream& is, Octagon& octagon) { 
        std::cout << "Введите 8 точек для восьмиугольника (x y):\n"; 
        for (auto& vertex : octagon.vertices) { 
            T x, y; 
            is >> x >> y; 
            vertex = std::make_unique<Point<T>>(x, y); 
        } 
        return is; 
    } 
 
 
    friend std::ostream& operator<<(std::ostream& os, const Octagon& octagon) { 
        os << "Восьмиугольник с вершинами:\n"; 
        for (const auto& vertex : octagon.vertices) { 
            os << *vertex << " "; 
        } 
        return os; 
    } 
}; 
 
}  
 
#endif