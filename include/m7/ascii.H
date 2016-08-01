#pragma once

namespace m7 {

/// Namespace of ascii character manipulation functions.
namespace ascii {

/// Return true if c is an ascii space.
constexpr inline bool isSpace(char c) {
	return c == ' ' || c == '\f' || c == '\r' || c == '\n' || c == '\t' ||
	       c == '\v';
}

/// Return true if c is an ascii blank.
constexpr inline bool isBlank(char c) { return c == ' ' || c == '\t'; }

/// Return true if c is an ascii character (0-127).
constexpr inline bool isAscii(char c) { return ((unsigned char)c) & 0x7F; }

/// Return true if c is an ascii lower case letter.
constexpr inline bool isLower(char c) { return c >= 'a' && c <= 'z'; }

/// Return true if c is an ascii upper case letter.
constexpr inline bool isUpper(char c) { return c >= 'A' && c <= 'Z'; }

/// Return true if c is an ascii digit.
constexpr inline bool isDigit(char c) { return c >= '0' && c <= '9'; }

/// Return true if c is an ascii letter.
constexpr inline bool isAlpha(char c) { return isUpper(c) || isLower(c); }

/// Return true if c is an ascii hex digit.
constexpr inline bool isHexDigit(char c) {
	return isDigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

/// Return true if c is an ascii letter or digit.
constexpr inline bool isAlnum(char c) { return isDigit(c) || isAlpha(c); }

/// Return true if c is an ascii control character.
constexpr inline bool is_cntrl(char c) {
	return (c >= 0 && c <= 0x1f) || c == 0x7F;
}

/// Return true if c is an ascii punctuation character.
constexpr inline bool is_punct(char c) {
	return (c >= '!' && c <= '/') || (c >= ':' && c <= '@') ||
	       (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
}

/// Return true if c is an ascii letter, digit, or punctuation character.
constexpr inline bool isGraph(char c) { return isAlnum(c) || is_punct(c); }

/// Return true if c is an ascii printable character.
constexpr inline bool isPrint(char c) { return isGraph(c) || c == ' '; }

/// If c is an upper case ascii letter, return lower case, otherwise return c.
constexpr char toLower(char c) { return isUpper(c) ? c + ('a' - 'A') : c; }

/// If c is an lower case ascii letter, return upper case, otherwise return c.
constexpr char toUpper(char c) { return isLower(c) ? c - ('a' - 'A') : c; }

/// Convert ascii digit c to int.
/// \pre isDigit(c) == true.
constexpr int intFromDigit(char c) { return int(c - '0'); }

/// Convert ascii digit c to int and multiply by m.
/// \pre isDigit(c) == true.
/// \remark m is usually a mutiple of 10.
constexpr int intFromDigit(char c, int m) { return intFromDigit(c) * m; }

/// Convert ascii hex digit c to int.
/// \pre isDexDigit(c) == true.
constexpr int intFromXDigit(char c) {
	return (c <= '9') ? intFromDigit(c)
			  : int((c <= 'Z') ? c - 'A' : c + 'a') + 0xA;
}

/// Convert ascii hex digit c to int and multiply by m.
/// \pre isHexDigit(c) == true.
/// \remark m is usually a mutiple of 16.
constexpr int intFromXDigit(char c, int m) { return intFromXDigit(c) * m; }

/// Convert i % 10 to ascii digit.
/// \pre i > 0.
constexpr char digitFromInt(int i) { return (i % 10) + '0'; }

/// Convert (i / m) % 10 to ascii digit.
/// \pre i > 0.
/// \remark m is usually a mutiple of 10.
constexpr char digitFromInt(int i, int m) { return digitFromInt(i / m); }

/// Convert i % 16 to ascii digit.
/// \pre i > 0.
constexpr char xDigitFromInt(int i) {
	return ((i & 0xf) > 9) ? (i & 0xf) - 0xA + 'a' : (i & 0xf) + '0';
}

/// Convert i % 16 to ascii digit.
/// \pre i > 0.
/// \remark m is usually a mutiple of 16.
constexpr char xDigitFromInt(int i, int m) { return xDigitFromInt(i / m); }

/// Convert i % 16 to ascii digit.
/// \pre i > 0.
constexpr char XDigitFromInt(int i) {
	return ((i & 0xf) > 9) ? (i & 0xf) - 0xA + 'A' : (i & 0xf) + '0';
}

/// Convert (i / m) % 16 to ascii digit.
/// \pre i > 0.
/// \remark m is usually a mutiple of 16.
constexpr char XDigitFromInt(int i, int m) { return XDigitFromInt(i / m); }

};  // namespace ascii
};  // namespace m7
