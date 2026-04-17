/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:15:53 by rdelicad          #+#    #+#             */
/*   Updated: 2026/04/16 20:04:30 by rdelicad         ###   ########.fr       */
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
# include <signal.h>
# include <sys/time.h>

extern volatile sig_atomic_t g_signal;

// Resultado individual por puerto + tipo de escaneo
typedef struct s_scan_result
{
	int				port;		// puerto
	char			*state;		// open, closed, filtered, unfiltered, open/filtered
	char			*scan_type;	// SYN, UPD, etc
	int				timed_out;	// 1 si se agoto tiempo, 0 si no
	int				error;		// 0 si ok, otro valor si error
}	t_scan_result;

// Objetivo individual a escanear
typedef struct s_target
{
	char			*hostname;		// nombre de host original
	char			*ip;			// IPv4 objetivo en texto
	struct s_target	*next;			// siguiente objetivo en la lista

	// Resultados de escaneo
	t_scan_result	**output;		// Array dinamico de resultados
	int				output_count;	// Cantidad de resultados guardados
}	t_target;

// Configuracion global del programa
typedef struct s_config 
{
	char 			*input_target;	// Ip o hostname de entrada unica
	char			*resolved_ip;	// Ip resuelta
	char 			*file_name;		// ruta del fichero con objetivos
	int				speedup;		// nivel de concurrencia solicitado
	int 			thread_count;	// numero real de hilos usados
	bool 			scan_syn;		// activar escaneo SYN
	bool 			scan_null;		// activar escaneo NULL
	bool 			scan_ack;		// activar escaneo ACK
	bool 			scan_fin;		// activar escaneo FIN
	bool 			scan_xmas;		// activar escaneo XMAS
	bool 			scan_udp;		// activar escaneo UDP
	bool 			show_help;		// mostrar ayuda y salir
	uint8_t 		ports[65536];	// tabla de puertos marcados para escanear
    int             ports_count;    // cantidad de puertos marcados
	t_target		*target_list;	// lista enlazada de objetivos finales
} t_config;

// ===== PARSER FUNCTIONS =====
void	show_help(void);	// imprime el uso del programa
int		parse_args(int ac, char **av, t_config *config);	// parsea toda la CLI
int		parse_scan(char *av, t_config *config);	// parsea tipos de escaneo
int		parse_ports(char *av, t_config *config);	// parsea rango/lista de puertos
int		parse_speedup(char *av, t_config *config);	// parsea valor de speedup
int		parse_file(char *av, t_config *config);	// parsea fichero de objetivos
int		parse_ip(char *av, t_config *config);	// parsea objetivo IP/FQDN unico

// ===== UTILS FUNCTIONS =====
void	free_config(t_config *config);	// libera toda la configuracion global
void	free_targets(t_target *target);	// libera la lista de objetivos
char	*resolve_hostname(const char *hostname);	// resuelve FQDN a IPv4
int		read_targets_from_file(const char *filename, t_config *config);	// carga objetivos desde fichero
int		build_target_list(t_config *config);	// construye la lista final de objetivos
int		add_target_node(t_config *config, const char *hostname, const char *ip);	// anade un objetivo a la lista

// ===== ENGINE OUTPUT FUNCTIONS =====
void	print_target_results(t_target *target);	// imprime resultados de un objetivo
void	print_all_results(t_target *target_list);	// imprime resultados de todos los objetivos

// ===== NETWORK SCAN FUNCTIONS =====
int		scan_start(t_config *config);	// inicia el flujo completo de escaneo


#endif