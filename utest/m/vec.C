#include <gtest/gtest.h>
#include <m7/m/vec.H>

using namespace m7;
using namespace m7::m;

#define INST_TYPE(T)                      \
	template struct m7::m::Vec<T, 1>; \
	template struct m7::m::Vec<T, 2>; \
	template struct m7::m::Vec<T, 3>; \
	template struct m7::m::Vec<T, 4>

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
