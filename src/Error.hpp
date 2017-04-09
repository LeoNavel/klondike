#ifndef ERROR_OBJ
#define ERROR_OBJ

#include <iostream>

class ErrorException {
    int error_code;
    std::string msg;


    ErrorException(int error, std::string message);

    int get_err_code();
    std::string get_message();
};

#endif //ERROR_OBJ