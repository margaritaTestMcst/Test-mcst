#ifndef HANDLERS_H
#define HANDLERS_H
#include <signal.h>
#include <stdbool.h>

void update_idx(int i, int j, int k);

bool choose_handler_mode(const char* string);

#endif //HANDLERS_H