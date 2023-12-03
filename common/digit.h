#pragma once

#include <charconv>
#include <iostream>

struct digit
{
	int i;

	friend std::istream& operator>>(std::istream& is, digit& d)
	{
		char c = is.peek();
		auto result = std::from_chars(&c, &c + 1, d.i);
		if (result.ptr == &c + 1)
			is.ignore();
		else
			is.setstate(std::ios::failbit);

		return is;
	}

	operator int() const
	{
		return i;
	}
};
