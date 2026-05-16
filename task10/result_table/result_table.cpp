#include <assert.h>
#include "result_table.h"

static int cmp_variables(const void* a, const void* b){
    const variables* x = (const variables*)a;
    const variables* y = (const variables*)b;

    return x->variable_name - y->variable_name;
}

static void print_header(metki* mtk){
    assert(mtk);
    for(size_t i = 0; i < mtk->first_free; i++){
        printf("%c ", mtk->var_info[i].variable_name);
    }

    printf("Result\n");
}

bool print_table(TreeHead_t* head, metki* mtk){
    assert(head);
    assert(head->root);
    assert(mtk);

    qsort(mtk->var_info, mtk->first_free, sizeof(variables), cmp_variables);
    print_header(mtk);

    size_t mtk_size = mtk->first_free;
    unsigned long long rows = 1 << mtk_size;

    for(unsigned long long mask = 0; mask < rows; ++mask){
        for(size_t i = 0; i < mtk_size; i++){
            mtk->var_info[i].value = (mask >> (mtk_size - 1 - i)) & 1;
            printf("%d ", mtk->var_info[i].value);
        }

        int result = 0;
        TreeErr_t err = NO_MISTAKE;
        CalcTreeExpression(head->root, mtk, &result, &err);
        if(err) return false;

        printf("%d\n", result);
    }

    return true;
}