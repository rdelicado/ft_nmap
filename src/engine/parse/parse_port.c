/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_port.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:55:54 by rdelicad          #+#    #+#             */
/*   Updated: 2025/11/01 19:39:44 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void disable_all_ports(t_config *config)
{
  memset(config->ports, 0, sizeof(config->ports));
}

static int process_single(char *port_str, t_config *config)
{
  int port;

  port = atoi(port_str);
  if (port < 1 || port > 65535)
	return (0);
  config->ports[port] = 1;
  return (1);
}

static int process_range(char *range_str, t_config *config)
{
  char *range;
  int start;
  int end;
  int i;

  range = strchr(range_str, '-');
  if (!range)
	return (0);
  *range = '\0';
  start = atoi(range_str);
  end = atoi(range + 1);
  if (start < 1 || start > 65535 || end < 1 || end > 65535 || start > end)
	return (0);
  i = start;
  while (i <= end && i <= 65535) {
	config->ports[i] = 1;
	i++;
  }
  return (1);
}

int parse_ports(char *av, t_config *config)
{
  char *list_port;
  char *single;
  char *range;

  if (!av)
	return (0);
  disable_all_ports(config);
  list_port = strdup(av);
  if (!list_port)
	return (0);
  single = strtok(list_port, ",");
  while (single != NULL) {
	range = strchr(single, '-');
	if (range != NULL) {
		if (!process_range(single, config)) {
			free(list_port);
			return (0);
		}
	} else {
		if (!process_single(single, config)) {
			free(list_port);
			return (0);
		}
	}
	single = strtok(NULL, ",");
  }
  free(list_port);
  return (1);
}
