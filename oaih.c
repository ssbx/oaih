/*
 * File:   oaih.c
 * Author: Sébastien Serre <sserre at msha.fr>
 *
 * Created on 27 février 2017, 16:58
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <clog.h>
#include <cargo.h>
#include <net.h>

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
    netsocket socket;
    char payload[PAYLOAD_MAX + 1], request[REQUEST_MAX + 1], form[FORM_MAX + 1];
    char *location, *host, *port, *verb, *metaprefix;
    char form_tpl[] = "?verb=%s;metadataPrefix=%s";
    char request_tpl[] =
            "GET %s%s HTTP/1.0\r\n"
            "Host: %s\r\n\r\n";


    host = cargoFlag("host", NULL, argc, argv);
    if (host == NULL) {
        printf("missing hostname\n");
        printUsageAndExit();
    }

    location = cargoFlag("location", NULL, argc, argv);
    if (location == NULL) {
        printf("missing location\n");
        printUsageAndExit();
    }

    port = cargoFlag("port", NULL, argc, argv);
    if (port == NULL) {
        printf("missing port\n");
        printUsageAndExit();
    }
    verb = cargoFlag("verb", "ListRecords", argc, argv);
    metaprefix = cargoFlag("metadataPrefix", "oai_dc", argc, argv);

    if (snprintf(form, FORM_MAX, form_tpl, verb, metaprefix) < 0) {
        printf("wrong form\n");
        printUsageAndExit();
    }

    if (snprintf(request, REQUEST_MAX, request_tpl, location, form, host) < 0) {
        printf("wrong request\n");
        printUsageAndExit();
    }

    socket = netdial(NET_TCP, host, atoi(port));
    if (socket.fd < 0) {
        printf("error socket %i",socket.status);
        closenetsocket(socket);
        printUsageAndExit();
    }

    printf("request: %s\n", request);
    // write http request
    if (netwrite(socket, request, strlen(request)) >= 0) {
        // Read reply
        while (netread(socket, payload, PAYLOAD_MAX) > 0) {
            printf("%s", payload);
        }
    }

    closenetsocket(socket);

    return (EXIT_SUCCESS);
}
