/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_target_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17                                  #+#    #+#             */
/*   Updated: 2026/04/17                                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <stdio.h>

t_target *create_target(char *ip)
{
    // 1. reservar memoria
        t_target *new_node = (t_target *)malloc(sizeof(t_target));
        if (new_node == NULL) {
            return NULL;
        }

        // 2. Inicializar los valores
        new_node->hostname = strdup(ip);
        new_node->ip = resolve_hostname(ip);
        if (new_node->ip == NULL)
        {
            printf("Error: Could not resolve hostname: %s\n", ip);
            free(new_node->hostname);
            free(new_node);
            return NULL;
        }
        new_node->next = NULL;
        new_node->output = NULL;
        new_node->output_count = 0;

        return new_node;
}

int		build_target_list(t_config *config)
{
    // Para una sola IP o FQDN
    if (config->input_target)
    {
        config->target_list = create_target(config->input_target);
        
        if (config->target_list == NULL)
            return (0);
    }
    else if (config->file_name) // Para IP's en archivo
    {
        if (read_targets_from_file(config->file_name, config) == 0)
            return (0);
    }

    return (1);
}