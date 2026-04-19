/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_hostname.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:20:31 by rdelicad          #+#    #+#             */
/*   Updated: 2025/11/23 12:20:32 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

char *resolve_hostname(const char *hostname)
{
    struct addrinfo hints, *result;
    char            *ip;
    struct sockaddr_in *addr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    if (getaddrinfo(hostname, NULL, &hints, &result) != 0)
        return (NULL);
        
    ip = malloc(INET_ADDRSTRLEN);
    if (!ip)
    {
        freeaddrinfo(result);
        return (NULL);
    }
    
    addr = (struct sockaddr_in *)result->ai_addr;
    inet_ntop(AF_INET, &(addr->sin_addr), ip, INET_ADDRSTRLEN);
    
    freeaddrinfo(result);
    return (ip);
}
