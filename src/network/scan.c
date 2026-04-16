#include "ft_nmap.h"

int	scan_start(t_config *config)
{
	t_target	*target;

	if (!config)
		return (0);
	target = config->target_list;
	if (target)
		printf("Simulando escaneo para la IP: %s\n", target->ip);
	else if (config->input_target)
		printf("Simulando escaneo para la IP: %s\n", config->input_target);
	else
		return (0);
	return (1);
}