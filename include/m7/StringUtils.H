#pragma once
#include <array>
#include <string_view>

namespace m7 {

template <size_t N>
constexpr std::string_view sv(const char (&literal)[N]) {
	return std::string_view(literal, N - 1);
}

template <size_t... N>
constexpr std::array<std::string_view, sizeof...(N)> sva(
    const char (&... literals)[N]) {
	return {{sv(literals)...}};
}
}  // namespace m7
