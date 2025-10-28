/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:15:53 by rdelicad          #+#    #+#             */
/*   Updated: 2025/10/28 22:25:11 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_H
# define FT_NMAP_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

// Structs

typedef struct s_config 
{
	char 	*ip_address;
	char 	*file_name;
	int		speedup;
	int 	ports[65536];
	int 	thread_count;
	bool 	scan_syn;
	bool 	scan_null;
	bool 	scan_ack;
	bool 	scan_fin;
	bool 	scan_xmas;
	bool 	scan_udp;
	bool 	show_help;
} t_config;

// Parser
int		parse_args(int ac, char **av, t_config *config);
void	print_help(void);

#endif