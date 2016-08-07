#include <gtest/gtest.h>
#include <m7/m/mat.H>

using namespace m7;
using namespace m7::m;

#define INST_ONE(T, M, N)                                               \
	template struct m7::m::Mat<T, M, N>;                            \
	static_assert(sizeof(m7::m::Mat<T, M, N>) == sizeof(T) * M * N, \
		      "Size is incorrect???");

#define INST_TYPE(T)       \
	INST_ONE(T, 1, 1); \
	INST_ONE(T, 1, 2); \
	INST_ONE(T, 1, 3); \
	INST_ONE(T, 1, 4); \
	INST_ONE(T, 1, 5); \
	INST_ONE(T, 2, 1); \
	INST_ONE(T, 2, 2); \
	INST_ONE(T, 2, 3); \
	INST_ONE(T, 2, 4); \
	INST_ONE(T, 2, 5); \
	INST_ONE(T, 3, 1); \
	INST_ONE(T, 3, 2); \
	INST_ONE(T, 3, 3); \
	INST_ONE(T, 3, 4); \
	INST_ONE(T, 3, 5); \
	INST_ONE(T, 4, 1); \
	INST_ONE(T, 4, 2); \
	INST_ONE(T, 4, 3); \
	INST_ONE(T, 4, 4); \
	INST_ONE(T, 4, 5); \
	INST_ONE(T, 5, 1); \
	INST_ONE(T, 5, 2); \
	INST_ONE(T, 5, 3); \
	INST_ONE(T, 5, 4); \
	INST_ONE(T, 5, 5)

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
