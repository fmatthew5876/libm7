#pragma once

namespace m7::ascii {

///true if c is an ascii digit.
constexpr bool isdigit(int c) noexcept {
  return c >= '0' && c <= '9';
}

///true if c is an ascii hex digit.
constexpr bool isxdigit(int c) noexcept {
  return isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

///true if c is an ascii hex digit (upper case only).
constexpr bool isxudigit(int c) noexcept {
  return isdigit(c) || (c >= 'A' && c <= 'F');
}

///true if c is an ascii hex digit (lower case only).
constexpr bool isxldigit(int c) noexcept {
  return isdigit(c) || (c >= 'a' && c <= 'f');
}

///true if c is a lower case ascii letter.
constexpr bool islower(int c) noexcept {
  return c >= 'a' && c <= 'z';
}

///true if c is an lower case ascii letter.
constexpr bool isupper(int c) noexcept {
  return c >= 'A' && c <= 'Z';
}

///true if c is an ascii letter.
constexpr bool isalpha(int c) noexcept {
  return islower(c) || isupper(c);
}

///true if c is an alpha-numeric ascii character.
constexpr bool isalnum(int c) noexcept {
  return isalpha(c) || isdigit(c);
}

///true if c is an ascii punctuation character.
constexpr bool ispunct(int c) noexcept {
  return (c >= '!' && c <= '/') || (c >= ':' && c <= '@') || (c >= '[' && c <= '`') || (c >= '{' && c <= '~');
}

///true if c is an ascii character with a graphical representation.
constexpr bool isgraph(int c) noexcept {
  return c >= '!' && c <='~';
}

///true if c is an ascii blank character.
constexpr bool isblank(int c) noexcept {
  return c == '\t' || c == ' ';
}

///true if c is an ascii space character.
constexpr bool isspace(int c) noexcept {
  return c == ' ' || (c >= '\t' && c <= '\r');
}

///true if c is an ascii printable character.
constexpr bool isprint(int c) noexcept {
  return c >= ' '&& c <= '~';
}

///true if c is an ascii control character.
constexpr bool iscntrl(int c) noexcept {
  return c == 0x7F || (c >= 0 && c <= 0x1F);
}

///If c is an upper-case ascii character converts to lower case, otherwise returns c.
constexpr char tolower(int c) noexcept {
  return isupper(c) ? c + ('z' - 'Z') : c;
}

///If c is an lower-case ascii character converts to upper case, otherwise returns c.
constexpr char toupper(int c) noexcept {
  return islower(c) ? c - ('z' - 'Z') : c;
}

//Converts character c into a digit.
//\pre m7::ascii::isdigit(c) == true
constexpr int todigit(int c) noexcept {
  return (c - '0');
}

//Converts character c into a digit, and then multiples by m
//\pre m7::ascii::isdigit(c) == true
//\note Usually m is a power of 10.
constexpr int todigit(int c, int m) noexcept {
  return todigit(c) * m;
}


//Converts character c into a hex digit
//\pre m7::ascii::isxdigit(c) == true
constexpr int toxdigit(int c) noexcept {
  if(c >= 'a' && c <= 'f') {
    return (c - 'a' + 0xa);
  }
  if(c >= 'A' && c <= 'F') {
    return (c - 'A' + 0xA);
  }
  return todigit(c);
}

//Converts character c into a hex digit and then multiples by m
//\pre m7::ascii::isxdigit(c) == true
//\note Usually m is a power of 0x10
constexpr int toxdigit(int c, int m) noexcept {
  return toxdigit(c) * m;
}


//Converts character c into a hex digit
//\pre m7::ascii::isxudigit(c) == true
constexpr int toxudigit(int c) noexcept {
  if(c >= 'A' && c <= 'F') {
    return (c - 'A' + 0xA);
  }
  return todigit(c);
}

//Converts character c into a hex digit and then multiples by m
//\pre m7::ascii::isxudigit(c) == true
//\note Usually m is a power of 0x10
constexpr int toxudigit(int c, int m) noexcept {
  return toxudigit(c) * m;
}

//Converts character c into a hex digit
//\pre m7::ascii::isxldigit(c) == true
constexpr int toxldigit(int c) noexcept {
  if(c >= 'a' && c <= 'f') {
    return (c - 'a' + 0xa);
  }
  return todigit(c);
}

//Converts character c into a hex digit and then multiples by m
//\pre m7::ascii::isxldigit(c) == true
//\note Usually m is a power of 0x10
constexpr int toxldigit(int c, int m) noexcept {
  return toxldigit(c) * m;
}


}  // namespace m7::ascii
