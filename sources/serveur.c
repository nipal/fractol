/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 22:39:08 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/31 14:08:53 by nperrin          ###   ########.fr       */
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

# define STACK_SIZE 100
//	int				get_server_socket(int ss);
//	int				*get_all_open_sockets(int new_socket);
//	static	void	close_sockets(int s);
//	static	int		create_server(int port);
//	void			add_new_client(int new_sock);
//	static	void	wait_for_event(int sock, fd_set *active_fd);
//	


static size_t			g_n_client = 0;
static t_client_data g_client_data[STACK_SIZE];

int	get_server_socket(int ss)
{
	static	int	server_socket = 0;

	if (ss == 0)
	{
		return (server_socket);
	}
	else
	{
		server_socket = ss;
		return (server_socket);
	}
}

int			remove_open_socket(size_t socket_id)
{
	if (socket_id >= (STACK_SIZE - 1)
		|| !g_client_data[socket_id].in_use)
		return (-1);
	g_client_data[socket_id].in_use = 0;
	g_n_client--;
	shutdown(g_client_data[socket_id].socket, 2);
	return (0);
}

int			remove_open_socket_by_socket(int socket)
{
	size_t	i;

	i = 0;
	while (i < STACK_SIZE)
	{
		if (g_client_data[i].in_use
			&& (g_client_data[i].socket == socket))
			return (remove_open_socket(i));
		i++;
	}
	return (-1);
}

int			remove_open_socket_by_addr(struct in_addr addr)
{
	size_t	i;

	i = 0;
	while (i < STACK_SIZE)
	{
		if (g_client_data[i].in_use
			&& (g_client_data[i].addr.s_addr == addr.s_addr))
			return (remove_open_socket(i));
		i++;
	}
	return (-1);
}

int			add_open_socket(
				int					new_socket,
				struct in_addr		new_addr)
{
	size_t	i;

	if (g_n_client >= (STACK_SIZE - 1))
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

size_t		get_all_open_sockets(
				t_client_data	**p_client_data)
{
	*p_client_data = (t_client_data *)g_client_data;
	return (g_n_client);
}

void     close_sockets(int s)
{
	static	int	first_time = 1;
	int     ss;
	size_t			n_shutdown;
	t_client_data	*client_data;

	printf("\n");
	(void)s;
	if (!first_time)
		exit(0) ;
	first_time = 0;
	if ((ss = get_server_socket(0)))
		close(ss);
	get_all_open_sockets(&client_data);
	for (int i = 0; n_shutdown < g_n_client; i++)
	{
		if (client_data[i].in_use)
		{
			printf("socket [%d] closed\n", client_data[i].socket);
			remove_open_socket(i);
			n_shutdown++;
		}
	}
	printf("server disconect\n");
	ft_exit(get_env(NULL));
}

int          create_server(int port)
{
	int                 sock;
	struct protoent     *proto;
	struct sockaddr_in  sin;

	proto = getprotobyname("tcp");
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		printf("cant bind port: %i\n", port), exit(-1);
	printf("Server connected on port %i\n", port);
	listen(sock, STACK_SIZE);
	return (sock);
}

//	void	add_new_client(int new_sock)
//	{
//		get_all_open_sockets(new_sock);
//	}


//	on va faire une fonction qui read les data et qui les 
int	read_from_nettowrk_and_draw(int socket)
{
	t_ifs_param	data_ifs;
	t_data_nw	data_nw;
	int			ret;
	t_env		*e;

	e = get_env(NULL);
	ret = read(socket, &data_nw, sizeof(t_data_nw));
	if (ret != 0)
	{
		format_data_to_print(&data_nw, &data_ifs);
		print_client_ifs(e->fractal, &data_ifs);
	//	actu_win_rest(e->fractal);
	}
	return (ret);
}


/*
**	C'ette fonction serra appeler en boucle
*/
void     wait_for_event(int sock, fd_set *active_fd, int status)
{
	struct			timeval timeout;
	struct          sockaddr_in clientname;
	socklen_t       size;
	fd_set          read_fd;
	int             new_sock;
	int				ret;

	t_ifs_param		simple_buffer;
	t_env			*e;

	e = get_env(NULL);
	timeout.tv_sec = 0;
	timeout.tv_usec = 2000;
	read_fd = *active_fd;
	if (select(FD_SETSIZE, &read_fd, NULL, NULL, &timeout) < 0)
		perror("(fatal) select"), exit(-1);

	for (int i = 0; i < FD_SETSIZE; ++i)
		if (FD_ISSET (i, &read_fd))
		{
			if (status == SERVEUR && i == sock)
			{
				size = sizeof(clientname);
				if ((new_sock = accept(sock, (struct sockaddr *)&clientname, &size)) < 0)
					perror ("accept"), exit(-1);
				printf("accepted connection: %i\n", new_sock);
				add_open_socket(new_sock, clientname.sin_addr);
				FD_SET(new_sock, active_fd);
			}
			else
			{	// la le serveur pourai aussi lire les data du client
				if (status == CLIENT)
				{
					ret = read_from_nettowrk_and_draw(i);
					if (ret == 0)
					{
//							shutdown(get_client_socket(0), 2);
//							exit(0);
					}
				}
			}
		}
}
