/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 14:28:52 by nperrin           #+#    #+#             */
/*   Updated: 2017/03/31 14:35:06 by nperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>

static size_t			g_n_client = 0;
static t_client_data 	g_client_data[MAX_CLIENT];

int			remove_client(size_t socket_id)
{
	if (socket_id >= (MAX_CLIENT - 1)
		|| !g_client_data[socket_id].in_use)
		return (-1);
	g_client_data[socket_id].in_use = 0;
	g_n_client--;
	shutdown(g_client_data[socket_id].socket, 2);
	return (0);
}

int			remove_client_by_socket(int socket)
{
	size_t	i;

	i = 0;
	while (i < MAX_CLIENT)
	{
		if (g_client_data[i].in_use
			&& (g_client_data[i].socket == socket))
			return (remove_client(i));
		i++;
	}
	return (-1);
}

int			remove_client_by_addr(struct in_addr addr)
{
	size_t	i;

	i = 0;
	while (i < MAX_CLIENT)
	{
		if (g_client_data[i].in_use
			&& (g_client_data[i].addr.s_addr == addr.s_addr))
			return (remove_client(i));
		i++;
	}
	return (-1);
}

int			add_client(
				int					new_socket,
				struct in_addr		new_addr)
{
	size_t	i;

	if (g_n_client >= (MAX_CLIENT - 1))
		return (-1);
	i = 0;
	while (g_client_data[i].in_use)
		i++;
	g_client_data[i].socket = new_socket;
	g_client_data[i].addr = new_addr;
	g_client_data[i].in_use = 1;
	g_n_client++;
	return (0);
}

size_t		get_all_client_data(
				t_client_data	**p_client_data)
{
	*p_client_data = (t_client_data *)g_client_data;
	return (g_n_client);
}
