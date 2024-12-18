#include <string> 
#include "gtest/gtest.h" 
#include "../include/solution.h" 
 
 
TEST(isPalindromTest1, Test1) { 
   std::string input = "Abaaba"; 
   EXPECT_EQ(isPalindrom(input), true); 
} 
 
TEST(isPalindromTest2, Test2) { 
   std::string input = "abacabaa"; 
   EXPECT_EQ(isPalindrom(input), false); 
} 
 
TEST(isPalindromTest3, Test3) { 
   std::string input = "hello world!"; 
   EXPECT_EQ(isPalindrom(input), false); 
} 
 
int main(int argc, char **argv) { 
   ::testing::InitGoogleTest(&argc, argv); 
   return RUN_ALL_TESTS(); 
}