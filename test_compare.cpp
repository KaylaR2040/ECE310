#include "gtest/gtest.h"
#include "hw1.h"
#include <compare>
#include <array>
#include <string>
//#include <format>

using strong = std::strong_ordering;
using std::array;
using std::string;

string dateToString(const CalendarDate& date) {
   return date.month + " " + std::to_string(date.day) + ", "
          + std::to_string(date.year);
   //return std::format("{} {}, {}", date.month, date.day, date.year);
}

TEST(CompareDates, DatesEqual) {
   const CalendarDate days[4] { {2025, "January", 12},
                                {2025, "January", 12},
                                {44,   "March",   15},
                                {44,   "March",   15}};
   EXPECT_EQ(days[0] <=> days[1], strong::equal)
      << "day1: " << dateToString(days[0])
      << ", day2: " << dateToString(days[1]);
   EXPECT_EQ(days[2] <=> days[3], strong::equal)
      << "day1: " << dateToString(days[2])
      << ", day2: " << dateToString(days[3]);
}

TEST(CompareDates, DateLess) {
   unsigned years[] { 1880, 1900 };
   const string months[] { "February", "June" };
   unsigned days[] { 5, 14 };
   // year is less
   CalendarDate day1 { years[0], months[1], days[1]};
   CalendarDate day2 { years[1], months[0], days[0]};
   EXPECT_EQ(day1 <=> day2, strong::less)
      << "day1: " << dateToString(day1)
      << ", day2: " << dateToString(day2);
   // year is equal, month is less
   day2.year = years[0];
   day1.month = months[0];
   day2.month = months[1];
   EXPECT_EQ(day1 <=> day2, strong::less)
      << "day1: " << dateToString(day1)
      << ", day2: " << dateToString(day2);
   // year and month are equal, day is less
   day1.month = months[1];
   day1.day = days[0];
   day2.day = days[1];
   EXPECT_EQ(day1 <=> day2, strong::less)
      << "day1: " << dateToString(day1)
      << ", day2: " << dateToString(day2);
}

TEST(CompareDates, DateGreater) {
   unsigned years[] { 2030, 2025 };
   const string months[] { "December", "November" };
   unsigned days[] { 20, 2 };
   // year is less
   CalendarDate day1 { years[0], months[1], days[1]};
   CalendarDate day2 { years[1], months[0], days[0]};
   EXPECT_EQ(day1 <=> day2, strong::greater)
                    << "day1: " << dateToString(day1)
                    << ", day2: " << dateToString(day2);
   // year is equal, month is less
   day2.year = years[0];
   day1.month = months[0];
   day2.month = months[1];
   EXPECT_EQ(day1 <=> day2, strong::greater)
                    << "day1: " << dateToString(day1)
                    << ", day2: " << dateToString(day2);
   // year and month are equal, day is less
   day1.month = months[1];
   day1.day = days[0];
   day2.day = days[1];
   EXPECT_EQ(day1 <=> day2, strong::greater)
                    << "day1: " << dateToString(day1)
                    << ", day2: " << dateToString(day2);
}