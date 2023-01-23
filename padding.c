#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int padding(size_t left_total_copy, size_t right_total_copy, char* argv[]) //as its just a pointer, only need a copy???
{
/*
   left_total_copy:   size of items in left file
   right_total_copy: size of items in right file
*/

char test [5] = "\n";

if(left_total_copy > right_total_copy){
    //which file is big/smallest
    printf("in main\n");
    size_t largest_file = left_total_copy;
    size_t smallest_file = right_total_copy;
    //create file pointer
    FILE* smaller_file = fopen(argv[2], "a");
    //not sure append returns a null, but futureproofing?
    if(smaller_file == NULL){ 
        printf("error padding bytes into %s\n", argv[2]);
    }
    while(smallest_file < largest_file){
        printf("line %zu added \n", smallest_file);
        printf("debug, largest_file is %zu\n", largest_file);
        fputc(test[0], smaller_file);
        smallest_file++;
    }

    fclose(smaller_file);
}


if(left_total_copy < right_total_copy){
    printf("left total is %zu right is %zu\n", left_total_copy, right_total_copy);
    size_t largest_file = right_total_copy;
    size_t smallest_file = left_total_copy;
    FILE* smaller_file = fopen(argv[1], "a");
    /*if(smaller_file == NULL){
        printf("error padding bytes into %s\n", argv[1]);
    } */
    printf("debug, largest_file is %zu\n", largest_file);
     while(left_total_copy < right_total_copy){
        fputc(test[0], smaller_file);
        left_total_copy++;
        printf("line %zu added \n", left_total_copy);
        if(left_total_copy == right_total_copy){
            /* if this next line isnt in this while loop
            it causes a segmentation fault, it doesnt do
            it for the if statement above, i dont get it
            my head hurts.*/
            FILE* smaller_file = fopen(argv[1], "a");
        }
     }
}


return 0;
}
