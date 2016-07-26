#pragma once
#include <experimental/string_view>

namespace m7 {
using StringView = std::experimental::string_view;

template <size_t N>
constexpr StringView sv(const char (&literal)[N]) {
	return StringView(literal, N - 1);
}

template <size_t... N>
constexpr std::array<StringView, sizeof...(N)> sva(
    const char (&... literals)[N]) {
	return {{sv(literals)...}};
}
}  // namespace m7
