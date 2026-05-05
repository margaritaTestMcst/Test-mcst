#include "merge.h"

static void* MergeTtheadFunc(void* arg);

static void append_data(int *dst, long *dst_idx, int *src, long *src_idx, long end);

static void merge(int *arr, int *tmp, long left_begin, long medium, long right_end);

// В дальнейшем можно попробовать не убивать потоки, так ак пока есть накладные расходы на создание/освобождение потоков

void ParallelMergeAllParts(ArrayAndSize *array_size, int *tmp, long *bounds, long parts_count){

    long current_parts = parts_count;
    while(current_parts > 1){
        long merge_tasks = current_parts / 2;

        pthread_t* thread_id = calloc(merge_tasks,sizeof(pthread_t));
        if(!thread_id){
            fprintf(stderr, "Error: can't allocate pthread_t* thread_id in merge\n");
            return;
        }

        MergeThreadTask* tasks = calloc(merge_tasks,sizeof(MergeThreadTask));
        if(!tasks){
            fprintf(stderr, "Error: can't allocate MergeThreadTask* tasks\n");
            free(thread_id);
            return;
        }

        for(long i = 0; i < merge_tasks; i++){
            tasks[i].arr = array_size->array;
            tasks[i].tmp = tmp;
            tasks[i].left = bounds[2 * i];
            tasks[i].middle = bounds[2*i + 1];
            tasks[i].right = bounds[2*i + 2];

            pthread_create(&thread_id[i],NULL,MergeTtheadFunc,&tasks[i]);
        }

        for(long i = 0; i < merge_tasks; i++){
            pthread_join(thread_id[i], NULL);
        }

        free(thread_id);
        free(tasks);

        long bounds_start_idx = 1;
        for(long i = 0; i < current_parts - 1; i += 2){
            bounds[bounds_start_idx] = bounds[i + 2];
            bounds_start_idx++;
        }
        if(current_parts % 2 != 0){
            bounds[bounds_start_idx] = bounds[current_parts];
            bounds_start_idx++;
        }
        current_parts = bounds_start_idx - 1;

    }
}


static void* MergeTtheadFunc(void* arg){
    MergeThreadTask* task = (MergeThreadTask*)arg;

    merge(task->arr,task->tmp,task->left,task->middle,task->right);

    return NULL;
}


static void append_data(int *dst, long *dst_idx, int *src, long *src_idx, long end){
    while (*src_idx < end) {
        dst[*dst_idx] = src[*src_idx];
        (*dst_idx)++;
        (*src_idx)++;
    }
}

static void merge(int *arr, int *tmp, long left_begin, long medium, long right_end){
    long arr_left = left_begin, arr_right = medium, tmp_left = left_begin;

    while(arr_left < medium && arr_right < right_end){
        if(arr[arr_left] <= arr[arr_right]){
            tmp[tmp_left] = arr[arr_left];
            tmp_left++;
            arr_left++;
            continue;
        } 
        tmp[tmp_left] = arr[arr_right];
        tmp_left++;
        arr_right++;
    }

    append_data(tmp, &tmp_left, arr, &arr_left, medium);
    append_data(tmp, &tmp_left, arr, &arr_right, right_end);

    for(long idx = left_begin; idx < right_end; idx++) {
        arr[idx] = tmp[idx];
    }
}
