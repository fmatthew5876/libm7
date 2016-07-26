#pragma once

namespace m7 {
namespace ascii {

constexpr inline bool isSpace(char c) {
	return c == ' ' || c == '\f' || c == '\r' || c == '\n' || c == '\t' ||
	       c == '\v';
}

constexpr inline bool isBlank(char c) { return c == ' ' || c == '\t'; }

constexpr inline bool isAscii(char c) { return ((unsigned char)c) & 0x7F; }

constexpr inline bool isLower(char c) { return c >= 'a' && c <= 'z'; }

constexpr inline bool isUpper(char c) { return c >= 'A' && c <= 'Z'; }

constexpr inline bool isDigit(char c) { return c >= '0' && c <= '9'; }

constexpr inline bool isAlpha(char c) { return isUpper(c) || isLower(c); }

constexpr inline bool isHexDigit(char c) {
	return isDigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

constexpr inline bool isAlnum(char c) { return isDigit(c) || isAlpha(c); }

constexpr inline bool is_cntrl(char c) {
	return (c >= 0 && c <= 0x1f) || c == 0x7F;
}

constexpr inline bool is_punct(char c) {
	return (c >= '!' && c <= '/') || (c >= ':' && c <= '@') ||
	       (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
}

constexpr inline bool isGraph(char c) { return isAlnum(c) || is_punct(c); }

constexpr inline bool isPrint(char c) { return isGraph(c) || c == ' '; }

constexpr char toLower(char c) { return isUpper(c) ? c + ('a' - 'A') : c; }

constexpr char toUpper(char c) { return isLower(c) ? c - ('a' - 'A') : c; }

constexpr int intFromDigit(char c) { return int(c - '0'); }

constexpr int intFromDigit(char c, int m) { return intFromDigit(c) * m; }

constexpr int intFromXDigit(char c) {
	return (c <= '9') ? intFromDigit(c)
			  : int((c <= 'Z') ? c - 'A' : c + 'a') + 0xA;
}

constexpr int intFromXDigit(char c, int m) { return intFromXDigit(c) * m; }

constexpr char digitFromInt(int i) { return (i % 10) + '0'; }

constexpr char digitFromInt(int i, int m) { return digitFromInt(i / m); }

constexpr char xDigitFromInt(int i) {
	return (i & 0xf > 9) ? (i & 0xf) - 0xA + 'a' : (i & 0xf) + '0';
}

constexpr char xDigitFromInt(int i, int m) { return xDigitFromInt(i / m); }

constexpr char XDigitFromInt(int i) {
	return (i & 0xf > 9) ? (i & 0xf) - 0xA + 'A' : (i & 0xf) + '0';
}

constexpr char XDigitFromInt(int i, int m) { return XDigitFromInt(i / m); }

};  // namespace ascii
};  // namespace m7
