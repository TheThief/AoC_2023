#include "CppUnitTest.h"

#include <sstream>
#include <string_view>
#include "AoC_2023_Day2/AoC_2023_Day2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

namespace aoc2023::day2::test
{
	const std::string test_input =
R"(Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green)"s;

	TEST_CLASS(Test)
	{
	public:
		Test()
		{
		}

		TEST_METHOD(Part1)
		{
			puzzle_input input;
			std::istringstream(test_input) >> input;
			const int expected_test_ouput_1 = 8;
			Assert::AreEqual(expected_test_ouput_1, part1(input));
		}

		TEST_METHOD(Part2)
		{
			puzzle_input input;
			std::istringstream(test_input) >> input;
			const int expected_test_ouput_2 = 2286;
			Assert::AreEqual(expected_test_ouput_2, part2(input));
		}
	};
}
