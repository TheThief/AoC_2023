#pragma once

#include <iostream>
#include <string>

#include "stream_required.h"

template<typename T, char sep = ','>
struct delimitered_value
{
	T value;

	operator const T& () const { return value; }
	operator T && ()&& { return std::move(value); }
};

template<typename T, char sep>
std::istream& operator>>(std::istream& in, delimitered_value<T, sep>& t)
{
	if (!(in >> t.value)) //if we failed to read the int
		return in;          //return failure state
	if (in.peek() == sep) //if next character is a comma
		in.ignore();        //extract it from the stream and we're done
	else                  //if the next character is anything else
		in.clear();         //clear the EOF state, read was successful
	return in;
}

template<char sep>
std::istream& operator>>(std::istream& in, delimitered_value<std::string, sep>& t)
{
	std::getline(in, t.value, sep);
	return in;
}

template<typename T>
using comma_separated = delimitered_value<T, ','>;



template<typename T, char sep = ','>
struct delimitered_container;

template<typename T>
struct remove_delimitered
{
	using type = T;
};

template<typename T, char sep>
struct remove_delimitered<delimitered_container<T, sep>>
{
	using type = T;
};

template<typename T, typename U>
struct remove_delimitered<std::pair<T, U>>
{
	using type = std::pair<typename remove_delimitered<T>::type, typename remove_delimitered<U>::type>;
};

template<typename T, char sep>
struct delimitered_container
{
	T value;

	operator const T& () const& { return value; }
	operator T&& () && { return std::move(value); }
	operator remove_delimitered<T>::type() const& requires !std::same_as<T, remove_delimitered<T>::type> { return value; }
	operator remove_delimitered<T>::type() && requires !std::same_as<T, remove_delimitered<T>::type> { return std::move(value); }
};

template<typename T, typename U, char sep>
std::istream& operator>>(std::istream& in, delimitered_container<std::pair<T,U>, sep>& t)
{
	in >> t.value.first >> required{ sep } >> t.value.second;

	return in;
}

template<typename T, char sep, typename Alloc = std::allocator<T>>
std::istream& operator>>(std::istream& is, delimitered_container<std::vector<T, Alloc>, sep>& t)
{
	while(1)
	{
		auto pos = is.tellg();
		std::stringbuf next;
		if(!is.get(next, sep))   //if we failed to read the value
		{
			return is;          //return failure state (stream may not be in a consistent state, can't rewind)
		}
		std::istream is2(&next);
		T value;
		if (!(is2 >> value))   //if we failed to read the value
		{
			is.seekg(pos);
			is.setf(std::ios_base::failbit);
			return is;          //return failure state (stream may not be in a consistent state, can't rewind)
		}
		t.value.push_back(std::move(value));
		is2 >> std::ws;
		if (is2.eof()) //if next character matches the separator
		{
			if (is.eof())
				break;
			is.ignore();        //extract it from the stream and loop round
			continue;
		}
		else                  //if the next character is anything else
		{
			is.clear();         //clear the EOF state, read was successful
			is.seekg(pos + is2.tellg());
			break;
		}
	}
	return is;
}

template<typename T, typename U, char sep=','>
using delimitered_pair = delimitered_container<std::pair<T, U>, sep>;

template<typename T, char sep = ',', typename Alloc=std::allocator<T>>
using delimitered_vector = delimitered_container<std::vector<T, Alloc>, sep>;
