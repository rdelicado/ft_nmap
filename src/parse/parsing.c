/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:03:56 by rdelicad          #+#    #+#             */
/*   Updated: 2025/11/01 12:44:33 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

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
			if (!parse_scan_types(av[i + 1], config))
				return (0);
			i++;
		}
		i++;
	}
	//print_scan_status(config);
	return (1);
}