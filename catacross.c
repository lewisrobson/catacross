/* Author: Lewis Robson */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include "padding.h"
#define DEBUG printf

int main(int argc, char* argv[])
{
//test();
//exit(0);
if(argv[1] == NULL){
    printf("expected arguments: file[1] file[2], -h for more info\n");
    exit(1);
}



if(strcmp(argv[1],"-h") == 0){ //add or --help
    printf("USAGE: catacross [left-file] [right-file] [Options]\n"
           "DESCRIPTION: combine strings on each line from "
           "left, then right file one at a time E.G. \n\n"
           "[file 1]:\n-line 1: this\n-line 2: an \n\n"
           "[file 2]:\n-line 1: is \n-line 2: example \n\n"
           "[output file]\n-line 1: this is\n"
           "-line 2: an example \n\n"
           "OPTIONS:\n-h: Help Menu\n-o: Output file name\n"
           "EXAMPLES: catacross left.txt right.txt -o output.txt\n\n");
    exit(0); 
}

char *output_file_name = (char*) malloc(sizeof(char) * 256);
strncpy(output_file_name, "output.txt", 256);

if(strcmp(argv[1], "-o") == 0){
    printf("\n-o specified in wrong place, please put at the end\nEXAMPLE: catacross left.txt right.txt -o output.txt\n\n");
    exit(0);
}

//custom output name check to go here <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

if(argv[3] != NULL){
if(strcmp(argv[3], "-o") == 0){
    if(argv[4] == NULL){
        printf("please enter output file name\n");
        exit(0);
    }
    strncpy(output_file_name, argv[4], 256);
}
    else{
    printf("expected two files only\n");
    exit(2);
}
}

//########################################################################
// get file pointer sizes for later uses
size_t left_total = 0;
size_t right_total = 0;
FILE *fp_left, *fp_right, *fp_left_backup, *fp_right_backup;


//create file pointers
fp_left = fopen(argv[1], "r");
if(fp_left == NULL){
    printf("error opening file %s\n", argv[1]);
    //fclose(fp_left);
    exit(1);
}

fp_right = fopen(argv[2], "r");
if(fp_right == NULL){
    printf("error opening file %s\n", argv[2]);
    //fclose(fp_right);
    exit(1);
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


//########################################################################
// padding
/*       here, we check if the files are not equal size, If they aren’t, prompt the user 
    for input to take a backup, attempt to automatically create, if the file name we are 
 going for exists, prompt the user for an absolute path and a filename, see example text
We then read from the left and right file pointers and write them to left and right file 
pointers named backup */

if(left_total != right_total){
    printf("Files not same size, unexpected results may occur, do you want "
            "to pad the file with less lines by adding some blank lines?\n"
            "[y][Y] / [n][N]\n");
    char user_selection[2];
    scanf("%s", user_selection);
    if((strcmp(user_selection, "y") == 0) || strcmp(user_selection, "Y") == 0){
        printf("Okay, lets take some backups first\n");
        //do backup of fp_left and fp_right
        char left_backup[256] = {0};
        char right_backup[256] = {0};
        strcat(left_backup, argv[1]);
        strcat(right_backup, argv[2]);
        strcat(left_backup, ".bak");
        strcat(right_backup, ".bak");
        
        int loop = 1;
        if(access(left_backup, F_OK) != -1){
            printf("file %s exists\n", left_backup);
            while(loop == 1){
            printf("please enter a new name and specify a full path name\nEXAMPLE: /tmp/leftfile.bak\n");
            scanf("%s", left_backup);
            if(access(left_backup, F_OK) != -1){
            printf("file %s exists\n", left_backup);
            }
            else{
                printf("breaking left loop\n");
                loop = 0;
            } } }


            if(access(right_backup, F_OK) != -1){
            printf("file %s exists\n", right_backup);
            loop = 1;
            while(loop == 1){
            printf("please enter a new name and specify a full path name\nEXAMPLE: /tmp/rightfile.bak\n");
            scanf("%s", right_backup);
            if(access(right_backup, F_OK) != -1){
            printf("file %s exists\n", right_backup);
            }
            else{
                printf("breaking right loop\n");
                loop = 0;
            } } }



            // read from fp_left and write into fp_left_backup
            fp_left = fopen(argv[1], "r");
            if(fp_left == NULL){
                printf("error opening file %s\n", argv[1]);
                //fclose(fp_left);
                exit(1);
            }
            fp_left_backup = fopen(left_backup, "w");
            if(fp_left_backup == NULL){
                printf("error opening file %s\n", left_backup);
                //fclose(fp_left_backup);
                exit(1);
            }
            char buffer [1024];
            size_t bytes_read;
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp_left)) >0)
            {
                fwrite(buffer, 1, bytes_read, fp_left_backup);
            }
            fclose(fp_left_backup);
            fclose(fp_left);
            //     create backup file with new path
            //copy from fp_left into fp_left_backup

            //read from fp_right and write into fp_right_backup
            fp_right = fopen(argv[2], "r");
            if(fp_right == NULL){
                printf("error opening file %s\n", argv[2]);
                //fclose(fp_right);
                exit(1);
            }
            fp_right_backup = fopen(right_backup, "w");
            if(fp_right_backup == NULL){
                printf("error opening file %s\n", right_backup);
                //fclose(fp_right_backup);
                exit(1);
            }
        
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp_right)) >0){
                fwrite(buffer, 1, bytes_read, fp_right_backup);
            }
            fclose(fp_right_backup);
            fclose(fp_right);
            printf("fp right closed\n");
         

    }


        if((strcmp(user_selection, "n") == 0) || strcmp(user_selection, "N") == 0){
        printf("Okay, proceeding...\n");
        }
}

/////////////// do the padding <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
padding(left_total, right_total, &argv[0]);
//########################################################################
// re open file descriptors to undertake the actual merging

fp_left = fopen(argv[1], "r");
if(fp_left == NULL){
    printf("error opening file %s\n", argv[1]);
}
fp_right = fopen(argv[2], "r");
if(fp_right ==NULL){
    printf("error opening file %s\n", argv[2]);
}


// main essentially starts here  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//define 2D array's to store multiple strings
char left_items[left_total][256];
char right_items[right_total][256];

/* these next two loops loop through each line of the file_pointer(s)
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

//file pointer for the combined strings to be output to below
FILE *fp_output;
fp_output = fopen(output_file_name, "w");
free(output_file_name);
if(fp_output == NULL){
    printf("error creating output file\n");
    exit(4);
}


/* this loop adds a space to the end of the left string 
then concatenates the left and right strings together */
int j = 0;
while(j < left_total){
    /*   this if statement checks if there is a blank line
    if there is, then it doesnt append a space to the line */
    if(strncmp(left_items[j], "\n", 2) == 0){
        strcat(left_items[j], right_items[j]);
        fputs(left_items[j], fp_output);
    j++;
    }
    else{
    strcat(left_items[j], " ");
    strcat(left_items[j], right_items[j]);
    fputs(left_items[j], fp_output);
    j++;
    }
}
fclose(fp_output);

printf("\a");
return 0;
}
