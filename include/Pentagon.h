#ifndef PENTAGON_H 
#define PENTAGON_H 
 
#include "Figure.h" 
#include <cmath> 
#include <memory> 
#include <iostream> 
#include <stdexcept> 
 
namespace Shape { 
 
template <typename T> 
class Pentagon : public Figure<T, 5> { 
private: 
    using Figure<T, 5>::vertices;  
 
public: 
 
    Pentagon() : Figure<T, 5>({{0, 0}, {1, 0}, {1.5, 1}, {1, 2}, {0, 1}}) {} 
 
  
    Pentagon(std::initializer_list<Point<T>> points) : Figure<T, 5>(points) { 
        if (points.size() != 5) { 
            throw std::invalid_argument("Pentagon должен иметь ровно 5 вершин."); 
        } 
    } 
 
 
    Pentagon(const Point<T>& center, T radius) { 
        double pi = std::acos(-1); 
        for (size_t i = 0; i < 5; ++i) { 
            double angle = i * 2 * pi / 5; 
            vertices[i] = std::make_unique<Point<T>>( 
                center.x + radius * std::cos(angle), 
                center.y + radius * std::sin(angle) 
            ); 
        } 
    } 
 
 
    Pentagon(const Pentagon& other) : Figure<T, 5>(other) {} 
 
 
    Pentagon(Pentagon&& other) noexcept : Figure<T, 5>(std::move(other)) {} 
 
 
    Pentagon& operator=(const Pentagon& other) { 
        if (this != &other) { 
            Figure<T, 5>::operator=(other); 
        } 
        return *this; 
    } 
 
    Pentagon& operator=(Pentagon&& other) noexcept { 
        if (this != &other) { 
            Figure<T, 5>::operator=(std::move(other)); 
        } 
        return *this; 
    } 
 
 
    bool operator==(const Pentagon& other) const { 
        for (size_t i = 0; i < 5; ++i) { 
            if (*this->vertices[i] != *other.vertices[i]) { 
                return false; 
            } 
        } 
        return true; 
    } 
 
 
    double area() const override { 
        double area = 0; 
        for (size_t i = 0; i < 5; ++i) { 
            const auto& [x1, y1] = *vertices[i]; 
            const auto& [x2, y2] = *vertices[(i + 1) % 5]; 
            area += static_cast<double>(x1) * y2 - static_cast<double>(x2) * y1; 
        } 
        return std::abs(area) / 2; 
    } 
 
 
    friend std::istream& operator>>(std::istream& is, Pentagon& pentagon) { 
        std::cout << "Введите 5 точек для пятиугольника (x y):\n"; 
        for (auto& vertex : pentagon.vertices) { 
            T x, y; 
            is >> x >> y; 
            vertex = std::make_unique<Point<T>>(x, y); 
        } 
        return is; 
    } 
 
    friend std::ostream& operator<<(std::ostream& os, const Pentagon& pentagon) { 
        os << "Пятиугольник с вершинами:\n"; 
        for (const auto& vertex : pentagon.vertices) { 
            os << *vertex << " "; 
        } 
        return os; 
    } 
}; 
 
}  
 
#endif