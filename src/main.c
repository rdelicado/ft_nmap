#include "ft_nmap.h"

volatile sig_atomic_t g_signal = 0;

void signal_handler(int signum)
{
	g_signal = signum;
}

void show_help() 
{
	char *help[] = {
		"Usage:\n",
		"  ft_nmap [--help] [--ports [NUMBER/RANGED]] --ip <TARGET> [--speedup "
		"[NUMBER]] [--scan [TYPE]]\n",
		"  ft_nmap [--help] [--ports [NUMBER/RANGED]] --file <FILE> [--speedup "
		"[NUMBER]] [--scan [TYPE]]\n",
		"\n",
		"TARGET SPECIFICATION:\n",
		"  --ip <IP/hostname>\t\t: Single IPv4 address or hostname\n",
		"\t\t\t\t  Simple IPv4 format (x.x.x.x) or FQDN\n",
		"\t\t\t\t  Example: 192.168.1.1 or scanme.nmap.org\n"
		"\n",
		"  --file <filename>\t\t: File containing list of targets\n"
		"\t\t\t\t  One target per line\n",
		"SCAN TECHNIQUES:\n",
		"  --scan <type(s)>\t\t: Scan techniques to use (comma-separated)\n",
		"\t\t\t\t: Available types:\n",
		"\t\t\t\t\tSYN\t:TCP SYN scan\n",
		"\t\t\t\t\tNULL\t:TCP NULL scan\n",
		"\t\t\t\t\tFIN\t:TCP FIN scan\n",
		"\t\t\t\t\tXMAS\t:TCP XMAS scan\n",
		"\t\t\t\t\tACK\t:TCP ACK scan\n",
		"\t\t\t\t\tUDP\t:UDP scan\n",
		"\t\t\t\t  Default: All types if not specified\n",
		"\t\t\t\t  Example: --scan SYN,UDP\n",
		"\n",
		"PORT SPECIFICATION:\n",
		"  --ports <spec>\t\t: Ports to scan\n",
		"\t\t\t\t  Formats accepted:\n",
		"\t\t\t\t    Single port\t: 80\n",
		"\t\t\t\t    Range\t: 1-1024\n",
		"\t\t\t\t    List\t: 22,80,443\n",
		"\t\t\t\t    Mixed\t: 1-10,22,80,443\n",
		"\t\t\t\t  Default: 1-1024\n",
		"\t\t\t\t  Maximum: 1024 ports total\n",
		"TIMING AND PERFORMANCE:\n",
		"  --speedup <number>\t\t: Number of parallel threads\n",
		"\t\t\t\t  Range: 0-250\n",
		"\t\t\t\t  Default: 0 (sequential scan)\n",
		"\t\t\t\t  Higher values = faster scan\n",
		"OUTPUT:\n",
		"  --help\t\t\t: Display this help message\n",
		NULL
	};

	for (int i = 0; help[i]; i++)
		printf("%s", help[i]);
}

static int	is_root_user()
{
	if (getuid() != 0)
	{
		printf("Error: ft_nmap requires root privileges\n");
		printf("Try: sudo ./ft_nmap ...\n");
		return (0);
	}
	return (1
	);
}

int main(int ac, char **av) 
{
	t_config	    config;
    struct timeval  start, end;

    // Configuracion inicial y parseo
    signal(SIGINT, signal_handler);
	if (!is_root_user())
		return (1);
	if (!parse_args(ac, av, &config))
		return (1);

    // Preparacion de objetivos
	if (!build_target_list(&config)) {
        free_config(&config);
        return 1;
    }

    // Imprimir configuracion inicial
	// print_scan_config(&config); -> falta implementar

    // Ejecucion del escaneo
    gettimeofday(&start, NULL);
    /* if (!scan_start(&config))
        return (free_config(&config), 1); */
    gettimeofday(&end, NULL);

	// Imprimir resultados
	// print_scan_time(start, end); -> falta implementar
    // print_all_results(config.target_list); -> falta implementar

    // Liberar memoria
    free_config(&config);
	return (EXIT_SUCCESS);
}