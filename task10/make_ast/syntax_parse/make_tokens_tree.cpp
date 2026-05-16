#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "make_tokens_tree.h"

// -------------------------------------------------------------------------------------
// Define lib

#define RED                        "\033[1;31m"
#define GREEN                      "\033[0;32m"
#define RESET                      "\033[0m"

#define CALL_AND_CHECK_ERR(function)\
    do{\
        function;\
        if(*err){ \
            return NULL;                                                         \
        } \
    }while(0)

#define CHECK_PARSING_ERR(bad_condition, val)\
    do{\
    *err = (bad_condition);\
        if(*err){ \
            return val; \
        } \
    }while(0) \

#define FAIL_IF(bad_condition, err_code, is_in_end_of_str)\
    if(bad_condition){ \
        *err = err_code; \
        return NULL; \
    } \

//-------------------------------------------------------------------------------------
// DSL

#define IS_TYPE_IN_POS(type_)           (*pos < tokens->first_free_place     && tokens->node_arr[*pos]     && tokens->node_arr[*pos]->type == type_)
#define IS_OPERATOR_IN_POS(op_)         (*pos < tokens->first_free_place     && tokens->node_arr[*pos]     && tokens->node_arr[*pos]->type == OPERATOR  && tokens->node_arr[*pos]->data.op == op_)

// -------------------------------------------------------------------------------------

/*
    G       ::= E
    E       ::= OR_EXPR
    OR_EXPR ::= AND_EXP{[OR]AND_EXP}*
    AND_EXP ::= NOT_EXP{[AND] NOT_EXP}*
    NOT_EXP ::=  NOT NOT_EXP | P
    P       ::= '(' E ')' | V
*/

static TreeNode_t* GetG  (size_t* pos, Tokens_t* tokens);
static TreeNode_t* GetE  (size_t* pos, Tokens_t* tokens, SyntaxErr_t* err);
static TreeNode_t* GetAND(size_t* pos, Tokens_t* tokens, SyntaxErr_t* err);
static TreeNode_t* GetNOT(size_t* pos, Tokens_t* tokens, SyntaxErr_t* err);
static TreeNode_t* GetP  (size_t* pos, Tokens_t* tokens, SyntaxErr_t* err);
static TreeNode_t* GetV  (size_t* pos, Tokens_t* tokens, SyntaxErr_t* err);

// -------------------------------------------------------------------------------------

TreeHead_t* MakeLangExprTokens(Tokens_t* tokens){
    DEBUG_TREE(
    ErrAndMsg_mistake_t error = find_err_and_msg_mistakes();
    if(error){
        fprintf(stderr, "error %zu in synatx err table", error);
        return NULL;
    }
    )

    TreeHead_t* head = TreeCtor();
    size_t pos = 0;
    head->root = GetG(&pos, tokens);
    if(!head->root){
        return NULL;
    }

    return head;
}

// -------------------------------------------------------------------------------------
// GetG

static TreeNode_t* GetG(size_t* pos, Tokens_t* tokens){
    SyntaxErr_t err = NO_MISTAKE;
    TreeNode_t* first_op = GetE(pos, tokens, &err);

    if(err || *pos != tokens->first_free_place){
        TokensDtor(tokens);
        return NULL;
    }
    assert(first_op);
    tree_dump_func(first_op, __FILE__, __func__, __LINE__ , "Before ret GetG node %zu", *pos);
    return first_op;
}


// -------------------------------------------------------------------------------------
// GetE

static TreeNode_t* GetE(size_t* pos, Tokens_t* tokens, SyntaxErr_t* err){
    if(*err) return NULL;

    TreeNode_t* left = NULL;
    CALL_AND_CHECK_ERR(left = GetAND(pos, tokens, err)); 

    while(IS_OPERATOR_IN_POS(OP_OR)){
        TreeNode_t *new_node = tokens->node_arr[*pos];

        (*pos)++; // or

        TreeNode_t* right = NULL;
        CALL_AND_CHECK_ERR(right = GetAND(pos, tokens, err));

        new_node->left = left;
        new_node->right = right;

        left->parent = new_node;
        right->parent = new_node;

        left = new_node;
    }
    assert(left);
    // tree_dump_func(left, __FILE__, __func__, __LINE__, "Before ret GetE node %zu", *pos);
    return left;
}

// -------------------------------------------------------------------------------------
// GetL

static TreeNode_t* GetAND(size_t* pos, Tokens_t* tokens, SyntaxErr_t* err){
    if(*err) return NULL;

    TreeNode_t* left = NULL;
    CALL_AND_CHECK_ERR(left = GetNOT(pos, tokens, err)); 

    while(IS_OPERATOR_IN_POS(OP_AND)){
        TreeNode_t *new_node = tokens->node_arr[*pos];

        (*pos)++; // skip + or -

        TreeNode_t* right = NULL;
        CALL_AND_CHECK_ERR(right = GetNOT(pos, tokens, err));

        new_node->left = left;
        new_node->right = right;

        left->parent = new_node;
        right->parent = new_node;

        left = new_node;
    }
    assert(left);
    // tree_dump_func(left, __FILE__, __func__, __LINE__, "Before ret GetE node %zu", *pos);
    return left;
}

//--------------------------------------------------------------------------------------
// GetNot

static TreeNode_t* GetNOT(size_t* pos, Tokens_t* tokens, SyntaxErr_t* err){
    if(*err) return NULL;
    TreeNode_t* val = NULL;

    if(IS_OPERATOR_IN_POS(OP_NOT)){
        val = tokens->node_arr[*pos];
        (*pos)++; // skip NOT

        if(IS_OPERATOR_IN_POS(OP_OPEN_BR)) (*pos)++; // skip '('

        TreeNode_t* left = NULL;
        CALL_AND_CHECK_ERR(left = GetE(pos, tokens, err));

        if(IS_OPERATOR_IN_POS(OP_CLOSE_BR)) (*pos)++; // skip ')'

        val->left = left;
        left->parent = val;
    }
    else{
        if(IS_TYPE_IN_POS(VARIABLE)){
            CALL_AND_CHECK_ERR(val = GetV(pos, tokens, err));
            (*pos)++;
        }
        else{
            FAIL_IF(true, 
                    INCORR_OPERAND_NOT_VAR_NOT_NUM, 
                    false)
        } 
    }
    // tree_dump_func(val, __FILE__, __func__, __LINE__, "Before ret GetP node %zu", *pos);
    return val;
}

// -------------------------------------------------------------------------------------
// GetP

static TreeNode_t* GetP(size_t* pos, Tokens_t* tokens, SyntaxErr_t* err){
    if(*err) return NULL;
    TreeNode_t* val = NULL;

    if(IS_OPERATOR_IN_POS(OP_OPEN_BR)){
        (*pos)++; // skip '('

        CALL_AND_CHECK_ERR(val = GetE(pos, tokens, err));

        FAIL_IF(!IS_OPERATOR_IN_POS(OP_CLOSE_BR), 
                NO_CLOSE_BRACKET_IN_MATH_EXPR, 
                true)
        (*pos)++; // skip ')'
    }
    else{
        if(IS_TYPE_IN_POS(VARIABLE)){
            CALL_AND_CHECK_ERR(val = GetV(pos, tokens, err));
            (*pos)++;
        }
        else{
            FAIL_IF(true, 
                    INCORR_OPERAND_NOT_VAR_NOT_NUM, 
                    false)
        } 
    }
    // tree_dump_func(val, __FILE__, __func__, __LINE__, "Before ret GetP node %zu", *pos);
    return val;
}


// -------------------------------------------------------------------------------------
// GetV and hrlping func

static TreeNode_t* GetV(size_t* pos, Tokens_t* tokens, SyntaxErr_t* err){
    FAIL_IF(!IS_TYPE_IN_POS(VARIABLE), 
            NO_VARIABLE, 
            false)

    return tokens->node_arr[*pos];
}

//----------------------------------------------------------------------
// UNDEF DSL

#undef IS_TYPE_IN_POS 
#undef IS_OPERATOR_IN_POS   
#undef RED
#undef GREEN           
#undef RESET  