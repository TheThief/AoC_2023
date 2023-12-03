#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "AoC_2023_Day1/AoC_2023_Day1.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

namespace aoc2023::day1::test
{
	const std::string test_input_1 =
R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet)"s;

	const std::string test_input_2 =
R"(two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen)"s;

	TEST_CLASS(Test)
	{
	public:
		Test()
		{
		}

		TEST_METHOD(Part1)
		{
			puzzle_input input;
			std::istringstream(test_input_1) >> input;
			const int expected_test_ouput_1 = 142;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			puzzle_input input;
			std::istringstream(test_input_2) >> input;
			const int expected_test_ouput_2 = 281;
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
