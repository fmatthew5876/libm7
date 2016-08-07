#include <gtest/gtest.h>
#include <m7/m/vec.H>

using namespace m7;
using namespace m7::m;

#define INST_ONE(T, N)                                           \
	template struct m7::m::Vec<T, N>;                        \
	static_assert(sizeof(m7::m::Vec<T, N>) == N * sizeof(T), \
		      "Size is incorrect??")

#define INST_TYPE(T)    \
	INST_ONE(T, 1); \
	INST_ONE(T, 2); \
	INST_ONE(T, 3); \
	INST_ONE(T, 4); \
	INST_ONE(T, 5)

INST_TYPE(bool);
INST_TYPE(char);
INST_TYPE(signed char);
INST_TYPE(unsigned char);
INST_TYPE(signed short);
INST_TYPE(unsigned short);
INST_TYPE(signed int);
INST_TYPE(unsigned int);
INST_TYPE(signed long);
INST_TYPE(unsigned long);
INST_TYPE(signed long long);
INST_TYPE(unsigned long long);

INST_TYPE(float);
INST_TYPE(double);
