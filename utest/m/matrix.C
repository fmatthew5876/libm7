#include <gtest/gtest.h>
#include <m7/m/matrix.H>

using namespace m7;
using namespace m7::m;

#define INST_TYPE(T)                            \
	template struct m7::m::Matrix<T, 1, 1>; \
	template struct m7::m::Matrix<T, 1, 2>; \
	template struct m7::m::Matrix<T, 1, 3>; \
	template struct m7::m::Matrix<T, 1, 4>; \
	template struct m7::m::Matrix<T, 2, 1>; \
	template struct m7::m::Matrix<T, 2, 2>; \
	template struct m7::m::Matrix<T, 2, 3>; \
	template struct m7::m::Matrix<T, 2, 4>; \
	template struct m7::m::Matrix<T, 3, 1>; \
	template struct m7::m::Matrix<T, 3, 2>; \
	template struct m7::m::Matrix<T, 3, 3>; \
	template struct m7::m::Matrix<T, 3, 4>; \
	template struct m7::m::Matrix<T, 4, 1>; \
	template struct m7::m::Matrix<T, 4, 2>; \
	template struct m7::m::Matrix<T, 4, 3>; \
	template struct m7::m::Matrix<T, 4, 4>

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
