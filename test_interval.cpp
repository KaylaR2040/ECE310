#include "gtest/gtest.h"
#include "Interval.h"
#include <string>

using ece309::Interval;
using ece309::find;
using ece309::filter;
using std::size_t;
using std::size;
using std::string;
using std::vector;

string intervalToString(const Interval &i) {
   return "[" + std::to_string(i.getMin()) + "," +
          std::to_string(i.getMax()) + "]";
}

string orderToString(std::partial_ordering o) {
   if (o == std::partial_ordering::equivalent) return {"EQUIVALENT"};
   if (o == std::partial_ordering::less) return {"LESS"};
   if (o == std::partial_ordering::greater) return {"GREATER"};
   return {"UNORDERED"};
}

// TEST SUITE: Basics

TEST(Basics, Constructor) {
   Interval i1{0, 100};
   EXPECT_EQ(i1.getMin(), 0);
   EXPECT_EQ(i1.getMax(), 100);

   Interval i2{-50, 42};
   EXPECT_EQ(i2.getMin(), -50);
   EXPECT_EQ(i2.getMax(), 42);

   Interval i3{-5, -1};
   EXPECT_EQ(i3.getMin(), -5);
   EXPECT_EQ(i3.getMax(), -1);
}

TEST(Basics, Width) {
   Interval objs[6] = {{10,   20},
                       {0,    5},
                       {-3,   15},
                       {-4,   0},
                       {-101, -92},
                       {10,   10}};
   size_t widths[6] = {11, 6, 19, 5, 10, 1};
   for (size_t i{0}; i < 6; ++i) {
      EXPECT_EQ(objs[i].getWidth(), widths[i]);
   }
}

TEST(Basics, Invalid) {
   Interval ii{25, 20};
   EXPECT_EQ(ii.getMin(), 0);
   EXPECT_EQ(ii.getMax(), 0);
   EXPECT_EQ(ii.getWidth(), 1);
}

TEST(Basics, Assignment) {
   Interval i1{25, 50}, i2{15, 80};
   // check values to make sure that compiler doesn't ignore
   EXPECT_EQ(i1.getMin(), 25);
   EXPECT_EQ(i1.getMax(), 50);
   i1 = i2;
   EXPECT_EQ(i1.getMin(), 15);
   EXPECT_EQ(i1.getMax(), 80);
}

// TEST SUITE: Operators

TEST(Operators, Addition) {
   EXPECT_TRUE(false);
}

TEST(Operators, Subtraction) {
   EXPECT_TRUE(false);
}

TEST(Operators, Multiplication) {
   EXPECT_TRUE(false);
}

TEST(Operators, Compare) {
   EXPECT_TRUE(false);
}

TEST(Operators, Shift) {
   EXPECT_TRUE(false);
}

TEST(MemberFunctions, Union) {
   EXPECT_TRUE(false);
}

TEST(MemberFunctions, Intersection) {
   EXPECT_TRUE(false);
}

TEST(NonMemberFunctions, FindOne) {
   vector<Interval> searchVector{{0,  10},
                                 {-3, 20},
                                 {40, 50},
                                 {40, 45},
                                 {-3, 20},
                                 {4,  5}};
   // look for first
   EXPECT_TRUE(find(searchVector, Interval{0, 10}));
   // look for last
   EXPECT_TRUE(find(searchVector, Interval{4, 5}));
   // look for mid
   EXPECT_TRUE(find(searchVector, Interval{40, 45}));
}

TEST(NonMemberFunctions, FindMultiple) {
   vector<Interval> searchVector{{0,  10},
                                 {-3, 20},
                                 {40, 50},
                                 {40, 45},
                                 {-3, 20},
                                 {4,  5}};
   // multiple matches
   EXPECT_TRUE(find(searchVector, Interval{-3, 20}));
}

TEST(NonMemberFunctions, FindNone) {
   vector<Interval> searchVector{{0,  10},
                                 {-3, 20},
                                 {40, 50},
                                 {40, 45},
                                 {-3, 20},
                                 {4,  5}};
   // not present
   EXPECT_FALSE(find(searchVector, Interval{9, 10}));
}

TEST(NonMemberFunctions, FindEmpty) {
   // empty search vector
   vector<Interval> emptyVector;
   EXPECT_FALSE(find(emptyVector, Interval{0, 10}));
}

using order = std::partial_ordering;

TEST(NonMemberFunctions, FilterEquiv) {
   vector<Interval> searchVector{{-30, -20},
                                 {0,   10},
                                 {20,  30},
                                 {-25, -15},
                                 {-10, 0},
                                 {-25, -15},
                                 {15,  25}};
   vector<Interval> outputVector;
   // for equality
   // (1) one match
   Interval test_iv{20, 30};
   outputVector = filter(searchVector, test_iv, order::equivalent);
   EXPECT_EQ(outputVector.size(), 1);
   for (auto &iv: outputVector) {
      EXPECT_TRUE(std::is_eq(iv <=> test_iv))
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
   // (2) multiple matches
   test_iv = Interval{-25, -15};
   outputVector = filter(searchVector, test_iv, order::equivalent);
   EXPECT_EQ(outputVector.size(), 2);
   for (auto &iv: outputVector) {
      EXPECT_TRUE(std::is_eq(iv <=> test_iv))
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
   // (3) no match
   test_iv = Interval{-25, 0};
   outputVector = filter(searchVector, test_iv, order::equivalent);
   EXPECT_EQ(outputVector.size(), 0);
   for (auto &iv: outputVector) {
      EXPECT_TRUE(std::is_eq(iv <=> test_iv))
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
}

TEST(NonMemberFunctions, FilterLess) {
   vector<Interval> searchVector{{-30, -20},
                                 {0,   10},
                                 {20,  30},
                                 {-25, -15},
                                 {-10, 0},
                                 {-25, -15},
                                 {15,  25}};
   vector<Interval> outputVector;

   // for less than
   // (1) one match
   Interval test_iv{-29, 0};
   outputVector = filter(searchVector, test_iv, order::less);
   EXPECT_EQ(outputVector.size(), 1);
   for (auto &iv: outputVector) {
      EXPECT_TRUE(std::is_lt(iv <=> test_iv))
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
   // (2) multiple matches
   test_iv = Interval{1, 10};
   outputVector = filter(searchVector, test_iv, order::less);
   EXPECT_EQ(outputVector.size(), 5);
   for (auto &iv: outputVector) {
      EXPECT_TRUE(std::is_lt(iv <=> test_iv))
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
   // (3) no matches
   test_iv = Interval{-50, -50};
   outputVector = filter(searchVector, test_iv, order::less);
   EXPECT_EQ(outputVector.size(), 0);
   for (auto &iv: outputVector) {
      EXPECT_TRUE(std::is_lt(iv <=> test_iv))
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
}

TEST(NonMemberFunctions, FilterGreater) {
   vector<Interval> searchVector{{-30, -20},
                                 {0,   10},
                                 {20,  30},
                                 {-25, -15},
                                 {-10, 0},
                                 {-25, -15},
                                 {15,  25}};
   vector<Interval> outputVector;

   // for greater than
   // (1) one match
   Interval test_iv{16, 29};
   outputVector = filter(searchVector, test_iv, order::greater);
   EXPECT_EQ(outputVector.size(), 1);
   for (auto &iv: outputVector) {
      EXPECT_TRUE(std::is_gt(iv <=> test_iv))
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
   // (2) multiple matches
   test_iv = Interval{0, 5};
   outputVector = filter(searchVector, test_iv, order::greater);
   EXPECT_EQ(outputVector.size(), 3);
   for (auto &iv: outputVector) {
      EXPECT_TRUE(std::is_gt(iv <=> test_iv))
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
   // (3) no matches
   test_iv = Interval{100, 100};
   outputVector = filter(searchVector, test_iv, order::greater);
   EXPECT_EQ(outputVector.size(), 0);
   for (auto &iv: outputVector) {
      EXPECT_TRUE(std::is_gt(iv <=> test_iv))
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
}

TEST(NonMemberFunctions, FilterUnordered) {
   vector<Interval> searchVector{{-30, -20},
                                 {0,   10},
                                 {20,  30},
                                 {-25, -15},
                                 {-10, 0},
                                 {-25, -15},
                                 {15,  25}};
   vector<Interval> outputVector;

   // for unordered
   // (1) one match
   Interval test_iv{2, 6};
   outputVector = filter(searchVector, test_iv, order::unordered);
   EXPECT_EQ(outputVector.size(), 1);
   for (auto &iv: outputVector) {
      EXPECT_TRUE((iv <=> test_iv) == std::partial_ordering::unordered)
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
   // (2) multiple matches
   test_iv = Interval{-50, 27};
   outputVector = filter(searchVector, test_iv, order::unordered);
   EXPECT_EQ(outputVector.size(), 6);
   for (auto &iv: outputVector) {
      EXPECT_TRUE((iv <=> test_iv) == std::partial_ordering::unordered)
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
   // (3) no matches
   test_iv = Interval{11, 11};
   outputVector = filter(searchVector, test_iv, order::unordered);
   EXPECT_EQ(outputVector.size(), 0);
   for (auto &iv: outputVector) {
      EXPECT_TRUE((iv <=> test_iv) == std::partial_ordering::unordered)
                       << "interval from vector: " << intervalToString(iv)
                       << ", test interval: " << intervalToString(test_iv)
                       << ", ordering: " << orderToString(iv <=> test_iv)
                       << std::endl;
   }
}
