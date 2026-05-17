#include "handlers.h"
#include "../write_char/write.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>

static volatile sig_atomic_t idx_i = 0;
static volatile sig_atomic_t idx_j = 0;
static volatile sig_atomic_t idx_k = 0;

void update_idx(int i, int j, int k){
    idx_i = i;
    idx_j = j;
    idx_k = k;
}

// Sigint -------------------------------------------------------

static void signal_sigint_handler(int signum){
    write_idx(idx_i, idx_j, idx_k);

    signal(SIGINT, SIG_DFL);
}

__attribute__((always_inline))
static void set_sigint_signal(){
    signal(SIGINT, signal_sigint_handler);
}

// -----------------------------------------------------------
// Sigaction -------------------------------------------------

static void sigaction_sigint_handler(int signum){
    write_idx(idx_i, idx_j, idx_k);

    struct sigaction sa = {};

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
}

static void set_sigaction_signal(){
    struct sigaction sa = {};

    sa.sa_handler = sigaction_sigint_handler; 
    sigemptyset(&sa.sa_mask);      
    sa.sa_flags = 0;              

    sigaction(SIGINT, &sa, NULL);
}

// -----------------------------------------------------------

bool choose_handler_mode(const char* string){
    assert(string);

    if(!strcmp(string, "--signal")){
        set_sigint_signal();
        return true;
    }

    if(!strcmp(string, "--sigaction")){
        set_sigaction_signal();
        return true;
    }

    return false;
}

// -----------------------------------------------------------