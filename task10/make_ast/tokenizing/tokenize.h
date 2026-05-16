#ifndef TOKENIZE_H
#define TOKENIZE_H

#include "../../tree/tree.h"
#include "../common/tokens.h"
#include "../../tree/tree_func.h"
#include "../../metki/metki.h"

Tokens_t* TokenizeInput(char* buffer, metki* mtk);

#endif //TOKENIZE_H