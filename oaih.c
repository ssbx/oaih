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
#define FORM_MAX 1000
#define PAYLOAD_MAX 100000

void
printUsageAndExit() {
    printf("Usage example: oaih --host=\"www.example.com\" --port=\"80\" --location=\"/somewere/request\"");
    printf("\n\nOptions:\n");
    printf("\t--verb   Default to \"ListRecords\"\n");
    printf("\t--metadataPrefix   Default to \"oai_dc\"\n");
    exit(EXIT_FAILURE);
}

/*
 *
 */
int
main(int argc, char** argv) {
    int socket;
    char payload[PAYLOAD_MAX + 1], request[REQUEST_MAX + 1], form[FORM_MAX + 1];
    char *location, *host, *port, *verb, *metaprefix;
    char form_tpl[] = "?verb=%s;metadataPrefix=%s";
    char request_tpl[] =
            "GET %s%s HTTP/1.0\r\n"
            "Host: %s\r\n\r\n";


    host = cargoFlag("hostname", NULL, argc, argv);
    if (host == NULL) {
        printUsageAndExit();
    }

    location = cargoFlag("location", NULL, argc, argv);
    if (location == NULL) {
        printUsageAndExit();
    }

    port = cargoFlag("port", NULL, argc, argv);
    if (port == NULL) {
        printUsageAndExit();
    }
    verb = cargoFlag("verb", "ListRecords", argc, argv);
    metaprefix = cargoFlag("metadataPrefix", "oai_dc", argc, argv);

    if (snprintf(form, FORM_MAX, form_tpl, verb, metaprefix) < 0) {
        printUsageAndExit();
    }

    if (snprintf(request, REQUEST_MAX, request_tpl, location, form, host) < 0) {
        printUsageAndExit();
    }

    if ((socket = netdial(TCP, host, atoi(port))) < 0) {
        printUsageAndExit();
    }

    printf("request: %s\n", request);
    // write http request
    if (write(socket, request, strlen(request)) >= 0) {
        // Read reply
        while (read(socket, payload, PAYLOAD_MAX) > 0) {
            printf("%s", payload);
        }
    }

    closesocket(socket);

    return (EXIT_SUCCESS);
}
