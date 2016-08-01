#pragma once
#include <exception>
#include <string>

namespace m7 {

/// Base class for all libm7 exceptions.
class Exception : public std::exception {
       public:
	/// Construct with empty message.
	Exception() = default;
	/// Construct with given message.
	Exception(std::string msg) : _msg(std::move(msg)) {}

	/// Return embedded message.
	virtual const char* what() const noexcept override {
		return _msg.c_str();
	}

       private:
	std::string _msg;
};
}  // namespace m7
