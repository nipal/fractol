/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_reseau_basique.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 15:59:20 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/30 00:31:03 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "fractol.h"
//	le nombre maximum de conexion entrante

# include <errno.h>
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



# define DATA_LENGTH_1 30
# define DATA_LENGTH_2 100
typedef	struct	s_data
{
	int		size;
	int		data[DATA_LENGTH_1];
	char	test[DATA_LENGTH_2];
}				t_data;

# define STACK_SIZE 100
int				get_server_socket(int ss);
int				*get_all_open_sockets(int new_socket);
static	void	close_sockets(int s);
static	int		create_server(int port);
void			add_new_client(int new_sock);
static	void	wait_for_event(int sock, fd_set *active_fd);



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

int	*get_all_open_sockets(int new_socket)
{
	static	int	id_add = 0;
	static	int	all_client_socket[STACK_SIZE];

	if (new_socket > 0)
	{
		all_client_socket[id_add] = new_socket;
		id_add++;
	}
	return (all_client_socket);
}

void     close_sockets(int s)
{
	int     ss;
	int     *socks;

	(void)s;
	if ((ss = get_server_socket(0)))
		close(ss);
	socks = get_all_open_sockets(-1);
	for (int i = 0; socks[i]; i++)
	{
		printf("socket [%d] closed\n", socks[i]);
		shutdown(socks[0], 2);
	}
	
	exit(0);
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

void	add_new_client(int new_sock)
{
	get_all_open_sockets(new_sock);
}

void     wait_for_event(int sock, fd_set *active_fd)
{
	struct			timeval timeout;
	struct          sockaddr_in clientname;
	socklen_t       size;
	fd_set          read_fd;
	int             new_sock;


	static	int		nb = 0;
	t_data			data;
	int				ret;
	int				to_write;
	int				*all_client;

	char			tmp[20];
	char			tmp2[100];

	timeout.tv_sec = 0;
	timeout.tv_usec = 2000;
	read_fd = *active_fd;
	if (select(FD_SETSIZE, &read_fd, NULL, NULL, &timeout) < 0)
		perror("(fatal) select"), exit(-1);
		
	nb++;
	all_client = get_all_open_sockets(-1);
	to_write = all_client[0]; 
//		ret = read(0, &(data.test), DATA_LENGTH_2 - 1);
//		printf(">>	{%s}\n", data.test);
//		write(to_write, &(data.test), ret);
	
	if (to_write)
	{
	//	printf("to_write:%d\n", to_write);
		bzero(data.test, DATA_LENGTH_2); 
		bzero(tmp, 20); 
//		printf("we send: %s\n", data.test);
		
		read(0, tmp2, DATA_LENGTH_2 - 30);
		int	i;
		for (i = 0; i < STACK_SIZE && all_client[i]; i++) 
		{
			bzero(data.test, DATA_LENGTH_2); 
			sprintf(tmp, "		%d", all_client[i]);
			strcat(data.test, tmp);
			strcat(data.test, tmp2);

			write(all_client[i], data.test, strlen(data.test));
		}
	}

	for (int i = 0; i < FD_SETSIZE; ++i)
		if (FD_ISSET (i, &read_fd))
		{
			// uniquement pour le serveur (le if)
			if (i == sock)
			{
				size = sizeof(clientname);
				if ((new_sock = accept(sock, (struct sockaddr *)&clientname, &size)) < 0)
					perror ("accept"), exit(-1);
				printf("accepted connection: %i\n", new_sock);
				add_new_client(new_sock);// foncirton a recoder pour stoquer les socket (comme un fd) et pour apres fermer toutes les connexion d;uncoup
				FD_SET(new_sock, active_fd);
			}
			else // ca c'est aussi pour le client
			{
//					if (read_from_client(i) < 0)
//					{
//	//						printf("%s closed !\n", get_client_info(i)->name);
//						close (i);
//	//						send_disconnected_client(i);
//	//						remove_client(i);
//						FD_CLR(i, active_fd);
//					}
			}
		}
}

// stac d'initilisation qui recupere les ctr+c pour fermer tout les client
int             main(int ac, char **av)
{
	int                 port;
	int                 sock;
	fd_set              read_fd;

	if (ac == 2)
	{
		signal(SIGINT, close_sockets);
		port = atoi(av[1]);
		sock = create_server(port);
		get_server_socket(sock);
		FD_ZERO(&read_fd);
		FD_SET(sock, &read_fd);
		//      FD_SET(0, &read_fd);
		while (42)
			wait_for_event(sock, &read_fd);
	}
//	else
//		usage(*av);
	return (0);
}
