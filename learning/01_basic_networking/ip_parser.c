#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum { OCTET_COUNT = 4, MAX_IP_LEN = 15 }; // 255.255.255.255

static void print_usage(const char *prog_name)
{
    printf("Usage: %s <IP>\n", prog_name);
}

static int copy_ip(const char *source, char *buffer, size_t buffer_size)
{
    size_t len = strlen(source);

    if (len == 0 || len > buffer_size) {
        printf("Error: IP too long\n");
        return 0;
    }
    memcpy(buffer, source, len + 1);
    return 1;
}

static int parse_octet(const char *token, int *value)
{
    if (*token == '\0') {
        printf("Error: empty octet\n");
        return 0;
    }
    for (size_t i = 0; token[i] != '\0'; ++i) {
        if (!isdigit((unsigned char)token[i])) {
            printf("Error: \"%s\" is not a valid number\n", token);
            return 0;
        }
    }
    int num = atoi(token);
    if (num < 0 || num > 255) {
        printf("Error: octet %d out of range\n", num);
        return 0;
    }
    *value = num;
    return 1;
}

static int parse_ip(const char *ip, int octets[OCTET_COUNT])
{
    char ip_copy[MAX_IP_LEN + 1];
    char *token = NULL;
    int count = 0;

    if (!copy_ip(ip, ip_copy, MAX_IP_LEN))
        return 0;

    token = strtok(ip_copy, ".");
    while (token != NULL && count < OCTET_COUNT) {
        if (!parse_octet(token, &octets[count]))
            return 0;
        ++count;
        token = strtok(NULL, ".");
    }
    if (count != OCTET_COUNT || token != NULL) {
        printf("Error: incorrect number of octets\n");
        return 0;
    }
    return 1;
}

static void print_ip_info(const char *ip, const int octets[OCTET_COUNT])
{
    printf("Valid IP: %s\n", ip);
    for (int i = 0; i < OCTET_COUNT; ++i)
        printf("  - Octet %d: %d\n", i + 1, octets[i]);
}

int main(int argc, char **argv)
{
    int octets[OCTET_COUNT];

    if (argc != 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    if (!parse_ip(argv[1], octets))
        return EXIT_FAILURE;

    print_ip_info(argv[1], octets);
    return EXIT_SUCCESS;
}