#include<stdio.h>
#include<string.h>






void main() {



    /*
 *   Need to check user input and make sure the byte value of machineCode 
 *   is an integer.  Program accepts hex strings, but prepending 0 may be necessary.
 *
 * */

    FILE* binaryFile = fopen("garbage", "w+b");

    char machine_code[] = "bba";
    char evenified_mc[strlen(machine_code)+2];
    evenified_mc[0] = '\0';
    printf("even string:<%s>\n", evenified_mc);

    /* Check if prepending is necessary */
    if ((strlen(machine_code) % 2) == 1) {
        printf("Need to evenify the string\n");
        evenified_mc[0] = '0';
        evenified_mc[1] = '\0';
    }
    /* utilize evenified_mc regardless of mod result to simplify things. */
    strcat(evenified_mc, machine_code);
    printf("our new string: <%s>\n", evenified_mc);


    /* At this stage evenified_mc is the machine code string to use. */
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

        fwrite(&newval, 1, 1, binaryFile);
        chars_remaining -= 2;
    }


    fclose(binaryFile);
//    char machine_code[6];
//    
//
//
//    unsigned long int chars_remaining = strlen(machine_code);       // countdown. Indicator for 1 char case
//    unsigned int i = 0;                                             // iterate through machine_code
//    char hexpair[2];
//    unsigned int newval;
//
//    while (chars_remaining > 0) {
//        
//        if (chars_remaining == 1) {
//            // edge case: We are at the end of the file and there isn't anything to read..
//            // Need to figure out of there is a next bite and we overwrite its first nibble
//            // or we are at EoF and need to 
//            char hexsingle = machine_code[i];
//            int ret = sscanf(&hexsingle, "%x", 
//        }
//        else {      // at least a pair of chars
//            hexpair[0] = machine_code[i++];
//            hexpair[1] = machine_code[i++];
//            int ret = sscanf(hexpair, "%x", &newval);
//            fwrite(&newval, 1, 1, fl); 
//            chars_remaining -= 2;
//        }
//
//    }

}
