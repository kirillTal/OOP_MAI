#include "../include/solution.h" 
#include "gtest/gtest.h" 
#include <iostream> 
 
TEST(FourTest, DefaultConstructor) { 
    Four num; 
    EXPECT_EQ(num.getSize(), 1);  // Проверка размера 
    EXPECT_EQ(num.toString(), "0");  // Проверка значения по умолчанию 
} 
 
// Тестирование конструктора с размером и инициализацией цифры 
TEST(FourTest, ConstructorWithSizeAndInit) { 
    Four num(5, 3); 
    EXPECT_EQ(num.getSize(), 5); 
    EXPECT_EQ(num.toString(), "33333"); 
} 
 
// Тестирование конструктора из строки 
TEST(FourTest, ConstructorWithString) { 
    Four num("123"); 
    EXPECT_EQ(num.getSize(), 3); 
    EXPECT_EQ(num.toString(), "123"); 
} 
 
// Тестирование конструктора копирования 
TEST(FourTest, CopyConstructor) { 
    Four original("321"); 
    Four copy = original; 
    EXPECT_EQ(copy.getSize(), 3); 
    EXPECT_EQ(copy.toString(), "321"); 
} 
 
// Тестирование оператора копирующего присваивания 
TEST(FourTest, CopyAssignment) { 
    Four num1("111"); 
    Four num2; 
    num2 = num1; 
    EXPECT_EQ(num2.getSize(), 3); 
    EXPECT_EQ(num2.toString(), "111"); 
} 
 
// Тестирование оператора сложения 
TEST(FourTest, AdditionOperator) { 
    Four num1("11"); 
    Four num2("02"); 
    Four result = num1 + num2; 
    EXPECT_EQ(result.toString(), "13");  // 11 + 02 = 13 
} 
 
// Тестирование оператора вычитания 
TEST(FourTest, SubtractionOperator) { 
    Four num1("13"); 
    Four num2("02"); 
    Four result = num1 - num2; 
    EXPECT_EQ(result.toString(), "11");  // 13 - 02 = 11 
} 
 
// Тестирование оператора сравнения == 
TEST(FourTest, EqualityOperator) { 
    Four num1("123"); 
    Four num2("123"); 
    EXPECT_TRUE(num1 == num2); 
    EXPECT_FALSE(num1 != num2); 
} 
 
// Тестирование оператора сравнения < 
TEST(FourTest, LessThanOperator) { 
    Four num1("122"); 
    Four num2("123"); 
    EXPECT_TRUE(num1 < num2); 
    EXPECT_FALSE(num1 > num2); 
} 
 
// Тестирование оператора вывода в поток 
TEST(FourTest, OutputOperator) { 
    Four num("123"); 
    std::stringstream ss; 
    ss << num; 
    EXPECT_EQ(ss.str(), "123"); 
} 
 
// Тестирование исключений при недопустимой строке 
TEST(FourTest, InvalidStringConstructor) { 
    EXPECT_THROW(Four("abcd"), std::invalid_argument); 
} 
 
// Тестирование исключений при вычитании, если результат отрицательный 
TEST(FourTest, InvalidSubtraction) { 
    Four num1("11"); 
    Four num2("22"); 
    EXPECT_THROW(num1 - num2, std::invalid_argument); 
} 
 
int main(int argc, char **argv) { 
  ::testing::InitGoogleTest(&argc, argv); 
  return RUN_ALL_TESTS(); 
}