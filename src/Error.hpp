#ifndef ERROR_OBJ
#define ERROR_OBJ

#include <iostream>

#define E_TARGET_PACK_PUSH  1
#define E_WORK_PACK_POP     2
#define E_WORK_PACK_PUSH    3
#define E_REM_PACK_POP      4

class ErrorException {
private:
    int error_code;
    std::string msg;

public:
    ErrorException(int error, std::string message);

    int get_err_code();
    std::string get_message();
};

#endif //ERROR_OBJ