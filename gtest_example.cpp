#include "gtest/gtest.h"

// computes n-factorial (n!)
// if n is negative, n! is defined to be 1
int factorial(int n) {
      int result = 1;
      for (int i = 1; i <= n; i++) {
         result *= i;
      }

      return result;
}

// Tests factorial of 0.
TEST(FactorialTest, HandlesZeroInput) {
   EXPECT_EQ(factorial(0), 1);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput) {
   EXPECT_EQ(factorial(1), 1);
   EXPECT_EQ(factorial(2), 2);
   EXPECT_EQ(factorial(3), 6);
   EXPECT_EQ(factorial(8), 40320);
}