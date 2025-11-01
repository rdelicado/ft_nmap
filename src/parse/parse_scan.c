/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:24:48 by rdelicad          #+#    #+#             */
/*   Updated: 2025/11/01 19:02:36 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void	disable_all_scans(t_config *config)
{
    config->scan_ack = false;
    config->scan_fin = false;
    config->scan_null = false;
    config->scan_syn = false;
    config->scan_udp = false;
    config->scan_xmas = false;
}

void	process_scan_token(char *token, t_config *config)
{
    if (strcmp(token, "ACK") == 0)
        config->scan_ack = true;
    else if (strcmp(token, "FIN") == 0)
        config->scan_fin = true;
    else if (strcmp(token, "NULL") == 0)
        config->scan_null = true;
    else if (strcmp(token, "SYN") == 0)
        config->scan_syn = true;
    else if (strcmp(token, "UDP") == 0)
        config->scan_udp = true;
    else if (strcmp(token, "XMAS") == 0)
        config->scan_xmas = true;
    else
        printf("Invalid scan type: %s\n", token);
}

int	parse_scan(char *av, t_config *config)
{
    char	*list_scan;
    char	*token;

    if (!av)
        return (0);
    disable_all_scans(config);
    list_scan = strdup(av);
    if (!list_scan)
        return (0);
    token = strtok(list_scan, ",");
    while (token != NULL)
    {
        process_scan_token(token, config);
        token = strtok(NULL, ",");
    }
    free(list_scan);
    return (1);
}
