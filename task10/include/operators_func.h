#ifndef OPERATOR_FUNC_H
#define OPERATOR_FUNC_H
#include <string.h>
#include "../tree/tree.h"
#include <stdio.h>

#ifdef CALCUL_TREE_CPP
    #define CALCUL(...) __VA_ARGS__
#else 
    #define CALCUL(...)
#endif //CALCUL_TREE_CPP

struct op_info{
    // reading from file
    OPERATORS op;
    const char* op_name_in_code;
    size_t num_of_symb_code;
    // dump
    const char* name_for_graph_dump;
    // calcul
    CALCUL(void(*function_calc)(int* result, int* left_result, int* right_result);)
};

const op_info OPERATORS_INFO[] = {
    {INCORR,NULL,  0,  NULL,     CALCUL(NULL)},
    {OP_AND,         "AND",                     sizeof("AND")                     - 1,  "OP_AND",  CALCUL(CalcAnd)},
    {OP_OR,          "OR",                      sizeof("OR")                      - 1,  "OP_OR",  CALCUL(CalcOr)},
    {OP_NOT,         "NOT",                     sizeof("NOT")                     - 1,  "OP_NOT",  CALCUL(CalcNot)},
    {OP_OPEN_BR,     "(",                       sizeof("(")                       - 1,  "OP_OB",  CALCUL(NULL)},
    {OP_CLOSE_BR,    ")",                       sizeof(")")                       - 1,  "OP_CB",  CALCUL(NULL)}
};

const size_t NUM_OF_OP = sizeof(OPERATORS_INFO) / sizeof(op_info); 

typedef uint64_t Op_info_mistake_t;

Op_info_mistake_t find_operators_info_mistake();

enum OPERATORS_INFO_MISTAKES{
    NO_MISTAKE_OP,
    INDEX_AND_OP_NOT_SIMMILAR,
    INCORR_LEN
};



#endif //OPERATOR_FUNC_H