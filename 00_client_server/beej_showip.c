/*
 * showip.c -- show IP addresses for a host given on the command line
 *
 * Reprinted from https://beej.us/guide/bgnet/examples/showip.c
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: showip hostname\n");
		return 1;
	}

	// set up hints for what we want
	struct addrinfo hints;
	memset(&hints, 0, sizeof hints);	// zero our hints but not res?
	hints.ai_family = AF_UNSPEC;		// IP agnostic
	hints.ai_socktype = SOCK_STREAM;	// TCP

	// make the call
	int status;
	struct addrinfo* res;
	if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}

	// print the results
	printf("IP addresses for %s:\n\n", argv[1]);

	for (struct addrinfo* p = res; p != NULL; p = p->ai_next) {
		void* addr;
		char* ipver;
		// get the pointer to the address itself,
		// different fields in IPv4 and IPv6:
		if (p->ai_family == AF_INET) {	// IPv4
			struct sockaddr_in* ipv4 =
				(struct sockaddr_in*)p->ai_addr;
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		} else {
			struct sockaddr_in6* ipv6 =
				(struct sockaddr_in6*)p->ai_addr;
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		// convert the IP to a string and print it:
		char ipstr[INET6_ADDRSTRLEN];	// big enough for IPv4 or IPv6
		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf("  %s: %s\n", ipver, ipstr);
	}

	freeaddrinfo(res);	// free the linked list

	return 0;
}

