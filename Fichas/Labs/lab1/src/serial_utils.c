#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define FLAG 0x7E
#define A 0x03
#define C_SET 0x03
#define C_UA 0x07

char* get_cmd (int fd) {
    char c = 0;
    char* ret = malloc (sizeof(char) * 2);
    int state = 0;
    int BCC_OK = 0;

    while (1) {
        int res = read (fd, &c, 1); // reads the first char
        printf("read %x state:%d\n", c, state);
        char packet_A = '\0', packet_C = '\0';

        switch (state)
        {
        case 0: 
            if (c == FLAG) {
                state = 1; // Moves to the next "node" of the state machine, FLAG RCV
            }
            else {
                state = 0; // Stays on the same "node", the Start Node
            }
            break;
        case 1: 
            packet_A = c; // We receive the byte A here, and store it
            if (c == A) {
                state = 2; // Moves to the next "node" of the state machine, A RCV
            }
            else {
                state = 0; // Stays on the same "node", the FLAG RCV Node
            }
            break;
        case 2: 
            packet_C = c; // We receive the byte B here, and store it
            if (c == C_SET) {
                state = 3;
            }
            else {
                state = 0;
            }
            break;
        case 3: 
            if ((packet_A ^ packet_C) == c) {
                state = 4;
                BCC_OK = 1;
            }
            else {
                state = 0;
                BCC_OK = 0;
            }
            break;
        case 4: 
            if (c == FLAG) {
                // SUCCESS!!!
                ret[0] = packet_A;
                ret[1] = packet_C;
                return ret;
            }
            else {
                state = 0;
            }
            break;
        default:
            break;
        }
    }
}