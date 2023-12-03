#pragma once

#include <iostream>
#include <optional>
#include <vector>

#include <range/v3/all.hpp>

template<typename T>
struct line
{
	T data;

	friend std::istream& operator>>(std::istream& is, line& l)
	{
		std::string line_string;
		std::getline(is, line_string);
		std::istringstream ss(line_string);
		ss >> l.data;

		return is;
	}

	operator T&       ()&      { return data; }
	operator T&&      ()&&     { return std::move(data); }
	operator T const& () const { return data; }

	bool operator ==(const line<T>&) const = default;
};

template<>
struct line<std::string>
{
	std::string data;

	friend std::istream& operator>>(std::istream& is, line& l)
	{
		std::getline(is, l.data);

		return is;
	}

	operator std::string& ()& { return data; }
	operator std::string && ()&& { return std::move(data); }
	operator std::string const& () const { return data; }

	bool operator ==(const line<std::string>&) const = default;
};

template<typename T>
struct line<std::vector<T>>
{
	std::vector<T> data;

	friend std::istream& operator>>(std::istream& is, line& l)
	{
		std::string line_string;
		std::getline(is, line_string);
		std::istringstream ss(line_string);
		l.data = ranges::istream_view<T>(ss) | ranges::to<std::vector>;

		return is;
	}

	operator std::vector<T>&       ()&      { return data; }
	operator std::vector<T>&&      ()&&     { return std::move(data); }
	operator std::vector<T> const& () const { return data; }

	// casting operators
	template<typename U>
	operator std::vector<U>() const& { return std::vector<U>(std::from_range, data); }
	template<typename U>
	operator std::vector<U>() &&     { return std::vector<U>(std::from_range, std::move(data)); }

	bool operator ==(const line<std::vector<T>>&) const = default;
};

template<typename T>
struct line<std::optional<T>>
{
	std::optional<T> data;

	friend std::istream& operator>>(std::istream& is, line& l)
	{
		std::string line_string;
		std::getline(is, line_string);
		if (!line_string.empty())
		{
			std::istringstream ss(line_string);
			T value;
			ss >> value;
			l.data = std::move(value);
		}
		else
		{
			l.data = std::nullopt;
		}

		return is;
	}

	operator std::optional<T>&       ()&      { return data; }
	operator std::optional<T>&&      ()&&     { return std::move(data); }
	operator std::optional<T> const& () const { return data; }

	bool operator ==(const line<std::optional<T>>&) const = default;
};
