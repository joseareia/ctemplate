#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "memory.h"
#include "debug.h"
#include "common.h"
#include "client_opt.h"

struct sockaddr_in get_server_addr(const char *ip, unsigned short port);

int main(int argc, char *argv[]) {
    struct gengetopt_args_info args;

    if (cmdline_parser(argc, argv, &args) != 0) {
        exit(ERR_ARGS);
    }

    int socket_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_udp == -1) {
        ERROR(2, "socket() failed");
    }

    struct sockaddr_in server_addr = get_server_addr(args.ip_arg, args.port_arg);

    /* Loop or function --- Insert "recvfrom" and "sendto" */

    /* Example of "sendto" */
    if (sendto(socket_udp, args.UTF8_arg, strlen(args.UTF8_arg), 0,
            (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in)) == -1) {
        ERROR(3, "sendto() failed");
    }
    /* End of the example of "sendto" */

    /* Example of "recvfrom" */
    struct sockaddr_in from_addr;
    socklen_t from_addr_len = sizeof(struct sockaddr_in);

    ssize_t read_bytes;
    char response[MAX_MSG_SIZE + 1];

    if ((read_bytes = recvfrom(socket_udp, response, MAX_MSG_SIZE, 0,
            (struct sockaddr *) &from_addr, &from_addr_len)) == -1) {
        ERROR(2, "recvform() failed");
    }

    response[read_bytes] = 0;
    printf("[CLIENT] Answer '%s'\n", response);
    /* End of the example of "recvfrom" */

    if (close(socket_udp) == -1) {
        ERROR(23, "Can't close udp_client_socket (IPv4)");
    }

    cmdline_parser_free(&args);
    return 0;
}

struct sockaddr_in get_server_addr(const char *ip, unsigned short port) {
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	switch (inet_pton(AF_INET, ip, &server_addr.sin_addr.s_addr)) {
		case 0:
			fprintf(stderr, "[%s@%d] ERROR - Cannot convert IP address (IPv4): Invalid Network Address\n", __FILE__, __LINE__);
			exit(22);
		case -1:
			ERROR(22, "Cannot convert IP address (IPv4)");
	}
	server_addr.sin_port = htons(port);
    return server_addr;
}
