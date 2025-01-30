#ifndef SPR25_HW1_H
#define SPR25_HW1_H

#include <string>
#include <compare>
#include <vector>

// PROBLEM #1

// replace all instances of target char, up to limit, with replacement char
void replaceChar(std::string& str, char target, char replace=' ', size_t limit=0);

// replace all instances of character in the selection string,
// up to limit, with the replacement character
void replaceChar(std::string& str, const std::string_view& selection,
                 char replace=' ', size_t limit=0);

// PROBLEM #2

// Implement the three-way comparison operator <=> that works with two dates.

struct CalendarDate {
   unsigned year;
   std::string month;
   unsigned day;
};

std::strong_ordering operator<=>(const CalendarDate& day1, const CalendarDate& day2);

// PROBLEM #3

// Given a string_view and a vector<long long>, extract all integers from the
// string and insert them into the vector, in the order in which they appear
// in the string.  Return a new string where all integers are replaced with "{}".
// (Return by value -- don't need to use "new" to allocate a new string. Just
// declare a local variable and return it.)

// And to make it more interesting, there may be commas embedded in the string's
// integers -- these must be ignored. In other words, the text "1,234,567" should
// be interpreted as the integer value 1234567LL and replaced with {}.

std::string removeNumbers(std::string_view text, std::vector<long long>& nums);

#endif //SPR25_HW1_H
