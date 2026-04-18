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

int		build_target_list(t_config *config)
{
    printf("ip:%s\n", config->input_target);
    printf("file:%s\n", config->file_name);
    return 1;
}