#include "merge.h"

static void append_data(int *dst, long *dst_idx, int *src, long *src_idx, long end);

static void merge(int *arr, int *tmp, long left_begin, long medium, long right_end);

void merge_all_parts(ArrayAndSize *array_size, int *tmp, long *bounds, int parts_count){
    while(parts_count > 1){
        int new_parts_count = 0;

        for(int idx = 0; idx < parts_count; idx += 2){
            long left_begin = bounds[idx];

            if(idx + 1 < parts_count){
                long middle = bounds[idx + 1];
                long right_end = bounds[idx + 2];

                merge(array_size->array, tmp, left_begin, middle, right_end);

                bounds[new_parts_count] = left_begin;
                new_parts_count++;
                bounds[new_parts_count] = right_end;
                continue;
            } 
            long right_end = bounds[idx + 1];

            bounds[new_parts_count] = left_begin;
            new_parts_count++;
            bounds[new_parts_count] = right_end;
        }

        parts_count = new_parts_count;
    }
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

    append_data(tmp, &right_end, arr, &arr_right, medium);
    append_data(tmp, &right_end, arr, &arr_right, right_end);

	for(long idx = left_begin; idx < right_end; idx++){
    	arr[idx] = tmp[idx];
	}

}
