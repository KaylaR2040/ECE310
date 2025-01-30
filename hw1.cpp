#include "hw1.h"
#include <array>
#include <cctype>
#include <compare>
using std::string;
using std::string_view;
using std::array;
using std::size;


// PROBLEM 1 -- two versions of a string replacement function
// The first specifies one character, while the second replaces any
// character that occurs in a string.  Both have default parameters
// for the replacement char and the number of replacements.
// (limit == 0 means there's no limit)

void replaceChar(string &str, char target, char replace, size_t limit) {
  size_t count = 0; // Tracks the number of replacements made
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == target) {
            str[i] = replace;
            count++;
            if (limit != 0 && count >= limit) {
                break; // Stop when the limit is reached
            }
        }
    }
   }
   // tests that don't remove any characters will pass,
   // but you won't get credit if you don't implement the function

void replaceChar(string &str, const string_view &selection, char replace, size_t limit) {
  size_t count = 0; // Tracks the number of replacements made
    for (int i = 0; i < str.size(); i++) {
        if (selection.find(str[i]) != string_view::npos) { // Check if the character is in `selection`
            str[i] = replace;
            count++;
            if (limit != 0 && count >= limit) {
                break; // Stop when the limit is reached
            }
        }
    }
}   
   // tests that don't remove any characters will pass,
   // but you won't get credit if you don't implement the function


// PROBLEM 2: three-way comparison operator for two structs
std::strong_ordering operator<=>(const CalendarDate& day1, const CalendarDate& day2) {
   // tests that expect equal will pass, but you won't get credit if you don't implement the function
   
   //array of months
   std:: string months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October","November", "December"};
   // Compare the years
   if(day1.year < day2.year){
        return std::strong_ordering::less;
   }
   else if(day1.year == day2.year) {
    //get the index value of the month that relates to the month in the struct using the array of months so that it is a int
    int month1 = 0;
    int month2 = 0;
    for(int i = 0; i < 12; i++) {
        if(day1.month == months[i]) {
            month1 = i;
        }
        if(day2.month == months[i]) {
            month2 = i;
        }
    }
    if(month1 < month2){
        return std::strong_ordering::less;
    }
    else if(month1 == month2) {
        if(day1.day < day2.day) {
            return std::strong_ordering::less;
        } else if(day1.day == day2.day) {
            return std::strong_ordering::equal;
        }
        else{
            return std::strong_ordering::greater;
        }
       
   } else {
       return std::strong_ordering::greater;
   }
   }
   else {
       return std::strong_ordering::greater;
   }
}

// PROBLEM 3: remove numbers from text

string removeNumbers(std::string_view text, std::vector<long long>& nums) {
// clear the vector
nums.clear();
// create a string to store the result as a string_view
string result;
// store the numbers here
long long number = 0;  // Initialize to 0
bool numberfound = false;
bool negative = false;  // Track negative sign

// parse through the string input
for (int i = 0; i < text.size(); i++) {
    // check if the value is a negative number
    if (text[i] == '-') {
        // check if the next is a digit
        if (i + 1 < text.size() && isdigit(text[i + 1])) {
            negative = true;  // Mark as negative
        } else {
            result += text[i]; // Add '-' as is
        }
    }
    else if (isdigit(text[i])) {
        // check if the value is in the ones place
        numberfound = true;
        number = number * 10 + (text[i] - '0');  // Accumulate the number
    }
    else if (text[i] == ',') {
        // If the comma is part of a number, ignore it
        if (i > 0 && i + 1 < text.size() && isdigit(text[i - 1]) && isdigit(text[i + 1])) {
            continue; // Ignore the comma
        }
        // If the comma is not part of a valid number, process the current number
        if (numberfound) {
            // Apply the negative sign if necessary
            if (negative) {
                number = -number;
            }

            // add the number to the vector
            nums.push_back(number);
            // add the {} to the result string
            result += "{}";

            // reset the number and state
            number = 0;
            numberfound = false;
            negative = false;
        }
        // include the comma in the result
        result += text[i];
    }
    else {
        if (numberfound) {
            // Apply the negative sign if necessary
            if (negative) {
                number = -number;
            }

            // add the number to the vector
            nums.push_back(number);
            // add the {} to the result string
            result += "{}";

            // reset the number and state
            number = 0;
            numberfound = false;
            negative = false;
        }

        // include the non-numeric character in the result
        result += text[i];
    }
}

// handle any number found at the end of the string
if (numberfound) {
    if (negative) {
        number = -number;
    }
    nums.push_back(number);
    result += "{}";
}

return result;

}
