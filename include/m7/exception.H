#pragma once
#include <exception>
#include <string>

namespace m7 {

class Exception : public std::exception {
       public:
	Exception() = default;
	Exception(std::string msg) : _msg(std::move(msg)) {}

	virtual const char* what() const noexcept override {
		return _msg.c_str();
	}

       private:
	std::string _msg;
};
}  // namespace m7
