/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:03:56 by rdelicad          #+#    #+#             */
/*   Updated: 2026/02/23 17:23:05 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void init_config(t_config *config) 
{
	int i;

	config->target = NULL;
	config->resolved_ip = NULL;
	config->file_name = NULL;
	config->targets = NULL;
	config->speedup = 0;
	config->thread_count = 0;
	config->scan_syn = true;
	config->scan_null = true;
	config->scan_ack = true;
	config->scan_fin = true;
	config->scan_xmas = true;
	config->scan_udp = true;
	config->show_help = false;
	memset(config->ports, 0, sizeof(config->ports));
	i = 1;
	while (i <= 1024) {
		config->ports[i] = 1;
		i++;
	}
}

int parse_args(int ac, char **av, t_config *config) {
	int i;

	if (ac < 2 || !av || !av[1])
		return (0);
	init_config(config);
	i = 1;
	while (i < ac) {
		if (strcmp(av[i], "--help") == 0)
			return (0);
		if (strcmp(av[i], "--scan") == 0) {
			if (i + 1 >= ac)
				return (0);
			if (!parse_scan(av[i + 1], config))
				return (0);
			i++;
		} else if (strcmp(av[i], "--port") == 0) {
			if (i + 1 >= ac)
				return (0);
			if (!parse_ports(av[i + 1], config))
				return (0);
			i++;
		} else if (strcmp(av[i], "--speedup") == 0) {
			if (i + 1 >= ac)
				return (0);
			if (!parse_speedup(av[i + 1], config))
				return (0);
			i++;
		} else if (strcmp(av[i], "--filename") == 0) {
			if (i + 1 >= ac)
				return (0);
			if (!parse_file(av[i + 1], config))
				return (0);
			i++;
		} else if (strcmp(av[i], "--ip") == 0) {
			if (i + 1 >= ac)
				return (0);
			if (!parse_ip(av[i + 1], config))
				return (0);
			i++;
		} else if (av[i][0] != '-') {
			if (!parse_ip(av[i], config))
				return (0);
		} else {
			printf("Error: argumento desconocido '%s'\n", av[i]);
			return (0);
		}
		i++;
	}

	if (!config->target && !config->file_name) {
		printf("Error: no target specified (IP of --filename required)\n");
		return (0);
	}
	return (1);
}