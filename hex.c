#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>


void main(int argc, char* argv[]) {

    // Check arg count
    if (argc != 4) {
        printf("[address] [machineCode] [binaryFile]\n");
        exit(1);
    }

    // Open designated binary file
    FILE *file = fopen(argv[3], "r+b");
    if (file == NULL) {
        printf("error opening file: %s\n", strerror(errno));
        exit(2);
    }

    /********* Moving to the designated file offset ********/
    // Translate hex to unsigned long int
    unsigned long memaddr;
    sscanf(argv[1], "%lx", &memaddr);
    // and adjust file to our offset 
    errno = 0;
    int ret = fseek(file, memaddr, SEEK_SET);
    if (ret == -1) {
        printf("fseek error: %s\n", strerror(errno));
        exit(3);
    } 

    /* Manual writing for debugging */
//    int jg = 127;
//    ret = fwrite(&jg, 1, 1, file);
//    if (ret != 1) {
//        printf("fwrite problem\n");
//        exit(4);
//    }
    
    // turn argv[2] from an ASCII representation of hex values
    // to int values we can write to a file
    int len = strlen(argv[2]); 
    unsigned int newvals[len]; 
    char tmp;
    
    // Trying new approach - Translate and print as we go
    for (int i=0;i<len;i++) {
        tmp = argv[2][i];
        printf("character to translate %c\n", argv[2][i]);
        ret = sscanf(&tmp, "%x", newvals+i);
        printf("value in newvals: %u\nRet val: %d\n", newvals[i], ret);
    }



    // Now writing the new binary values to the file 
    //for (int i=0;i<len;i++) {
        //ret = fwrite(&newvals[i], 1, 1, file);
        //if (ferror(file) != 0) {
         //   printf("encountered error writing binary to file\n No guarantee of file state.\n");
          //  exit(4);
       // }
    //}

    fclose(file);

}
