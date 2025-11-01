/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:03:56 by rdelicad          #+#    #+#             */
/*   Updated: 2025/11/01 19:49:24 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void	init_config(t_config *config)
{
    int	i;

    config->ip_address = NULL;
    config->file_name = NULL;
    config->speedup = 0;
    config->thread_count = 0;
    config->scan_syn = true;
    config->scan_null = true;
    config->scan_ack = true;
    config->scan_fin = true;
    config->scan_xmas = true;
    config->scan_udp = true;
    config->show_help = true;
    memset(config->ports, 0, sizeof(config->ports));
    i = 1;
    while (i <= 1024)
    {
        config->ports[i] = 1;
        i++;
    }
}

int	parse_args(int ac, char **av, t_config *config)
{
	int i;
	
	if (ac < 2 || !av || !av[1])
		return (0);
	init_config(config);
	i = 1;
	while (i < ac)
	{
		if (strcmp(av[i], "--help") == 0)
			return (0);
		if (strcmp(av[i], "--scan") == 0)
		{
			if (i + 1 >= ac)
				return (0);
			if (!parse_scan(av[i + 1], config))
				return (0);
			i++;
		}
		else if (strcmp(av[i], "--port") == 0)
		{
			if (i + 1 >= ac)
				return (0);
			if (!parse_ports(av[i + 1], config))
				return (0);
			i++;
		}
		else if (strcmp(av[i], "--speedup") == 0)
		{
			if (i + 1 >= ac)
				return (0);
			if (!parse_speedup(av[i + 1], config))
				return (0);
			i++;
		}
		i++;
	}
	return (1);
}