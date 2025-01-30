#ifndef ECE309_INTERVAL_H
#define ECE309_INTERVAL_H

#include <vector>
#include <compare>

namespace ece309 {

   class Interval {
   public:
   // Used the  compiler-generated defaults for the copy constructor, assignment, and destructor.
      Interval(int min, int max);   // constructor
      Interval(const Interval&);    // copy constructor
      Interval& operator=(const Interval&);  // assignment operator
      ~Interval();   // destructor

      // getters
      int getMin() const;
      int getMax() const;
      std::size_t getWidth() const;

      // overloaded operators
      Interval operator+(const Interval&) const;    // addition
      Interval operator-(const Interval&) const;    // subtraction
      Interval operator*(const Interval&) const;    // multiplication
      std::partial_ordering operator <=> (const Interval&) const;  // compare
      Interval operator>>(unsigned int) const;      // right shift
      Interval operator<<(unsigned int) const;      // left shift

      // member functions
      Interval unionWith(const Interval&) const;
      Interval intersectionWith(const Interval&) const;

   private:
      int min;
      int max;
      // private member variables, etc., go here
   };

   // non-member functions related to Interval

   // return true if there is at least one element of v that is
   // equivalent to i
   bool find(const std::vector<Interval>& v, const Interval& i);

   // return a vector that contains all elements of v
   // that satisfy the relationship with i
   // (e.g., all elements less than i)
   std::vector<Interval> filter(const std::vector<Interval>& v,
                                const Interval& i,
                                std::partial_ordering relation);

} // ece309

#endif //ECE309_INTERVAL_H



