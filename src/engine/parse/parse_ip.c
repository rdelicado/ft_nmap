/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:04:04 by rdelicad          #+#    #+#             */
/*   Updated: 2026/04/18 11:35:36 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static int	is_ascii_alnum(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

static int	has_alpha(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z'))
			return (1);
		i++;
	}
	return (0);
}

static int	is_valid_hostname_syntax(const char *target)
{
	int		label_len;
	size_t	i;
	size_t	len;
	char	*tld;

	if (!target || !target[0])
		return (0);
	len = strlen(target);
	if (len > 253)
		return (0);
	if (target[0] == '.' || target[0] == '-')
		return (0);
	if (target[len - 1] == '.' || target[len - 1] == '-')
		return (0);
	i = 0;
	label_len = 0;
	while (i < len)
	{
		if (target[i] == '.')
		{
			if (label_len == 0 || label_len > 63 || target[i - 1] == '-')
				return (0);
			label_len = 0;
		}
		else if (target[i] == '-')
		{
			if (label_len == 0)
				return (0);
			label_len++;
		}
		else if (is_ascii_alnum(target[i]))
			label_len++;
		else
			return (0);
		i++;
	}
	if (label_len == 0 || label_len > 63 || target[len - 1] == '-')
		return (0);
	tld = strrchr(target, '.');
	if (tld && !has_alpha(tld + 1))
		return (0);
	return (1);
}

static int	is_valid_hostname(const char *target)
{
	struct addrinfo hints;
	struct addrinfo *result;
	int	ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	ret = getaddrinfo(target, NULL, &hints, &result);
	if (ret != 0)
		return (0);
	freeaddrinfo(result);
	return (1);
}

static int	seems_ipv4_literal(const char *target)
{
	int	i;
	int	dots;

	if (!target || !target[0])
		return (0);
	i = 0;
	dots = 0;
	while (target[i])
	{
		if (target[i] == '.')
			dots++;
		i++;
	}
	if (dots != 3)
		return (0);
	if (target[0] < '0' || target[0] > '9')
		return (0);
	if (target[i - 1] < '0' || target[i - 1] > '9')
		return (0);
	return (1);
}

static int	is_valid_ipv4(const char *ip)
{
	struct in_addr addr;

	if (!ip)
		return (0);

	return (inet_pton(AF_INET, ip, &addr) == 1);
}

int parse_ip(char *av, t_config *config)
{
	if (!av)
		return (0);
	if (config->input_target) {
		printf("Error: multiple targets specified\n");
		return (0);
	}
	if (config->file_name) {
		printf("Error: cannot specify both IP and --file\n");
		return (0);
	}
	if (is_valid_ipv4(av))
	{
		config->input_target = strdup(av);
		if (!config->input_target)
			return (0);
		return (1);
	}
	if (seems_ipv4_literal(av))
	{
		printf("Error: invalid IPv4 address '%s'\n", av);
		return (0);
	}
	if (!is_valid_hostname_syntax(av))
	{
		printf("Error: invalid hostname '%s'\n", av);
		return (0);
	}
	if (!is_valid_hostname(av))
	{
		printf("Error: invalid hostname '%s'\n", av);
		return (0);
	}
	config->input_target = strdup(av);
	if (!config->input_target)
		return (0);
	return (1);
}
