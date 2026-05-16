#ifndef PARSE_H
#define PARSE_H

#include "../Array/array.h"
#include <bits/getopt_core.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool get_arguments(int argc, char** argv, ArrayAndSize* array_short, ArrayAndSize* array_long);

#endif //PARSE_H