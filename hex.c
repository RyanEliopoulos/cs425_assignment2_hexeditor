#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>



FILE* writePrep(int, char*, char*);
void writeBytes(FILE*, char []);

int main(int argc, char* argv[]) {
    
    // Arg check, open file, fseek offset, 
    FILE *binaryfile = writePrep(argc, argv[1], argv[3]); 

    writeBytes(binaryfile, argv[2]);

    fclose(binaryfile);

    return 0;
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


// Caller responsible for pre-positioning file offset
void writeBytes(FILE *binaryfile, char machine_code[]) {


    /*
 *   Need to check user input and make sure the # of bytes of machineCode 
 *   is an integer.  
 *   Program accepts hex strings. 
 *   May need to prepend 0 onto the machine code
 *
 * */

    // Staging prepending variables
    char evenified_mc[strlen(machine_code)+2];
    evenified_mc[0] = '\0';
    printf("even string:<%s>\n", evenified_mc);

    /* Check if prepending is necessary */
    if ((strlen(machine_code) % 2) == 1) {
        printf("Need to evenify the string\n");
        evenified_mc[0] = '0';
        evenified_mc[1] = '\0';
    }
    /* utilize evenified_mc regardless of mod result (to simplify things.) */
    strcat(evenified_mc, machine_code);
    printf("our new string: <%s>\n", evenified_mc);

    /* At this stage evenified_mc is the machine code string to use. */
    /* Preparing to loop through machine code */
    unsigned long int chars_remaining = strlen(evenified_mc);
    unsigned long int mc_index = 0;
    char hexpair[3];
    unsigned int newval;

    /* Translating ASCII string to int values, righting to file */
    while (chars_remaining > 0) {
    
        /* loading chars for sccanf */
        hexpair[0] = evenified_mc[mc_index++];
        hexpair[1] = evenified_mc[mc_index++];
        hexpair[2] = '\0';
        printf("hexpair: (%c, %c)\n", hexpair[0], hexpair[1]);
        int sscanf_ret  = sscanf(hexpair, "%x", &newval);

        printf("newval: %u\nret:%d", newval, sscanf_ret);
        if (sscanf_ret == 0) {
            printf("error reading hexpair:%c, %c\n", hexpair[0], hexpair[1]);
            printf("file state cannot be guaranteed. Terminating..\n");
            return; 
        }
        fwrite(&newval, 1, 1, binaryfile);
        chars_remaining -= 2;
    }


















        // turn argv[2] from an ASCII representation of hex values
    // to int values we can write to a file
//    int len = strlen(machine_code); 
//    unsigned int newvals[len]; 
//    char tmp;
//
//    // Trying new approach - Translate and print as we go
//    for (int i=0;i<len;i++) {
//        tmp = machine_code[i];
//        printf("character to translate %c\n", machine_code[i]);
//        int ret = sscanf(&tmp, "%x", newvals+i);
//        if (ret == 0) {
//            printf("sscanf failed to convert <%c> to int representation\n", tmp);
//            printf("File state cannot be guaranteed.\nTerminating");
//            printf("Terminating\n");
//            return;
//        }
//        printf("value in newvals: %u\nRet val: %d\n", newvals[i], ret);
//    }
//
//
//    for (int i=0;i<len;i++) {
//        printf("%u\n", newvals[i]);
//    }
    // Now writing the new binary values to the file 
    //for (int i=0;i<len;i++) {
        //ret = fwrite(&newvals[i], 1, 1, file);
        //if (ferror(file) != 0) {
         //   printf("encountered error writing binary to file\n No guarantee of file state.\n");
          //  exit(4);
       // }
    //}

}
