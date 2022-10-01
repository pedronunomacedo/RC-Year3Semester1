// Application layer protocol implementation

#include "application_layer.h"
#define BUF_SIZE 256
void applicationLayer(const char *serialPort, const char *role, int baudRate,
                      int nTries, int timeout, const char *filename)
{
    // Emissor
    LinkLayer defs;
    strcpy(defs.serialPort, serialPort);
    if(strcmp(role,0)){
        defs.role = role[0]; // WRITER
    } else if(strcmp(role,1)){
        defs.role = role[1]; // WRITER
    }
    defs.baudRate = baudRate;
    defs.nRetransmissions = nTries;
    defs.timeout = timeout;

    if (llopen(defs) < 0) {
        return 1;
    }
    
    if (llwrite(filename, BUF_SIZE) < 0) {
        return 1;
    }

    


}
