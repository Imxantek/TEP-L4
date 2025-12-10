#include "CError.h"
#include <string>
CError::CError(const std::string& message) {
	str_message = message;
}
CError::CError(const CError& other){
	str_message = other.str_message;
}

std::string CError::strGetMessage() const {
	return str_message;
}
//