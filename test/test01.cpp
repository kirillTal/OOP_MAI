#include <gtest/gtest.h> 
#include "../include/Pentagon.h" 
#include "../include/Hexagon.h" 
#include "../include/Octagon.h" 
#include "../include/Array.h" 
 
 
TEST(ArrayTest, PushBackAndAccess) { 
    Shape::Array<std::shared_ptr<Shape::bFigure>> shapes; 
 
 
    shapes.push_back(std::make_shared<Shape::Pentagon<double>>(Shape::Point<double>{0.0, 0.0}, 1.0)); 
    shapes.push_back(std::make_shared<Shape::Hexagon<double>>(Shape::Point<double>{0.0, 0.0}, 2.0)); 
 
 
    EXPECT_EQ(shapes.size(), 2); 
 
 
    EXPECT_NEAR(shapes[0]->area(), 2.377, 1e-3);  
    EXPECT_NEAR(shapes[1]->area(), 10.392, 1e-3);  
} 
 
 
TEST(ArrayTest, RemoveAt) { 
    Shape::Array<std::shared_ptr<Shape::bFigure>> shapes; 
 
    shapes.push_back(std::make_shared<Shape::Octagon<double>>(Shape::Point<double>{0.0, 0.0}, 1.0)); 
    shapes.push_back(std::make_shared<Shape::Pentagon<double>>(Shape::Point<double>{0.0, 0.0}, 1.0)); 
 
 
    shapes.remove_at(0); 
 
    EXPECT_EQ(shapes.size(), 1); 
 
 
    EXPECT_NEAR(shapes[0]->area(), 2.377, 1e-3);  
} 
 
 
TEST(ArrayTest, CopyAndMove) { 
    Shape::Array<std::shared_ptr<Shape::bFigure>> shapes; 
    shapes.push_back(std::make_shared<Shape::Hexagon<double>>(Shape::Point<double>{0.0, 0.0}, 2.0)); 
 
 
    Shape::Array<std::shared_ptr<Shape::bFigure>> copy = shapes; 
    EXPECT_EQ(copy.size(), shapes.size()); 
    EXPECT_NEAR(copy[0]->area(), shapes[0]->area(), 1e-3); 
 
 
    Shape::Array<std::shared_ptr<Shape::bFigure>> moved = std::move(shapes); 
    EXPECT_EQ(moved.size(), 1); 
    EXPECT_EQ(shapes.size(), 0);  
    EXPECT_NEAR(moved[0]->area(), 10.392, 1e-3);  
} 
 
 
TEST(ArrayTest, TotalArea) { 
    Shape::Array<std::shared_ptr<Shape::bFigure>> shapes; 
 
 
    shapes.push_back(std::make_shared<Shape::Pentagon<double>>(Shape::Point<double>{0.0, 0.0}, 1.0)); 
    shapes.push_back(std::make_shared<Shape::Octagon<double>>(Shape::Point<double>{0.0, 0.0}, 1.0)); 
 
 
    EXPECT_NEAR(shapes.TotalArea(), 5.206, 1e-3);  
} 
 
 
int main(int argc, char **argv) { 
    testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}