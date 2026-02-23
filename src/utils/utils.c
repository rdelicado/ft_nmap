/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:38:20 by rdelicad          #+#    #+#             */
/*   Updated: 2025/11/23 12:19:54 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void free_targets(t_target *target) 
{
	t_target	*tmp;

	while (target)
	{
		tmp = target->next;
		if (target->hostname)
			free(target->hostname);
		if (target->ip)
			free(target->ip);
		free(target);
		target = tmp;
	}
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	if (config->target)
		free(config->target);
	if (config->resolved_ip)
		free(config->resolved_ip);
	if (config->file_name)
		free(config->file_name);
	if (config->targets)
		free_targets(config->targets);
}
