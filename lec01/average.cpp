#include <cstddef>  // for size_t
#include "gtest/gtest.h"

double average(double *array, size_t count) {
   if (count == 0) return 0.0;
   double sum {}; // Accumulate total in here
   for (size_t i {}; i < count; ++i)
      sum += *array++; // Sum array elements
   return sum / static_cast<double>(count);
}

TEST(AverageTest, ZeroLengthArray) {
   double emptyArray[1] {};
   EXPECT_EQ(average(emptyArray,0), 0);
}

TEST(AverageTest, AllIntegers) {
   double intArray[10] {1., 2., 3., 4., 5., 6., 7., 8., 9., 10.};
   EXPECT_DOUBLE_EQ(average(intArray, 10), 5.5);
}

TEST(AverageTest, LargeFloats) {
   double array[3] {1., 5., 4.};
   EXPECT_NEAR(average(array, 3), 3.33, 0.005);
}
