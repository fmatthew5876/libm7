#pragma once
#include <exception>

namespace m7 {

class Exception : public std::exception {
       public:
	Exception() = default;
	Exception(std::string msg) : _msg(std::move(msg)) {}

	virtual const char* what() override { return _msg.c_str(); }

       private:
	std::string _msg;
};
}  // namespace m7
