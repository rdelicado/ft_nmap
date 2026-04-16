/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:38:20 by rdelicad          #+#    #+#             */
/*   Updated: 2026/04/16 20:04:30 by rdelicad         ###   ########.fr       */
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
	if (config->input_target)
		free(config->input_target);
	if (config->resolved_ip)
		free(config->resolved_ip);
	if (config->file_name)
		free(config->file_name);
	if (config->target_list)
		free_targets(config->target_list);
}
