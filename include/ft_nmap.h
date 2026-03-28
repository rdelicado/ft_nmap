/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:15:53 by rdelicad          #+#    #+#             */
/*   Updated: 2026/03/28 12:16:11 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_H
# define FT_NMAP_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <arpa/inet.h>
# include <netdb.h>

// Structs
typedef struct s_target
{
	char			*hostname;
	char			*ip;
	struct s_target	*next;
}	t_target;

typedef struct s_scan_result
{
	int				port;
	char			*state;		// open, closed, filtered
	char			*scan_type;	// SYN, UPD, etc
}	t_scan_result;

typedef struct s_config 
{
	char 		*target;		// Ip o hostname
	char		*resolved_ip;	// Ip resuelta
	char 		*file_name;
	int			speedup;
	int 		thread_count;
	bool 		scan_syn;
	bool 		scan_null;
	bool 		scan_ack;
	bool 		scan_fin;
	bool 		scan_xmas;
	bool 		scan_udp;
	bool 		show_help;
	uint8_t 	ports[65536];
	t_target	*targets;
} t_config;

// Parser
void	show_help(void);
int		parse_args(int ac, char **av, t_config *config);
int		parse_scan(char *av, t_config *config);
int		parse_ports(char *av, t_config *config);
int		parse_speedup(char *av, t_config *config);
int		parse_file(char *av, t_config *config);
int		parse_ip(char *av, t_config *config);

// Utils.c
void	free_config(t_config *config);
void	free_targets(t_target *target);

// otros.c
char	*resolve_hostname(const char *hostname);
int		read_targets_from_file(const char *filename, t_config *config);
int		build_target_list(t_config *config);

/* --- SECCION DE REDES ---*/
void	scan_target(t_target *target, t_config *config);

#endif