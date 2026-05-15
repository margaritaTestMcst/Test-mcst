#include "parse.h"

const char* const SHORT_OPTS = "mcst";

const size_t ELBRUS_NUM = 6969;

const struct option long_options[] ={
    {"elbrus", required_argument, 0, ELBRUS_NUM}
};


static void parse_incorrect(char** argv);

static bool is_valid_elbrus(const char *value);

bool get_arguments(int argc, char** argv, ArrayAndSize* array_short, ArrayAndSize* array_long){
    int opterr = 0;
    int opt = 0;
    while((opt = getopt_long(argc, argv, SHORT_OPTS, long_options, NULL)) != -1){
        if(opt == 'm' || opt == 'c' || opt == 's' || opt == 't'){
            ArrayAndSizeInsert(array_short, &opt);
            continue;
        }
        if(opt == ELBRUS_NUM){
            if(!is_valid_elbrus(optarg)){
                fprintf(stderr, "Incorrect option: elbrus=%s", optarg);
                return false;
            }
            ArrayAndSizeInsert(array_long, optarg);
            continue;
        }

        parse_incorrect(argv);
        return false;
    }

    return true;
}

static bool is_valid_elbrus(const char *value){
    const char *valid[] = {"1c+", "2c+", "2c3", "4c", "8c", "16c"};
    size_t valid_size = sizeof(valid) / sizeof(valid[0]);

    for(size_t i = 0; i < valid_size; i++){
        if(!strcmp(valid[i], value)) return true;
    }

    return false;
}

static void parse_incorrect(char** argv){
    if(optopt != 0){
        fprintf(stderr, "Incorrect option: %c", optopt);
        return;
    }

    char* incorrect = argv[optind - 1];
    if(incorrect[0] == '-'){
        if(incorrect[1] == '-'){
            fprintf(stderr, "Incorrect option: %s", incorrect + 2*sizeof(char));
            return;
        }
        fprintf(stderr, "Incorrect option: %s", incorrect + sizeof(char));
    }

    fprintf(stderr, "Incorrect option: %s", incorrect);
}