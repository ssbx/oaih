/*
 * File:   oaih.c
 * Author: Sébastien Serre <sserre at msha.fr>
 *
 * Created on 27 février 2017, 16:58
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xml.h>
#include <clog.h>
#include <cargo.h>
#include <ssock.h>

#define REQUEST_MAX 1000
#define PAYLOAD_MAX 100000

void
printUsageAndExit() {
    printf("Usage: oaih --url=\"http://www.example.com/bla\"");
    exit(EXIT_FAILURE);
}

/*
 *
 */
int
main(int argc, char** argv) {
    int fd, count;
    char payload[PAYLOAD_MAX + 1], request[REQUEST_MAX + 1];
    char request_tpl[] =
            "GET %s HTTP/1.0\r\n"
            "Host: %s\r\n\r\n";
    char* url, location, host, port;

    url = cargoFlag("url", NULL, argc, argv);
    if (url == NULL) {
        printUsageAndExit();
    }
    location = parseurl(url, LOCATION_TYPE);
    if (location == NULL) {
        printUsageAndExit();
    }
    host = parseurl(url, HOST_TYPE);
    if (host == NULL) {
        printUsageAndExit();
    }
    port = parseurl(url, PORT_TYPE);
    if (port == NULL) {
        printUsageAndExit();
    }

    if (sprintf(request, (size_t) REQUEST_MAX, request_tpl, host, location) < 0) {
        printUsageAndExit();
    }

    if ((fd = netdial(TCP, *host, atoi(port))) < 0) {
        printUsageAndExit();
    }

    // write http request
    if (write(fd, request, strlen(request)) >= 0) {
        // Read reply
        while ((count = read(fd, payload, PAYLOAD_MAX)) > 0) {
            printf("%s", payload);
        }
    }

    return (EXIT_SUCCESS);
}
