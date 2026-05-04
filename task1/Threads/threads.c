#include "threads.h"
#include <assert.h>

long ChooseNumOfThreads(ArrayAndSize* array_size, int threads){
    assert(array_size);

    if(threads <= 1 || array_size->size < 2){
        return 1;
    }

    if(threads > 16){
        return 16; //на моем процессоре 16 ядер, и желательно не допускать, чтобы потоков было сильно больше, чем ядер
    }

    int size_div_two = array_size->size / 2;
    if(threads > size_div_two){
        return size_div_two; // нужно чтобы базово в самом минимальном подмассиве было 2 элемента
    }

    return threads;
}