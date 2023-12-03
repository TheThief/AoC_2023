#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <range/v3/all.hpp>

using namespace std::string_view_literals;

namespace aoc2023::day1
{
	struct puzzle_input
	{
		std::vector<std::string> lines;

		friend std::istream& operator>>(std::istream& is, puzzle_input& input)
		{
			input.lines = ranges::getlines(is) | ranges::to<std::vector>;

			return is;
		}
	};

	int part1(const puzzle_input& input)
	{
		return ranges::accumulate(
			input.lines | ranges::views::transform(
				[](const auto& line)
				{
					auto first = line.find_first_of("0123456789");
					auto last = line.find_last_of("0123456789");
					return (line[first] - '0') * 10 + (line[last] - '0');
				}), 0);
	}

	const std::map<std::string_view, int> values =
	{
		{"1"sv, 1},
		{"2"sv, 2},
		{"3"sv, 3},
		{"4"sv, 4},
		{"5"sv, 5},
		{"6"sv, 6},
		{"7"sv, 7},
		{"8"sv, 8},
		{"9"sv, 9},
		{"0"sv, 0},
		{"one"sv,   1},
		{"two"sv,   2},
		{"three"sv, 3},
		{"four"sv,  4},
		{"five"sv,  5},
		{"six"sv,   6},
		{"seven"sv, 7},
		{"eight"sv, 8},
		{"nine"sv,  9},
	};

	int part2(const puzzle_input& input)
	{
		return ranges::accumulate(
			input.lines | ranges::views::transform(
				[](auto line)
				{
					line += "....";
					auto forward = line | ranges::views::sliding(5) |
						ranges::views::for_each(
							[](const auto& line)
							{
								return values | ranges::views::for_each(
									[line](const auto& value_pair) -> std::vector<int>
									{
										if (ranges::starts_with(line, value_pair.first))
											return { value_pair.second };
										return {};
									});
							});
					auto reverse = line | ranges::views::sliding(5) | ranges::views::reverse |
						ranges::views::for_each(
							[](const auto& line)
							{
								return values | ranges::views::for_each(
									[line](const auto& value_pair) -> std::vector<int>
									{
										if (ranges::starts_with(line, value_pair.first))
											return { value_pair.second };
										return {};
									});
							});
					auto first = *std::begin(forward);
					auto last = *std::begin(reverse);
					return first * 10 + last;
				}), 0);
	}
}
