#include "Array/array.h"
#include "Parse/parse.h"

void print_result(int argc, char** argv, ArrayAndSize* array_short, ArrayAndSize* array_long);

int main(int argc, char* argv[]){

    ArrayAndSize* array_short = ArrayAndSizeCtor(sizeof(char));
    ArrayAndSize* array_long = ArrayAndSizeCtor(sizeof(char*));

    bool is_parsing_correct = get_arguments(argc, argv, array_short, array_long);
    if(!is_parsing_correct){
        ArrayAndSizeDtor(array_long);
        ArrayAndSizeDtor(array_short);
        return 0;
    }

    print_result(argc, argv, array_short, array_long);

    ArrayAndSizeDtor(array_long);
    ArrayAndSizeDtor(array_short);

    return 0;
}

void print_result(int argc, char** argv, ArrayAndSize* array_short, ArrayAndSize* array_long){
    printf("Short options:");
    char* shorts = (char*)array_short->array;
    for(size_t idx=0; idx < array_short->size; idx++){
       printf(" '%c'", shorts[idx]);
    }
    printf("\n");

    printf("Long options:");
    char** longs = (char**)array_long->array;
    for(size_t idx=0; idx < array_long->size; idx++){
       printf(" 'elbrus=%s'", longs[idx]);
    }
    printf("\n");

    printf("Non options:");
    for(int idx=optind; idx < argc; idx++){
       printf(" '%s'", argv[idx]);
    }
    printf("\n");
}