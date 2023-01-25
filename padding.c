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

//char test [2] = "\n";
//hel
printf("argv1 is %s and argv2 is %s\n", argv[1], argv[2]);
FILE* smaller_file = (FILE*) NULL;
size_t smallest_file;
size_t largest_file;

//left is smallest
if(left_total_copy < right_total_copy){
    smallest_file = left_total_copy;
    largest_file = right_total_copy;
    smaller_file = fopen(argv[1], "a");
    if (smaller_file == NULL) {
    printf("Error opening file\n");
    return -1;
    }
}
//right is smallest
else{
    smallest_file = right_total_copy;  
    largest_file = left_total_copy;
    smaller_file = fopen(argv[2], "a");
    if (smaller_file == NULL) {
    printf("Error opening file\n");
    return -1;
    }
}

printf("smallest and largest are %zu \n", smallest_file);
printf("%zu\n", largest_file);

while(smallest_file < largest_file){ 
        fputc('\n', smaller_file);
        smallest_file++;
        printf("line %zu added \n", smallest_file);
        //fputc(test[0], smaller_file);
    }
    int result = fclose(smaller_file);
    if (result == EOF) {
    printf("Error closing file\n");
    return -1;
    }


    //fclose(smaller_file);

return 0;
}
