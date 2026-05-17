#include <assert.h>
#include <unistd.h>
#include "write.h"

static void append_symbol(char* buffer, size_t* pos, char symb);

static void append_digit(char* buffer, sig_atomic_t value, size_t* pos);

static void append_idx(char* buffer, size_t* pos, sig_atomic_t value1, sig_atomic_t value2);

void write_idx(sig_atomic_t i, sig_atomic_t j, sig_atomic_t k){
    char buffer[100] = {};
    size_t pos = 0;

    append_idx(buffer, &pos, i + 1, k + 1);
    append_idx(buffer, &pos, k + 1, j + 1);
    append_idx(buffer, &pos, i + 1, j + 1);

    write(STDOUT_FILENO, buffer,pos);
}

static void append_symbol(char* buffer, size_t* pos, char symb){
    assert(buffer);
    assert(pos);

    buffer[*pos] = symb;
    (*pos)++;
}

static void append_digit(char* buffer, sig_atomic_t value, size_t* pos){
    assert(buffer);
    assert(pos);
    
    char tmp[10] = {};
    int cnt = 0;

    if(value == 0){
        append_symbol(buffer, pos, '0');
        return;
    }

    while(value > 0){
        tmp[cnt] = '0' + value % 10;
        cnt++;
        value = value / 10;
    }

    for(int i = 0; i < cnt; i++){
        append_symbol(buffer, pos, tmp[cnt - i - 1]);
    }
}

static void append_idx(char* buffer, size_t* pos, sig_atomic_t value1, sig_atomic_t value2){
    assert(buffer);
    assert(pos);

    append_digit(buffer, value1, pos);
    append_symbol(buffer, pos, ' ');
    append_digit(buffer, value2, pos);
    append_symbol(buffer, pos, '\n');
}
