#include "ft_nmap.h"

void	print_help()
{
	char	*help[] = 
	{
		"Usage:\n",
		"  ft_nmap [--help] [--ports [NUMBER/RANGED]] --ip IP_ADDRESS [--speedup [NUMBER]] [--scan [TYPE]]\n",
		"  ft_nmap [--help] [--ports [NUMBER/RANGED]] --file FILE [--speedup [NUMBER]] [--scan [TYPE]]\n",
		"\n",
		"TARGET SPECIFICATION:\n",
		"  --ip <IP/hostname>\t\t: Single IPv4 address or hostname\n",
		"\t\t\t\t  Simple IPv4 format (x.x.x.x) or FQDN\n",
		"\t\t\t\t  Example: 192.168.1.1 or scanme.nmap.org\n"
		"\n",
		"  --file <filename>\t\t: File containing list of targets\n"
		"\t\t\t\t  One target per line\n",
		"SCAN TECHNIQUES:\n",
		"  --scan <type(s)>\t\t: Scan techniques to use (comma-separeted)\n",
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
		"TIMING ADN PERFORMANCE:\n",
		"  --speedup <number>\t\t: Number of parallel threads\n",
		"\t\t\t\t  Range: 0-250\n",
		"\t\t\t\t  Default: 0 (sequential scan)\n",
		"\t\t\t\t  Higher values = faster scan\n",
		"OUTPUT:\n",
		"  --help\t\t\t: Display this help message\n",
		NULL
	};

	for(int i = 0; help[i]; i++)
		printf("%s", help[i]);
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		print_help();
		return EXIT_FAILURE;
	}
	(void)av;
	return (0);
}