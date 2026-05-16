#include <stdlib.h>
#include "make_ast/io/read_program.h"
#include "make_ast/tokenizing/tokenize.h"
#include "make_ast/syntax_parse/make_tokens_tree.h"
#include "metki/metki.h"


int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Can't parse name of the file frontend\n");
        return 0;
    }

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

    char* buffer = read_file_to_string_array(argv[1]);
    if(!buffer) return 1;

    metki* mtk = MetkiInit();
    if(!mtk){
        free(buffer);
        return 1;
    }

    Tokens_t* tokens = TokenizeInput(buffer, mtk);
    if(!tokens){
        free(buffer);
        free(mtk);
        return 1;
    }

    // DEBUG FOR TOKENS
    /*
    for(int i = 0; i < tokens->num_of_nodes; i++){
        tree_dump_func(tokens->node_arr[i], __FILE__, __func__, __LINE__, "%d pos", i);
    }
    */
    TreeHead_t* head = MakeLangExprTokens(tokens);
    if(!head){
        free(buffer);
        free(mtk);
        // tokens were already deleted in  MakeLangExprTokens
        return 1;
    }

    free(head);
    TokensDtor(tokens);
    return 0;
}