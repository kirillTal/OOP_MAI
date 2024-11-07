#ifndef HEXAGON_H 
#define HEXAGON_H 
 
#include "Figure.h" 
#include <cmath> 
#include <memory> 
#include <iostream> 
#include <stdexcept> 
 
namespace Shape { 
 
template <typename T> 
class Hexagon : public Figure<T, 6> { 
private: 
    using Figure<T, 6>::vertices; 
 
public: 
 
    Hexagon() : Figure<T, 6>({{0, 0}, {1, 0}, {1.5, 1}, {1, 2}, {0, 2}, {-0.5, 1}}) {} 
 
 
    Hexagon(std::initializer_list<Point<T>> points) : Figure<T, 6>(points) { 
        if (points.size() != 6) { 
            throw std::invalid_argument("Hexagon должен иметь ровно 6 вершин."); 
        } 
    } 
 
 
    Hexagon(const Point<T>& center, T radius) { 
        double pi = std::acos(-1); 
        for (size_t i = 0; i < 6; ++i) { 
            double angle = i * 2 * pi / 6; 
            vertices[i] = std::make_unique<Point<T>>( 
                center.x + radius * std::cos(angle), 
                center.y + radius * std::sin(angle) 
            ); 
        } 
    } 
 
 
    Hexagon(const Hexagon& other) : Figure<T, 6>(other) {} 
 
 
    Hexagon(Hexagon&& other) noexcept : Figure<T, 6>(std::move(other)) {} 
 
 
    Hexagon& operator=(const Hexagon& other) { 
        if (this != &other) { 
            Figure<T, 6>::operator=(other); 
        } 
        return *this; 
    } 
 
    Hexagon& operator=(Hexagon&& other) noexcept { 
        if (this != &other) { 
            Figure<T, 6>::operator=(std::move(other)); 
        } 
        return *this; 
    } 
 
 
    bool operator==(const Hexagon& other) const { 
        for (size_t i = 0; i < 6; ++i) { 
            if (*this->vertices[i] != *other.vertices[i]) { 
                return false; 
            } 
        } 
        return true; 
    } 
 
 
    double area() const override { 
        double area = 0; 
        for (size_t i = 0; i < 6; ++i) { 
            const auto& [x1, y1] = *vertices[i]; 
            const auto& [x2, y2] = *vertices[(i + 1) % 6]; 
            area += static_cast<double>(x1) * y2 - static_cast<double>(x2) * y1; 
        } 
        return std::abs(area) / 2; 
    } 
 
 
    friend std::istream& operator>>(std::istream& is, Hexagon& hexagon) { 
        std::cout << "Введите 6 точек для шестиугольника (x y):\n"; 
        for (auto& vertex : hexagon.vertices) { 
            T x, y; 
            is >> x >> y; 
            vertex = std::make_unique<Point<T>>(x, y); 
        } 
        return is; 
    } 
 
 
    friend std::ostream& operator<<(std::ostream& os, const Hexagon& hexagon) { 
        os << "Шестиугольник с вершинами:\n"; 
        for (const auto& vertex : hexagon.vertices) { 
            os << *vertex << " "; 
        } 
        return os; 
    } 
}; 
 
}  
 
#endif