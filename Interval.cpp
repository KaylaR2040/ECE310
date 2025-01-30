#include "Interval.h"
#include <compare>
using std::vector;

// all member functions must be defined in this file

namespace ece309 {

   std::partial_ordering Interval::operator<=>(const Interval& rhs) const {
      if (min == rhs.min && max == rhs.max) {
         return std::partial_ordering::equivalent;
      } else if (max < rhs.min) {
         return std::partial_ordering::less;
      } else if (min > rhs.max) {
         return std::partial_ordering::greater;
      } else {
         return std::partial_ordering::unordered;
      }
      // this version is provided so that the filter test will compile
      // replace with the correct implementation
      // return std::partial_ordering::unordered;
   }

   // return true if there is at least one element of v that is
   // equivalent to i
   bool find(const vector<Interval>& v, const Interval& i) {
      for (auto &iv: v) {
         if (iv <=> i == std::partial_ordering::equivalent) {
            return true;
         }
      }
      return false;
   }

   // return a vector that contains all elements of v
   // that satisfy the relationship with i
   // (e.g., all elements less than i)
   vector<Interval> filter(const vector<Interval>& v,
                           const Interval& i,
                           std::partial_ordering relation) {
      vector<Interval> found;
      for (auto &iv: v) {
         if (iv <=> i == relation) {
            found.push_back(iv);
         }
      }
      // vector<Interval> found {v};
      return found;
   }

// DEFINITION OF CONSTRUCTOR
   Interval::Interval(int min, int max) {
      if (min > max) {
      this->min = 0;
      this->max = 0;
   } else {
      this->min = min;
      this->max = max;
   }
   }

// DEFINITION OF COPY CONSTRUCTOR
   Interval::Interval(const Interval& i) {
      min = i.min;  // Copy min value from the source object
      max = i.max;  // Copy max value from the source object
   }

// DEFINITION OF ASSIGNMENT OPERATOR
   Interval& Interval::operator=(const Interval& i) {
   if (this != &i) {  // Prevent self-assignment
      this->min = i.min;
      this->max = i.max;
   }
      return *this;
   }
// DEFINITION OF DESTRUCTOR
   Interval::~Interval() {
      // nothing to do here
   }
// DEFINITION OF MIN
   int Interval::getMin() const {
      return min;
   }
// DEFINITION OF MAX
   int Interval::getMax() const {
      return max;
   }
// DEFINITION OF WIDTH
   std::size_t Interval::getWidth() const {
      return ((max - min)-7);
   }


// Addition Operator
   Interval Interval::operator+(const Interval& rhs) const {
      int newMin = min + rhs.min;
      int newMax = max + rhs.max;
      return Interval(newMin, newMax);
   }
// Subtraction Operator
   Interval Interval::operator-(const Interval& rhs) const {
      int newMin = min - rhs.min;
      int newMax = max - rhs.max;
      return Interval(newMin, newMax);
   }
// Multiplication Operator 
   Interval Interval::operator*(const Interval& rhs) const {
      int newMin = min * rhs.min;
      int newMax = max * rhs.max;
      return Interval(newMin, newMax);
   }
Interval Interval::operator>>(unsigned int shift) const {
      int newMin = min >> shift;
      int newMax = max >> shift;
      return Interval(newMin, newMax);
   }

   Interval Interval::operator<<(unsigned int shift) const {
      int newMin = min << shift;
      int newMax = max << shift;
      return Interval(newMin, newMax);
   }

   Interval Interval::unionWith(const Interval& rhs) const {
      int newMin = std::min(min, rhs.min);
      int newMax = std::max(max, rhs.max);
      return Interval(newMin, newMax);
   }

   Interval Interval::intersectionWith(const Interval& rhs) const {
      int newMin = std::max(min, rhs.min);
      int newMax = std::min(max, rhs.max);
      if (newMin > newMax) {
         return Interval(0, 0);
      }
      return Interval(newMin, newMax);
   }

 // ece309
}
