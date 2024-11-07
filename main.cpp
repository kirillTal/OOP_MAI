#include <iostream> 
#include <memory> 
#include "include/Pentagon.h" 
#include "include/Hexagon.h" 
#include "include/Octagon.h" 
#include "include/Point.h" 
#include "include/Array.h"  
 
using namespace Shape; 
 
int main() { 
    size_t n; 
    std::cout << "Введите количество фигур: "; 
    std::cin >> n; 
 
    auto figures = std::make_unique<std::shared_ptr<Shape::bFigure>[]>(n); 
 
    for (size_t i = 0; i < n; ++i) { 
        int type; 
        std::cout << "Выберите тип фигуры (1 - Пятиугольник, 2 - Шестиугольник, 3 - Восьмиугольник): "; 
        std::cin >> type; 
 
        if (type == 1) { 
            std::cout << "Создаем пятиугольник...\n"; 
            figures[i] = std::make_shared<Shape::Pentagon<double>>(); 
            std::cin >> *std::dynamic_pointer_cast<Shape::Pentagon<double>>(figures[i]); 
        }  
        else if (type == 2) { 
            std::cout << "Создаем шестиугольник...\n"; 
            figures[i] = std::make_shared<Shape::Hexagon<double>>(); 
            std::cin >> *std::dynamic_pointer_cast<Shape::Hexagon<double>>(figures[i]); 
        }  
        else if (type == 3) { 
            std::cout << "Создаем восьмиугольник...\n"; 
            figures[i] = std::make_shared<Shape::Octagon<double>>(); 
            std::cin >> *std::dynamic_pointer_cast<Shape::Octagon<double>>(figures[i]); 
        }  
        else { 
            std::cout << "Неверный тип фигуры, пропускаем...\n"; 
            figures[i] = nullptr; 
        } 
    } 
 
    std::cout << "\nВыводим информацию о фигурах:\n"; 
    for (size_t i = 0; i < n; ++i) { 
        if (figures[i]) { 
            std::cout << "Фигура " << i + 1 << ":\n"; 
            std::cout << *figures[i] << "\n"; 
            std::cout << "Площадь: " << figures[i]->area() << "\n"; 
        } else { 
            std::cout << "Фигура " << i + 1 << " не была инициализирована.\n"; 
        } 
    } 
 
    return 0; 
}