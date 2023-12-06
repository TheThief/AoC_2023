#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include <range/v3/all.hpp>
#include "common/delimitered.h"
#include "common/stream_line.h"
#include "common/stream_required.h"

using namespace std::string_view_literals;

namespace aoc2023::day2
{
	enum class colour : int
	{
		red,
		green,
		blue,
	};
	struct bag
	{
		std::array<int, 3> balls; // indexed by enum colour

		struct ball
		{
			int count;
			std::string colour;

			friend std::istream& operator>>(std::istream& is, ball& input)
			{
				is >> input.count >> input.colour;
				return is;
			}
		};

		friend std::istream& operator>>(std::istream& is, bag& input)
		{
			delimitered_vector<ball, ','> balls;
			is >> balls;
			input.balls = {};
			for (const auto& ball : balls.value)
			{
				if (ball.colour == "red")
					input.balls[(int)colour::red] = ball.count;
				else if (ball.colour == "green")
					input.balls[(int)colour::green] = ball.count;
				else if (ball.colour == "blue")
					input.balls[(int)colour::blue] = ball.count;
			}

			return is;
		}

		std::partial_ordering operator<=>(const bag& rhs) const
		{
			std::weak_ordering o = balls[0] <=> rhs.balls[0];
			std::weak_ordering o2 = balls[1] <=> rhs.balls[1];
			if (o == 0)
				o = o2;
			else if (o2 != 0 && o2 != o)
				return std::partial_ordering::unordered;
			std::weak_ordering o3 = balls[2] <=> rhs.balls[2];
			if (o == 0)
				o = o2;
			else if (o3 != 0 && o3 != o)
				return std::partial_ordering::unordered;
			return o;
		}
	};

	struct game
	{
		int id;
		std::vector<bag> bags;

		friend std::istream& operator>>(std::istream& is, game& input)
		{
			is >> required{ "Game " } >> input.id >> required{ ": " };
			delimitered_vector<bag, ';'> bags;
			is >> bags;
			input.bags = std::move(bags.value);

			return is;
		}
	};
	struct puzzle_input
	{
		std::vector<game> games;

		friend std::istream& operator>>(std::istream& is, puzzle_input& input)
		{
			input.games = ranges::istream_view<line<game>>(is) | ranges::to<std::vector<game>>();

			return is;
		}
	};

	int part1(const puzzle_input& input)
	{
		return ranges::accumulate(
			input.games | ranges::views::filter(
				[](const auto& game)
				{
					return ranges::all_of(game.bags, [](const auto& b) { return b < bag{ 12, 13, 14 }; });
				}), 0, std::plus(), &game::id);
	}

	int part2(const puzzle_input& input)
	{
		return ranges::accumulate(
			input.games | ranges::views::transform(
				[](const auto& game)
				{
					return *ranges::fold_left_first(game.bags,
						[](const auto& b1, const auto& b2)
						{
							return bag{
								std::max(b1.balls[0], b2.balls[0]),
								std::max(b1.balls[1], b2.balls[1]),
								std::max(b1.balls[2], b2.balls[2])
							};
						});
				}) |
			ranges::views::transform(
				[](const auto& min_bag)
				{
					return *ranges::fold_left_first(min_bag.balls, std::multiplies());
				})
			, 0);
	}
}
