/* Author: Lewis Robson */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define DEBUG printf

int main(int argc, char* argv[])
{

if(argv[1] == NULL){
    printf("expected arguments: file[1] file[2], -h for more info\n");
    exit(1);
}



if(strcmp(argv[1],"-h") == 0){
    printf("Description: take two files as input, [left] and [right]\n"
           "combine the strings on each line from the "
           "left, then the right file E.G. \n\n"
           "[file 1]: -line 1: this -line 2: an \n"
           "[file 2]: -line 1: is -line 2: example \n"
           "[combined.txt] -line 1: this is "
           "-line 2: an example \n\n");
    exit(0); 
}

if(argv[3] != NULL){
    printf("expected two files only\n");
    exit(2);
}


size_t left_total = 0;
size_t right_total = 0;
FILE *fp_left, *fp_right;


//create file pointers
fp_left = fopen(argv[1], "r");
if(fp_left == NULL){
    printf("error opening file %s\n", argv[1]);
}

fp_right = fopen(argv[2], "r");
if(fp_right == NULL){
    printf("error opening file %s\n", argv[2]);
}

//get left_total && right_total for use later on
char string[256];
while(fgets(string, sizeof(string), fp_left)){
left_total++;
}
fclose(fp_left);

while(fgets(string, sizeof(string), fp_right)){
right_total++;
}
fclose(fp_right);


if(left_total != right_total){
    printf("Files not same size, program "
    "not intended to be used this way\n");
    exit(3);
}

//re open closed file descriptors so we are back at start
fp_left = fopen(argv[1], "r");
if(fp_left == NULL){
    printf("error opening file %s\n", argv[1]);
}
fp_right = fopen(argv[2], "r");
if(fp_right ==NULL){
    printf("error opening file %s\n", argv[2]);
}

//define 2D array's
char left_items[left_total][256];
char right_items[right_total][256];

/*these next two loops loop through each line of the file_pointer(s)
the strtok is to remove the \n character from the left side file, the
string pulled out of the file is then assigned to item i of the array */
int i = 0;
while(fgets(string, sizeof(string), fp_left)){
strtok(string, "\n");
strncpy(&left_items[i][0], string, 256);
i++;
}
fclose(fp_left);

i = 0;
while(fgets(string, sizeof(string), fp_right)){
strncpy(&right_items[i][0], string, 256);
i++;
}
fclose(fp_right);

//file pointer for the combined strings to be output to
FILE *fp_output;
fp_output = fopen("combined.txt", "w");
if(fp_output == NULL){
    printf("error creating output file\n");
    exit(4);
}


/* this loop adds a space to the end of the left string 
then concatenates the left and right strings together */
int j = 0;
while(j < left_total){
    strcat(left_items[j], " ");
    strcat(left_items[j], right_items[j]);
    fputs(left_items[j], fp_output);
    j++;
}
fclose(fp_output);

return 0;
}
