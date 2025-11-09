/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:29:51 by rdelicad          #+#    #+#             */
/*   Updated: 2025/11/09 15:51:19 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h" 

int	parse_file(char *av, t_config *config)
{
	if (!av)
		return (0);
	if (access(av, F_OK) == -1)
	{
		printf("Error: file '%s' does not exist\n", av);
		return(0);
	}
	if (access(av, R_OK) == -1)
	{
		printf("Error: file '%s' is not readable\n", av);
		return (0);
	}
	if (config->file_name)
		free(config->file_name);
	config->file_name = strdup(av);
	if (!config->file_name)
		return (0);
	return 1;
}