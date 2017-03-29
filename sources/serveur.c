/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 22:39:08 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/29 22:41:44 by fjanoty          ###   ########.fr       */
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
int				get_server_socket(int ss);
int				*get_all_open_sockets(int new_socket);
static	void	close_sockets(int s);
static	int		create_server(int port);
void			add_new_client(int new_sock);
static	void	wait_for_event(int sock, fd_set *active_fd);


