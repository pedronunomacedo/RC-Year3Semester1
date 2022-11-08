#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <regex.h>

#define HOST_REGEX "%*[^/]//%*[^@]@%[^/]"
#define PATH_REGEX "%*[^/]//%*[^/]%s"
#define USER_REGEX "%*[^/]//%[^:]"
#define PASSWORD_REGEX "%*[^/]//%*[^:]:%[^@]"

int main (int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: ./download <FILE>\n");
        exit(0);
    }

    char host[strlen(argv[1])];
    char path[strlen(argv[1])];
    char user[strlen(argv[1])];
    char pass[strlen(argv[1])];

    sscanf(argv[1], HOST_REGEX, host);
    sscanf(argv[1], PATH_REGEX, path);
    sscanf(argv[1], USER_REGEX, user);
    sscanf(argv[1], PASSWORD_REGEX, pass);


    printf("Hostname: %s\n", host);
    printf("Path: %s\n", path);
    printf("User: %s\n", user);
    printf("Password: %s\n", pass);

    return 0;
}