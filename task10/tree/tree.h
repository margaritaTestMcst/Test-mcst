#ifndef TREE_H
#define TREE_H
#include <cstdint>
#include <string.h>
#include <sys/types.h>

const char *const TREE_SIGNATURE = "My_tree";
const int POISON = -6666;

enum OPERATORS
{
    INCORR,
    OP_AND,
    OP_OR,
    OP_NOT,
    OP_OPEN_BR,
    OP_CLOSE_BR
};


union TreeElem_t{
    enum OPERATORS op;
    size_t var_code; 
};

#ifdef _DEBUG_SMALL_TREE
#define DEBUG_TREE(...) __VA_ARGS__
#else
#define DEBUG_TREE(...)
#endif //_DEBUG_SMALL_TREE

#define CHECK_AND_RET_TREEERR(bad_condition)\
    {\
    TreeErr_t err_ = (bad_condition);\
    if (err_)                                                                          \
    {                                                                                           \
        fprintf(stderr, "err = %lu, %s, %s, %d\n", err_, __FILE__, __func__, __LINE__); \
        return err_;                                                                   \
    }}

enum VALUE_TYPE
{
    INCORR_VAL,
    OPERATOR,
    VARIABLE
};

struct TreeNode_t
{
    VALUE_TYPE type;
    TreeElem_t data;
    TreeNode_t *left;
    TreeNode_t *right;
    TreeNode_t *parent;
    const char *signature;
};

struct TreeHead_t
{
    TreeNode_t *root;
};

#endif // TREE_H