/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:04:04 by rdelicad          #+#    #+#             */
/*   Updated: 2025/11/09 16:33:07 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static int is_valid_ip_or_hostname(const char *target)
{
	struct addrinfo	hints;
	struct addrinfo	*result;
	int				ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	ret = getaddrinfo(target, NULL, &hints, &result);
	if (ret != 0)
		return (0);
	freeaddrinfo(result);
	return (1);
}

int	parse_ip(char *av, t_config *config)
{
	if (!av)
		return (0);
	if (config->ip_address)
	{
		printf("Error: multiple targets specified\n");
		return (0);
	}
	if (config->file_name)
	{
		printf("Error: cannot specify both IP and --filename\n");
		return (0);
	}
	if (!is_valid_ip_or_hostname(av))
	{
		printf("Error: invalid IP address or hostname '%s'\n", av);
		return (0);
	}
	config->ip_address = strdup(av);
	if (!config->ip_address)
		return (0);
	return (1);
}