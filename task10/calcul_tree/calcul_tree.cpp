#include <assert.h>
#include <math.h>
#include <stdio.h>

#define CALCUL_TREE_CPP
#include "calcul_tree.h"

#define CALL_FUNC_AND_CHECK_ERR(function)\
    do{\
        function;\
        if(*err){ \
            return;                                                         \
        } \
    }while(0)

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// DSL for calculating funt

#define RES_L *left_result
#define RES_R *right_result
#define DEF_OP(Op, Result) \
static void Calc##Op(int*result, int*left_result, int*right_result){ \
    assert(result); \
    *result = (Result); \
}

DEF_OP(And, RES_L && RES_R);
DEF_OP(Or, RES_L || RES_R);

/*
* Унарные операторы со значением в левом узле - снимаем предупреждение
*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
DEF_OP(Not, !RES_L);
#pragma GCC diagnostic pop

#include "../include/operators_func.h"

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// First part of task - tree of expressions and main function for it

static void CalcTreeExpressionRecursive(metki* mtk, TreeNode_t* node,  int* result, TreeErr_t* err);

void CalcTreeExpression(TreeNode_t* node, metki* mtk, int* result, TreeErr_t* err){
    if(*err) return;
    assert(result);
    DEBUG_TREE(CALL_FUNC_AND_CHECK_ERR( *err = TreeNodeVerify(node);));
    
    CALL_FUNC_AND_CHECK_ERR(CalcTreeExpressionRecursive(mtk, node, result, err));

    DEBUG_TREE(CALL_FUNC_AND_CHECK_ERR(*err = TreeNodeVerify(node);))
}

//--------------------------------------------------------------------------------------------
// Postfix tree calculating
// After will be verifying

static void CalcExpWithOperator(TreeNode_t *node, int *result, int *left_result, int *right_result, TreeErr_t* err);

static void CalcExpWithVar(metki* mtk, TreeNode_t* node, int*result, TreeErr_t* err);

static void CalcTreeExpressionRecursive(metki* mtk, TreeNode_t* node, int*result, TreeErr_t* err){
    if(*err) return;
    assert(result);

    int left_result = 0;
    int right_result = 0;

    if(!node) return;

    if(node->type == OPERATOR){
        CALL_FUNC_AND_CHECK_ERR(CalcTreeExpressionRecursive(mtk, node->left, &left_result, err));
        CALL_FUNC_AND_CHECK_ERR(CalcTreeExpressionRecursive(mtk, node->right, &right_result, err));
    }
    switch(node->type){
        case INCORR_VAL: *err = INCORR_TYPE; return;
        case OPERATOR: CALL_FUNC_AND_CHECK_ERR(CalcExpWithOperator(node, result, &left_result, &right_result, err)); break;
        case VARIABLE: CALL_FUNC_AND_CHECK_ERR(CalcExpWithVar(mtk, node, result, err));                              break;
        default:         *err = INCORR_TYPE; return;
    }


}
//--------------------------------------------------------------------------------

static void CalcExpWithOperator(TreeNode_t* node, int*result, int*left_result, int*right_result, TreeErr_t* err){
    if(*err) return;
    assert(result); 

    size_t arr_num_of_elem = sizeof(OPERATORS_INFO) / sizeof(op_info);
    if(node->data.op >= arr_num_of_elem){
        *err = INCORR_OPERATOR;
        return;
    }
    if(OPERATORS_INFO[node->data.op].function_calc == NULL){
        *err = NULL_PTR_TO_FUNC;
        return;
    }
    OPERATORS_INFO[node->data.op].function_calc(result, left_result, right_result);
}


static void CalcExpWithVar(metki* mtk, TreeNode_t* node, int*result, TreeErr_t* err){
    if(*err) return;
    assert(mtk); assert(result);

    size_t var_idx = FindVarInMtkArr(mtk, node->data.var_name);

    if(var_idx >= mtk->num_of_metki){
        *err = INCORR_IDX_IN_MTK;
        return;
    }
    if(!mtk->var_info[var_idx].variable_name){
        *err = CANT_GET_VALUE_FOR_NULL_NAME_IN_MTK;
        return;
    }
    *result = mtk->var_info[var_idx].value;
}

//-----------------------------------------------------------------------------
// Undef dsl
#undef RES_L
#undef RES_R
#undef DEF_OP
#undef CALL_FUNC_AND_CHECK_ERR
#undef CALCUL_TREE_CPP