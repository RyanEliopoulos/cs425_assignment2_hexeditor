/*
 * Ryan Paulos
 * CS 425 - Digital Forensics
 * Assignment 2
 * "basically a hex editor"
 *
 *  Program requires three arguments: 
 *
 *  ARG1: hex address of memory to begin write
 *  ARG2: machine code, in hex, to write
 *  ARG3: path to binary file
 *  
 */


#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>



FILE* writePrep(int, char*, char*, char*);
void writeBytes(FILE*, char []);
int hexCheck(char []);

int main(int argc, char* argv[]) {
    
    // Arg check, open file, fseek offset, 
    FILE *binaryfile = writePrep(argc, argv[1], argv[2], argv[3]); 
    
    // Parsing and writing machine code
    writeBytes(binaryfile, argv[2]);

    fclose(binaryfile);
    return 0;
}

/* 
 *  Returns file pointer loaded at the 
 *  user-defined offset, ready for writing.  */
FILE* writePrep(int argc, char *hex_address, char *machine_code, char *filepath) {

    // Check arg count
    if (argc != 4) {
        printf("[address] [machineCode] [binaryFile]\n");
        exit(1);
    }

    // screen machineCode for invalid hex characters
    if (hexCheck(hex_address) != 0) {
        printf("Invalid [address]. Terminating..\n");
        exit(2);
    }

    if (hexCheck(machine_code) != 0) {
        printf("Invalid [machineCode]. Terminating..\n");
        exit(3);
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

    /* Check if prepending is necessary */
    if ((strlen(machine_code) % 2) == 1) {
        evenified_mc[0] = '0';
        evenified_mc[1] = '\0';
    }
    /* utilize evenified_mc regardless of mod result (to simplify things.) */
    strcat(evenified_mc, machine_code);

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
        int sscanf_ret  = sscanf(hexpair, "%x", &newval);

        if (sscanf_ret == 0) {
            printf("sscanf error on chars (%c, %c)\nFile state not guaranteed. Terminating..\n", hexpair[0], hexpair[1]);
            return; 
        }
        fwrite(&newval, 1, 1, binaryfile);
        chars_remaining -= 2;
    }
}


int hexCheck(char hexstring[]) {

    unsigned long i = 0;
    while (hexstring[i] != '\0') {
        char tmp = hexstring[i++];
        if (tmp >= 97 && tmp <= 102) continue;
        if (tmp >= 65 && tmp <= 70) continue;
        if (tmp >= 48 && tmp <= 57) continue;

        printf("<%c> isn't valid hex\n", tmp);
        return 1;
    }
    return 0; }
