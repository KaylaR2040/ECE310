#include "gtest/gtest.h"
#include "hw1.h"

TEST(ReplaceChar, ReplaceFirst) {
   const std::string input {"abc def ghi"};
   const std::string default_out {" bc def ghi"};
   const std::string q_out {"?bc def ghi"};
   std::string text { input };
   replaceChar(text, 'a');
   EXPECT_STREQ(text.data(), default_out.data())
      << "args: \"" << input << R"(", 'a')";
   text = input;
   replaceChar(text, 'a', '?');
   EXPECT_STREQ(text.data(), q_out.data())
      << "args: \"" << input << R"(", 'a', '?')";
}

TEST(ReplaceChar, ReplaceLast) {
   const std::string input {"abc def ghi"};
   const std::string default_out {"abc def gh "};
   const std::string plus_out {"abc def gh+"};
   std::string text { input };
   replaceChar(text, 'i');
   ASSERT_STREQ(text.data(), default_out.data())
      << "args: \"" << input << R"(", 'i')";
   text = input;
   replaceChar(text, 'i', '+');
   EXPECT_STREQ(text.data(), plus_out.data())
      << "args: \"" << input << R"(", 'i', '+')";
}

TEST(ReplaceChar, ReplaceNone) {
   const std::string input {"abc def ghi"};
   std::string text { input };
   replaceChar(text, 'A');
   EXPECT_STREQ(text.data(), input.data())
      << "args: \"" << input << R"(", 'A')";
}

TEST(ReplaceChar, ReplaceAll) {
   const std::string input {"one, two, zippidy-doo, ..."};
   const std::string default_out {"one  two  zippidy-doo  ..."};
   const std::string star_out {"*ne, tw*, zippidy-d**, ..."};
   std::string text { input };
   replaceChar(text, ',');
   EXPECT_STREQ(text.data(), default_out.data())
      << "args: \"" << input << R"(", ',')";
   text = input;
   replaceChar(text, 'o', '*');
   EXPECT_STREQ(text.data(), star_out.data())
      << "args: \"" << input << R"(", 'o', '*')";
}

TEST(ReplaceChar, ReplaceLimit) {
   const std::string input {"one, two, zippidy-doo, ..."};
   const std::string one_out {"-ne, two, zippidy-doo, ..."};
   const std::string three_out {"-ne, tw-, zippidy-d-o, ..."};
   const std::string all_out {"-ne, tw-, zippidy-d--, ..."};
   std::string text { input };
   replaceChar(text, 'o', '-', 1);
   EXPECT_STREQ(text.data(), one_out.data())
      << "args: \"" << input << R"(", 'o', '-', 1)";
   text = input;
   replaceChar(text, 'o', '-', 3);
   EXPECT_STREQ(text.data(), three_out.data())
      << "args: \"" << input << R"(", 'o', '-', 3)";
   text = input;
   replaceChar(text, 'o', '-', 10);
   EXPECT_STREQ(text.data(), all_out.data())
      << "args: \"" << input << R"(", 'o', '-', 10)";
}

TEST(ReplaceChar, ReplaceSelectAll) {
   const std::string input {"one, two, zippidy-doo, ..."};
   // replace o, p, ., with space
   const std::string default_out {" ne, tw , zi  idy-d  ,    "};
   // replace n, t, z, -, with !
   const std::string bang_out { "o!e, !wo, !ippidy!doo, ..."};
   std::string text { input };
   replaceChar(text, "op.");
   EXPECT_STREQ(text.data(), default_out.data())
      << "args: \"" << input << R"(", "op.")";
   text = input;
   replaceChar(text, "-nzt", '!');
   EXPECT_STREQ(text.data(), bang_out.data())
      << "args: \"" << input << R"(", "-nzt", '!')";
}

TEST(ReplaceChar, ReplaceSelectLimit) {
   const std::string input {"one, two, zippidy-doo, ..."};
   // replace i, d, . with space, limit = 1
   const std::string one_out {"one, two, z ppidy-doo, ..."};
   // replace n, t, z, -, with !, limit 2
   const std::string two_out { "o!e, !wo, zippidy-doo, ..."};
   std::string text { input };
   replaceChar(text, "id.", ' ', 1);
   EXPECT_STREQ(text.data(), one_out.data())
      << "args: \"" << input << R"(", "id.", ' ', 1)";
   text = input;
   replaceChar(text, "-nzt", '!', 2);
   EXPECT_STREQ(text.data(), two_out.data())
      << "args: \"" << input << R"(", "-nzt", '!', 2)";
}