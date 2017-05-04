/*! 
 *  \file       Error.cpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#include "Error.hpp"

ErrorException::ErrorException(int error, std::string message) {
    this->error_code = error;
    this->msg = message;
    #ifdef DEBUG
    std::cerr << "Error : " << error << " MSG : " << message << std::endl;
    #endif
}

int ErrorException::get_err_code() {
    return this->error_code;
}

std::string ErrorException::get_message() {
    return this->msg;
}
