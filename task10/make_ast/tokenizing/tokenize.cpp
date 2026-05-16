#include "tokenize.h"
#include "../../include/operators_func.h"
#include "../io/read_program.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <math.h> 

const size_t MAX_SIZE_BUFFER = 256;
uint8_t DIGIT_FOR_SKIP_SLASH_N = 2;

static void skip_space(const char* str, size_t* pos);

static bool FindOperators(Tokens_t* tokens,  const char* buffer, size_t* pos);

static bool Tokenize_Variable(Tokens_t* tokens, const char* buffer, size_t* pos, metki* mtk);

Tokens_t* TokenizeInput(char* buffer, metki* mtk){
    Tokens_t* tokens = TokensCtor(10);
    size_t pos = 0;

    while(true){
        skip_space(buffer, &pos);

        if(buffer[pos] == '\0'){
            break;
        }

        else if(FindOperators(tokens, buffer, &pos))          continue; 

        else if(Tokenize_Variable(tokens, buffer, &pos, mtk))      continue;

        else{
            TokensDtor(tokens);
            return NULL;
        }
    }
    buffer_free(buffer);
    return tokens;
}

static void skip_space(const char* str, size_t* pos){
    char ch = str[(*pos)];
    while(isspace(ch) && ch != '\0'){
        (*pos)++;
        ch = str[(*pos)];
    }
}

static bool FindOperators(Tokens_t* tokens, const char* buffer, size_t* pos){
    for(size_t idx = 1; idx < NUM_OF_OP; idx++){
        if(!OPERATORS_INFO[idx].op_name_in_code){
            continue;
        }
        if(!strncmp(buffer + *pos, OPERATORS_INFO[idx].op_name_in_code, OPERATORS_INFO[idx].num_of_symb_code)){

            TokensAddElem(NodeCtor(OPERATOR, (TreeElem_t){.op = OPERATORS_INFO[idx].op}, NULL, NULL, NULL), tokens);
            *pos += OPERATORS_INFO[idx].num_of_symb_code;
            return true;
        }
    }
    return false;
}

static bool Tokenize_Variable(Tokens_t* tokens, const char* buffer, size_t* pos, metki* mtk){
    char buffer_var = '1';
    int num_of_symb = 0;
    if(isalpha(buffer[*pos])){
        buffer_var = *(buffer + *pos);
        if(!isupper(buffer_var)) return false;

        size_t idx = MetkiAddName(mtk, buffer_var);
        TokensAddElem(NodeCtor(VARIABLE, {.var_code = idx}, NULL, NULL, NULL), tokens);

        *pos += num_of_symb;
        return true;
    }
    return false;
}