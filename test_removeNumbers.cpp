#include "gtest/gtest.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
#include "hw1.h"


TEST(RemoveNumbers, EmptyString) {
   vector<long long> vector_output{};
   string string_output {removeNumbers("", vector_output)};
   EXPECT_EQ(std::size(string_output), 0);
   EXPECT_EQ(std::size(vector_output), 0);
}

TEST(RemoveNumbers, SmallString) {
   const string text1 {"There are 12 eggs in a dozen."};
   const string expected_output {"There are {} eggs in a dozen."};
   const vector<long long> expected_numbers {12LL};
   vector<long long> vector_output {};
   string string_output {removeNumbers(text1, vector_output)};
   EXPECT_STREQ(string_output.data(), expected_output.data())
                    << "Input string: \"" << text1 << "\"\n";
   ASSERT_EQ(std::size(vector_output), std::size(expected_numbers));
   EXPECT_EQ(vector_output, expected_numbers);
}

TEST(RemoveNumbers, NonemptyVector) {
   const string text1 {"There are 12 eggs in a dozen."};
   vector<long long> vector_output {1, 2, 3};
   string string_output {removeNumbers(text1, vector_output)};
   EXPECT_EQ(std::size(vector_output), 1);
}

TEST(RemoveNumbers, NoNumString) {
   const string text1 {"No numbers in this string"};
   vector<long long> vector_output {};
   string string_output {removeNumbers(text1, vector_output)};
   EXPECT_STREQ(string_output.data(), text1.data())
      << "Input string: \"" << text1 << "\"\n";
   EXPECT_EQ(std::size(vector_output), 0);
}

TEST(RemoveNumbers, MultiNumString) {
   const string text1 {"The sum of 999 and 100 is 1099."};
   const string expected_output {"The sum of {} and {} is {}."};
   const vector<long long> expected_numbers {999LL, 100LL, 1099LL};
   vector<long long> vector_output {};
   string string_output {removeNumbers(text1, vector_output)};
   EXPECT_STREQ(string_output.data(), expected_output.data())
                    << "Input string: \"" << text1 << "\"\n";
   ASSERT_EQ(std::size(vector_output), std::size(expected_numbers));
   EXPECT_EQ(vector_output, expected_numbers);
}

TEST(RemoveNumbers, StringWithMinus) {
   const string text1 {"The sum of -999 and 1000 is 1 -- a non-negative number."};
   const string expected_output {"The sum of {} and {} is {} -- a non-negative number."};
   const vector<long long> expected_numbers {-999LL, 1000LL, 1LL};
   vector<long long> vector_output {};
   string string_output {removeNumbers(text1, vector_output)};
   EXPECT_STREQ(string_output.data(), expected_output.data())
                    << "Input string: \"" << text1 << "\"\n";
   ASSERT_EQ(std::size(vector_output), std::size(expected_numbers));
   EXPECT_EQ(vector_output, expected_numbers);
}

TEST(RemoveNumbers, StringWithCommas) {
   const string text1 {"The sum of 9,999 and 1,000,000 is 1,009,999, isn't it?"};
   const string expected_output {"The sum of {} and {} is {}, isn't it?"};
   const vector<long long> expected_numbers {9'999LL, 1'000'000LL, 1'009'999LL};
   vector<long long> vector_output {};
   string string_output = {removeNumbers(text1, vector_output)};
   EXPECT_STREQ(string_output.data(), expected_output.data())
                    << "Input string: \"" << text1 << "\"\n";
   ASSERT_EQ(std::size(vector_output), std::size(expected_numbers));
   EXPECT_EQ(vector_output, expected_numbers);

}

TEST(RemoveNumbers, StringFromChatGPT) {
   const string text1{
           "In 2025, the global population reached 8,054,326,402.\n"
           "China had a population of 1,425,784,000, followed closely by India with 1,412,600,000.\n"
           "The United States reported 335,894,000 inhabitants, while Indonesia's \n"
           "population stood at 287,501,000. Pakistan's population reached 243,381,000.\n"
           "The world experienced 134,568,000 births and 59,783,000 deaths in the same year.\n"
           "In terms of urbanization, 6,8 billion people were classified as living in urban areas, \n"
           "compared to 1.2 billion in rural areas. The total number of registered vehicles worldwide \n"
           "exceeded 1,618,900,000, and global energy consumption was recorded at 201,284,560,000 \n"
           "megawatt-hours. The year also saw 587432 disasters globally - resulting in damages \n"
           "estimated at $297840000000."
   };
   const string expected_output {
           "In {}, the global population reached {}.\n"
           "China had a population of {}, followed closely by India with {}.\n"
           "The United States reported {} inhabitants, while Indonesia's \n"
           "population stood at {}. Pakistan's population reached {}.\n"
           "The world experienced {} births and {} deaths in the same year.\n"
           "In terms of urbanization, {} billion people were classified as living in urban areas, \n"
           "compared to {}.{} billion in rural areas. The total number of registered vehicles worldwide \n"
           "exceeded {}, and global energy consumption was recorded at {} \n"
           "megawatt-hours. The year also saw {} disasters globally - resulting in damages \n"
           "estimated at ${}."
   };
   const vector<long long> expected_numbers{
           2025LL, 8'054'326'402LL, 1'425'784'000LL, 1'412'600'000LL,
           335'894'000LL, 287'501'000LL, 243'381'000LL, 134'568'000LL, 59'783'000LL,
           68LL, 1LL, 2LL, 1'618'900'000LL, 201'284'560'000LL, 587432LL, 297840000000LL
   };
   vector<long long> vector_output {};
   string string_output {removeNumbers(text1, vector_output)};
   EXPECT_STREQ(string_output.data(), expected_output.data())
                    << "Input string: \"" << text1 << "\"\n";
   ASSERT_EQ(std::size(vector_output), std::size(expected_numbers));
   EXPECT_EQ(vector_output, expected_numbers);

}