/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_targets_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17                                  #+#    #+#             */
/*   Updated: 2026/04/17                                 ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

int		read_targets_from_file(const char *filename, t_config *config)
{
    FILE        *file;
    char        line[256];
    t_target    *last = NULL;
    t_target    *new_node;

    // abrir archivo
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file '%s'\n", filename);
        return (0);
    }

    // leer linea a linea con fget
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // cuando encuentre \n sustituir por \0
        line[strcspn(line, "\n")] = '\0';
        // si la linea es vacia (pj: intro), lo saltamos
        if (strlen(line) == 0)
            continue;
        // Creamos nodo
        new_node = create_target(line);
        if (new_node == NULL)
            continue;
        // Enganchar a la lista enlazada
        if (config->target_list == NULL)
        {
            // si esta vacia la lista, este sera el primer nodo
            config->target_list = new_node;
            last = new_node;
        }
        else
        {
            // si hay mas nodos lo ponemos el ultimo al nodo
            last->next = new_node;
            last = new_node;
        }
    }
    fclose(file);
    return (1);
}