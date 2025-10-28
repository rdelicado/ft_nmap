/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:03:56 by rdelicad          #+#    #+#             */
/*   Updated: 2025/10/28 22:50:44 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void	init_config(t_config *config)
{
	config->ip_address		= NULL;
	config->file_name		= NULL;
	config->speedup			= 0;
	config->thread_count	= 0;
	config->scan_syn 		= true;
	config->scan_null 		= true;
	config->scan_ack 		= true;
	config->scan_fin 		= true;
	config->scan_xmas 		= true;
	config->scan_udp 		= true;
	config->show_help 		= true;
	memset(config->ports, 0, sizeof(config->ports));
	for (int i = 1; i <= 1024; i++)
		config->ports[i] = 1;
}

int	parse_args(int ac, char **av, t_config *config)
{
	// Validación básica de argumentos
	if (ac < 2 || !av || !av[1])
		return (0);
	
	if (strcmp(av[1], "--help") == 0)
		return (0);
	
	
	init_config(config);
	
	// Aquí irá el parsing real de los argumentos
	(void)av;
	
	return (1);
}