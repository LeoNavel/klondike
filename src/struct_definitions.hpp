/*! 
 *  \file       struct_definitions.hpp
 *  \author     Filip Klembara
 *  \author     Adrián Tomašov
 *  \date       2017
 *  \copyright GNU Public License.
 */
#ifndef STR_DEF_H
#define STR_DEF_H


typedef struct {
    int type_stack;
    int id_stack;

} stack_id_t;

typedef struct {
    stack_id_t source_stack;
    stack_id_t destination_stack;
    int num_of_cards;
} cmd_t;

#endif //STR_DEF_H