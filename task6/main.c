#include "stat_dump/stat_dump.h"

int main(int argc,char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: <program> <file>\n");
        return 1;
    }

    struct stat file_info = {};

    if(stat(argv[1], &file_info) == -1){
        perror("Stat error");
        return 1;
    }

    print_stat_info(argv[1], file_info);

    return 0;
}