/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:09:05 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/29 21:09:27 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int         create_client(char *addr, int port)
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

int	get_client_socket(int ss)
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

static void     wait_for_event(int sock, fd_set *active_fd)
{
	static	int	nb = 0;
	struct		timeval timeout;
	struct      sockaddr_in clientname;
	socklen_t   size;
	fd_set      read_fd;
	int         new_sock;

	t_data		test;
	int			ret;
	ret = -1;

	timeout.tv_sec = 0;
	timeout.tv_usec = 2000;
	read_fd = *active_fd;
	if (select(FD_SETSIZE, &read_fd, NULL, NULL, &timeout) < 0)
		perror("(fatal) select"), exit(-1);


	
	for (int i = 0; i < FD_SETSIZE; ++i)
		if (FD_ISSET (i, &read_fd))
		{

			bzero(test.test, DATA_LENGTH_2); 
			if ((ret = read(i, &(test.test), sizeof(t_data))) < 0)
			{
				printf("%d closed !\n", i);
				close (i);
//					send_disconnected_client(i);
//					remove_client(i);
				FD_CLR(i, active_fd);
				exit(0);
			}
		printf("ret:%d->	%s\n", ret, test.test);
		if (ret == 0)
		{
			// la on quite mais on pourrai tenter d'attendre une nouvelle coneciton
			exit(0);
		}
	//		printf("[%d]> %s\n", nb++, test.test);
		}
}

int	main(int ac, char **av)
{
	int                 port;
	int                 sock;
	fd_set              read_fd;

	if (ac >= 3)
	{
		port = atoi(av[2]);
		sock = create_client(av[1], port);
		get_client_socket(sock);
		FD_ZERO(&read_fd);
		FD_SET(sock, &read_fd);
		//      FD_SET(0, &read_fd);
		while (42)
		{
			wait_for_event(sock, &read_fd);
		}


	}
}
