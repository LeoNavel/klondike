/*! 
 *  \file       Error.hpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef ERROR_OBJ
#define ERROR_OBJ

#include <iostream>

#define E_END_GAME                  0
#define E_TARGET_PACK_PUSH          1
#define E_WORK_PACK_POP             2
#define E_WORK_PACK_PUSH            3
#define E_REM_PACK_POP              4
#define E_POP_FROM_EMPTY_STACK      5
#define E_POP_INVISIBLE             6
#define E_PUSH_ON_INVISIBLE         7
#define E_NOT_VISIBLE               8
#define E_NOT_INVISIBLE             9
#define E_UNKNOWN_COMMAND           10
#define E_OUT_OF_RANGE              11
#define E_UNKNOWN_STACK_TYPE        12
#define E_NO_MORE_MOVE              13


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
