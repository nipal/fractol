/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 01:37:49 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/30 01:40:07 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		create_client(char *addr, int port)
{
	int                 sock;
	struct protoent     *proto;
	struct sockaddr_in  sin;

	if (port == 0)
		return (-1);
	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	if (!strcmp(addr, "localhost"))
		sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		perror("Connection error !\n");
	return (sock);
}

int		get_client_socket(int ss)
{
	static	int	client_socket = 0;

	if (ss == 0)
	{
		return (client_socket);
	}
	else
	{
		client_socket = ss;
		return (client_socket);
	}
}
