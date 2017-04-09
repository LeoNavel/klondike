#include "Error.hpp"

ErrorException::ErrorException(int error, std::string message) {
    this->error_code = error;
    this->msg = message;
}

int ErrorException::get_err_code() {
    return this->error_code;
}

std::string ErrorException::get_message() {
    return this->msg;
}
