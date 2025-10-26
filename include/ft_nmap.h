/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:15:53 by rdelicad          #+#    #+#             */
/*   Updated: 2025/10/26 18:03:54 by rdelicad         ###   ########.fr       */
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

typedef struct s_ft_nmap_args {
	bool show_help;
	char *ip_address;
	char *file_name;
	int ports[1024];
	int port_count;
	int thread_count;
	bool scan_syn;
	bool scan_null;
	bool scan_ack;
	bool scan_fin;
	bool scan_xmas;
	bool scan_udp;
} t_ft_nmap_args;

#endif