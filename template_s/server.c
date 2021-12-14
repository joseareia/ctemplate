#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "debug.h"
#include "common.h"
#include "server_opt.h"

int bind_udp_server(unsigned short port);
struct sockaddr_in get_addr_for_all_interfaces(unsigned short port);
void handle_request(int sockfd);

int main(int argc, char *argv[]) {
    struct gengetopt_args_info args;

    if (cmdline_parser(argc, argv, &args) != 0) {
        exit(ERR_ARGS);
    }

    int udp_server_socket;
	if ((udp_server_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        ERROR(31, "Can't create udp_server_socket (IPv4)");
    }

    if (args.port_arg < 1 || args.port_arg > USHRT_MAX) {
        fprintf(stderr, "Invalid port range. Valid values: 1 - %hu\n", USHRT_MAX);
        exit(1);
    }

    int sockfd = bind_udp_server(args.port_arg);
    if (sockfd == -1) {
        exit(1);
    }

    printf("[INFO] Listening on the port: %d\n", args.port_arg);

    /* Handle request with a loop or a function --- Insert "recvform" and "sendto" */

    /* Example of a function "handle_request" at main@line:57 */
    handle_request(sockfd);
    /* End of the example function "handle_request" */

    if (close(udp_server_socket) == -1) {
        ERROR(33, "Can't close udp_server_socket (IPv4)");
    }

    cmdline_parser_free(&args);
    return 0;
}

void handle_request(int sockfd) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_lenght = sizeof(struct sockaddr_in);

    ssize_t read_bytes, sent_bytes;
    char message[MAX_MSG_SIZE + 1];

    if ((read_bytes = recvfrom(sockfd, message, MAX_MSG_SIZE, 0,
            (struct sockaddr *) &client_addr, &client_addr_lenght)) == -1) {
        ERROR(2, "recvform() failed");
    }

    message[read_bytes] = 0;
    printf("[SERVER] %lu bytes received ('%s')\n", read_bytes, message);

    char response[MAX_MSG_SIZE];
    sprintf(response, "Number of symbols: %d", symbol);

    if ((sent_bytes = sendto(sockfd, response, strlen(response), 0,
            (struct sockaddr *) &client_addr, client_addr_lenght)) == -1) {
        ERROR(3, "sendto() failed");
    }

    printf("[SERVER] Sending answer to client\n");
    printf("[SERVER] Answer sent to client (%lu bytes)\n", strlen(response));
}

int bind_udp_server(unsigned short port) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        WARNING("socket() failed");
        return -1;
    }

    struct sockaddr_in addr = get_addr_for_all_interfaces(port);
    if (bind(sockfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1) {
        WARNING("bind() failed");
        close(sockfd);
        return -1;
    }

    return sockfd;
}

struct sockaddr_in get_addr_for_all_interfaces(unsigned short port) {
    struct sockaddr_in addr;

    memset(&addr, 0, sizeof(struct sockaddr_in));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    return addr;
}
