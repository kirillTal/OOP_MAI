#include <iostream> 
#include <string> 
#include <memory_resource> 
#include "../include/solution.cpp" 
 
struct ComplexType { 
    int id; 
    std::string name; 
    double value; 
 
    ComplexType(int id_, const std::string& name_, double value_) 
        : id(id_), name(name_), value(value_) {} 
}; 
 
void DemonstrateForwardList() { 
    std::cout << "ForwardList with int" << std::endl; 
    ForwardList<int> intList; 
    intList.PushFront(10); 
    intList.PushFront(20); 
    intList.PushFront(30); 
 
    std::cout << "List size: " << intList.Size() << std::endl; 
    while (!intList.IsEmpty()) { 
        std::cout << "Front: " << intList.Front() << std::endl; 
        intList.PopFront(); 
    } 
 
    std::cout << "\nForwardList with ComplexType" << std::endl; 
    ForwardList<ComplexType> complexList; 
    complexList.PushFront(ComplexType(1, "First", 100.0)); 
    complexList.PushFront(ComplexType(2, "Second", 200.5)); 
    complexList.PushFront(ComplexType(3, "Third", 300.75)); 
 
    std::cout << "List size: " << complexList.Size() << std::endl; 
    while (!complexList.IsEmpty()) { 
        const ComplexType& front = complexList.Front(); 
        std::cout << "Front: { id: " << front.id  
                  << ", name: " << front.name  
                  << ", value: " << front.value << " }" << std::endl; 
        complexList.PopFront(); 
    } 
 
    std::cout << "\nForwardList with custom allocator" << std::endl; 
    CustomMemoryResource memoryResource; 
    std::pmr::polymorphic_allocator<int> allocator(&memoryResource); 
    ForwardList<int, std::pmr::polymorphic_allocator<int>> allocList(allocator); 
 
    allocList.PushFront(100); 
    allocList.PushFront(200); 
    allocList.PushFront(300); 
 
    std::cout << "List size (with custom allocator): " << allocList.Size() << std::endl; 
    while (!allocList.IsEmpty()) { 
        std::cout << "Front: " << allocList.Front() << std::endl; 
        allocList.PopFront(); 
    } 
} 
 
int main() { 
    DemonstrateForwardList(); 
    return 0; 
}