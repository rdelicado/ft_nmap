/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:24:48 by rdelicad          #+#    #+#             */
/*   Updated: 2025/11/01 12:42:21 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void	init_config(t_config *config)
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

int	parse_scan_types(char *arg, t_config *config)
{
    char	*list_scan;
    char	*token;

    if (!arg)
        return (0);
    disable_all_scans(config);
    list_scan = strdup(arg);
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

void	print_scan_status(t_config *config)
{
    printf("\n=== Scan Configuration ===\n");
    printf("SYN:  %s\n", config->scan_syn ? "1" : "0");
    printf("NULL: %s\n", config->scan_null ? "1" : "0");
    printf("ACK:  %s\n", config->scan_ack ? "1" : "0");
    printf("FIN:  %s\n", config->scan_fin ? "1" : "0");
    printf("XMAS: %s\n", config->scan_xmas ? "1" : "0");
    printf("UDP:  %s\n", config->scan_udp ? "1" : "0");
    printf("==========================\n\n");
}
