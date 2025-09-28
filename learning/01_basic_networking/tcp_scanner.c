#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

enum { PORT_MIN = 1, PORT_MAX = 65535 };

static void print_usage(const char *prog)
{
	printf("Usage: %s <IP> <PORT>\n", prog);
}

static int parse_port(const char *arg)
{
	char *endptr = NULL;
	long value = strtol(arg, &endptr, 10);

	if (*arg == '\0' || *endptr != '\0') {
		fprintf(stderr, "Error: port must be a number\n");
		return -1;
	}
	if (value < PORT_MIN || value > PORT_MAX) {
		fprintf(stderr, "Error: port out of range (%d-%d)\n", PORT_MIN, PORT_MAX);
		return -1;
	}
	return (int)value;
}

static int try_connect(const struct sockaddr_in *target)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		perror("socket");
		return -1;
	}
	if (connect(sockfd, (const struct sockaddr *)target, sizeof(*target)) == 0) {
		close(sockfd);
		return 0;
	}

	switch (errno) {
		case ECONNREFUSED:
			printf("Port CLOSED (connection refused)\n");
			break;
		case ETIMEDOUT:
			printf("No response (timeout)\n");
			break;
		case ENETUNREACH:
		case EHOSTUNREACH:
			printf("Network unreachable\n");
			break;
		default:
			printf("Network error: %s\n", strerror(errno));
			break;
	}
	close(sockfd);
	return -1;
}

int main(int argc, char **argv)
{
	struct sockaddr_in target;
	int port;

	if (argc != 3) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	port = parse_port(argv[2]);
	if (port < 0)
		return EXIT_FAILURE;

	memset(&target, 0, sizeof(target));
	target.sin_family = AF_INET;
	target.sin_port = htons((uint16_t)port);

	if (inet_pton(AF_INET, argv[1], &target.sin_addr) != 1) {
		fprintf(stderr, "Error: invalid IPv4 address\n");
		return EXIT_FAILURE;
	}

	printf("Trying IP: %s Port: %d\n", argv[1], port);

	if (try_connect(&target) == 0)
		printf("Port OPEN\n");

	return EXIT_SUCCESS;
}

