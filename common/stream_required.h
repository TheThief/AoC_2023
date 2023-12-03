#pragma once

#include <iostream>
#include <string_view>

template<size_t N>
struct required : std::array<char, N>
{
};

template<size_t N>
required(const char (&)[N])->required<N>;

required(const char)->required<1>;

template<class e, class t, int N>
std::basic_istream<e, t>& operator>>(std::basic_istream<e, t>& in, const required<N>& req)
{
    std::array<char, N> buffer = {};
    bool null_terminated = req[N - 1] == 0;
    const size_t len = null_terminated ? N - 1 : N;
    if (len > 0)
        in >> buffer[0]; // skips whitespace, read first character
    if (len > 1)
        in.read(&buffer[1], len - 1); // read the rest
    if (std::string_view(&buffer[0], len) != std::string_view(&req[0], len))
        in.setstate(std::ios::failbit);
    return in;
}
