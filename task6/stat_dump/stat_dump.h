#ifndef STAT_DUMP_H
#define STAT_DUMP_H

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>

void print_stat_info(const char* filename, struct stat file_info);

#endif //STAT_DUMP_H