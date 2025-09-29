#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

#define UDP_PAYLOAD "PING"
#define UDP_PAYLOAD_LEN (sizeof(UDP_PAYLOAD) - 1)
#define UDP_RESPONSE_BUFFER 1024
#define UDP_TIMEOUT_SECONDS 5

enum udp_status
{
	UDP_STATUS_ERROR = -1,
	UDP_STATUS_OK = 0,
	UDP_STATUS_TIMEOUT = 1
};

static int create_udp_socket(void);
static int configure_receive_timeout(int sockfd, time_t seconds, suseconds_t microseconds);
static ssize_t send_udp_payload(int sockfd, const struct sockaddr_in *target,
	const void *data, size_t length);
static int receive_udp_response(int sockfd, char *buffer, size_t capacity,
	ssize_t *out_length);

enum
{
	PORT_MIN = 1,
	PORT_MAX = 65535
};

void print_usage(char *name)
{
	printf("Usage: ./%s <target> <port>\n", name);
}

int parse_port(const char *av)
{
	char *endptr = NULL;
	long value = strtol(av, &endptr, 10);

	if (*av == '\0' || *endptr != '\0') {
		fprintf(stderr, "Error: port must be a number\n");
		return -1;
	}
	if (value < PORT_MIN || value > PORT_MAX) {
		fprintf(stderr, "Error: port out of range (%d-%d)\n", PORT_MIN, PORT_MAX);
		return -1;
	}
	return (int)value;
}

static int create_udp_socket(void)
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd < 0)
		perror("socket");

	return sockfd;
}

static int configure_receive_timeout(int sockfd, time_t seconds, suseconds_t microseconds)
{
	struct timeval tv = {
		.tv_sec = seconds,
		.tv_usec = microseconds,
	};

	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == -1) {
		perror("setsockopt");
		return -1;
	}

	return 0;
}

static ssize_t send_udp_payload(int sockfd, const struct sockaddr_in *target,
	const void *data, size_t length)
{
	ssize_t sent = sendto(sockfd, data, length, 0,
		(const struct sockaddr *)target, sizeof(*target));

	if (sent < 0)
		perror("sendto");

	return sent;
}

static int receive_udp_response(int sockfd, char *buffer, size_t capacity,
	ssize_t *out_length)
{
	ssize_t received = recvfrom(sockfd, buffer, capacity - 1, 0, NULL, NULL);

	if (received < 0) {
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return UDP_STATUS_TIMEOUT;

		perror("recvfrom");
		return UDP_STATUS_ERROR;
	}

	buffer[received] = '\0';
	if (out_length)
		*out_length = received;

	return UDP_STATUS_OK;
}

int try_connect(const struct sockaddr_in *target)
{
	char buffer[UDP_RESPONSE_BUFFER];
	ssize_t sent_length;
	ssize_t received_length = 0;
	int sockfd;
	int status = UDP_STATUS_ERROR;

	memset(buffer, 0, sizeof(buffer));

	sockfd = create_udp_socket();
	if (sockfd < 0)
		return UDP_STATUS_ERROR;

	if (configure_receive_timeout(sockfd, UDP_TIMEOUT_SECONDS, 0) == -1)
		goto cleanup;

	sent_length = send_udp_payload(sockfd, target, UDP_PAYLOAD, UDP_PAYLOAD_LEN);
	if (sent_length < 0)
		goto cleanup;

	printf("Sent %zd bytes\n", sent_length);
	printf("Waiting for response...\n");

	status = receive_udp_response(sockfd, buffer, sizeof(buffer), &received_length);
	if (status == UDP_STATUS_OK)
		printf("Response received (%zd bytes): %s\n", received_length, buffer);
	else if (status == UDP_STATUS_TIMEOUT)
		printf("No response (timeout)\n");

cleanup:
	close(sockfd);
	return status;
}

int main(int ac, char **av)
{
	struct sockaddr_in target;
	int port;

	if (ac != 3) {
		print_usage(av[0]);
		return EXIT_FAILURE;
	}

	port = parse_port(av[2]);
	if (port < 0)
		return EXIT_FAILURE;

	memset(&target, 0, sizeof(target));
	target.sin_family = AF_INET;
	target.sin_port = htons((uint16_t)port);

	if (inet_pton(AF_INET, av[1], &target.sin_addr) != 1) {
		fprintf(stderr, "Error: invalid IPv4 address\n");
		return EXIT_FAILURE;
	}

	printf("Trying IP: %s Port: %d\n", av[1], port);

	int status = try_connect(&target);
	if (status == UDP_STATUS_OK)
		printf("Port OPEN (response received)\n");
	else if (status == UDP_STATUS_TIMEOUT)
		printf("No UDP response (open|filtered)\n");
	else
		printf("Error sending UDP probe\n");

	return EXIT_SUCCESS;
}