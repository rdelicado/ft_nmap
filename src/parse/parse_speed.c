/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_speed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:49:41 by rdelicad          #+#    #+#             */
/*   Updated: 2025/11/01 19:57:36 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

int	parse_speedup(char *av, t_config *config)
{
	int	value;

	if (!av)
		return (0);
	value = atoi(av);
	if (value < 1 || value > 250)
	{
		printf("Error: speedup must be between 1 and 250\n\n");
		return (0);
	}
	config->speedup = value;
	return (1);
}

