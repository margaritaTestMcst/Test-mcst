#include <stdlib.h>
#include "make_ast/io/read_program.h"
#include "make_ast/tokenizing/tokenize.h"
#include "make_ast/syntax_parse/make_tokens_tree.h"
#include "metki/metki.h"
#include "result_table/result_table.h"

int main(){

    DEBUG_TREE(
    if(find_operators_info_mistake() || find_functions_info_mistake()){
        return 0;
    })

    /*
    size_t num = sizeof(OPERATORS_INFO) / sizeof(op_info);
    for(size_t i = 1; i < num; i++){
        fprintf(stderr, "[idx] = %zu\t op_num = %d\t op_debug = %s\n", i, OPERATORS_INFO[i].op, OPERATORS_INFO[i].name_for_graph_dump);
    }
    */

    char* buffer = read_stdin_to_string_array();
    if(!buffer) return 1;

    metki* mtk = MetkiInit();
    if(!mtk){
        free(buffer);
        return 1;
    }

    Tokens_t* tokens = TokenizeInput(buffer, mtk);
    if(!tokens){
        MetkiDestroy(mtk);
        return 1;
    }

    // DEBUG FOR TOKENS
    /*
    for(int i = 0; i < tokens->first_free_place; i++){
        tree_dump_func(tokens->node_arr[i], __FILE__, __func__, __LINE__, "%d pos", i);
    }
    */
    TreeHead_t* head = MakeLangExprTokens(tokens);
    if(!head){
        MetkiDestroy(mtk);
        // tokens and buffer were already deleted in  MakeLangExprTokens
        return 1;
    }

    if(!print_table(head, mtk)){
        free(head);
        TokensDtor(tokens);
        MetkiDestroy(mtk);
        return 1;
    }

    free(head);
    TokensDtor(tokens);
    MetkiDestroy(mtk);
    return 0;
}