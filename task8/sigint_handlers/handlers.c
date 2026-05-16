#include "handlers.h"

static volatile sig_atomic_t idx_i = 0;
static volatile sig_atomic_t idx_j = 0;
static volatile sig_atomic_t idx_k = 0;

void update_idx(int i, int j, int k){
    idx_i = i;
    idx_j = j;
    idx_k = k;
}