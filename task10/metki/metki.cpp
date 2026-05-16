#include "metki.h"
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

metki* MetkiInit(){
    metki* mtk = (metki*)calloc(sizeof(metki), 1);
    if(!mtk){
        return NULL;
    }

    variables* metki_arr = (variables*)calloc(sizeof(variables), MAX_NUMBER_OF_METKI); 
    if(!metki_arr){
        free(mtk);
        return NULL;
    }

    mtk->num_of_metki = MAX_NUMBER_OF_METKI;
    mtk->var_info = metki_arr;
    mtk->first_free = 0;

    return mtk;
}

size_t MetkiAddName(metki* mtk, char num_of_variable){
    assert(mtk);
    assert(num_of_variable);

    mtk->var_info[mtk->first_free].variable_name = num_of_variable;
    mtk->first_free++;
    if(mtk->first_free > mtk->num_of_metki){
        if(!MetkiRealloc(mtk, mtk->num_of_metki*2)) return SIZE_MAX;
    }
    return mtk->first_free - 1;
}

bool MetkiRealloc(metki* mtk, size_t num_of_elem){
    variables* metki_arr_copy = (variables*)recallocarray(mtk->var_info, mtk->num_of_metki , num_of_elem, sizeof(variables));
    if(!metki_arr_copy){
        return false;
    }
    mtk->var_info = metki_arr_copy;
    mtk->num_of_metki = num_of_elem;
    return true;
}

size_t FindVarInMtkArr(metki* mtk, char num_of_variable){
    for(size_t metka = 0; metka < mtk->first_free; metka++){
        if(mtk->var_info[metka].variable_name == num_of_variable){
            return metka;
        }
    }
    return SIZE_MAX;
}

bool MetkiAddValue(metki* mtk, size_t idx, int value){
    assert(mtk);

    if(idx >= mtk->first_free) return false;

    mtk->var_info[idx].value = value;
    return true;
}


void MetkiDestroy(metki* mtk){
    if(mtk){
        if(mtk->var_info){
            free(mtk->var_info);
        }
        free(mtk);
    }
}