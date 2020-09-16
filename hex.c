#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>



FILE* writePrep(int, char*, char*);
void writeBytes(FILE*, char *);

void main(int argc, char* argv[]) {
    
    // arg check, open file, fseek offset, 
    FILE *binaryfile = writePrep(argc, argv[1], argv[3]); 

    writeBytes(binaryfile, argv[3]);

    fclose(binaryfile);

}

/* 
 *  Returns file pointer loaded at the 
 *  user-defined offset, ready for writing.  */
FILE* writePrep(int argc, char *hex_address, char *filepath) {

    // Check arg count
    if (argc != 4) {
        printf("[address] [machineCode] [binaryFile]\n");
        exit(1);
    }

    // Open designated binary file
    FILE *filestream = fopen(filepath, "r+b");
    if (filestream == NULL) {
        printf("error opening file: %s\n", strerror(errno));
        exit(2);
    }

    /********* Moving to the designated file offset ********/
    // Translate hex to unsigned long int
    unsigned long memaddr;
    sscanf(hex_address, "%lx", &memaddr);
    // and adjust file to our offset 
    errno = 0;
    int ret = fseek(filestream, memaddr, SEEK_SET);
    if (ret == -1) {
        printf("fseek error: %s\n", strerror(errno));
        exit(3);
    } 

    return filestream; 
}

void writeBytes(FILE *binaryfile, char *machine_code) {

        // turn argv[2] from an ASCII representation of hex values
    // to int values we can write to a file
    int len = strlen(argv[2]); 
    unsigned int newvals[len]; 
    char tmp;
    
    // Trying new approach - Translate and print as we go
    for (int i=0;i<len;i++) {
        tmp = argv[2][i];
        printf("character to translate %c\n", argv[2][i]);
        int ret = sscanf(&tmp, "%x", newvals+i);
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

}
