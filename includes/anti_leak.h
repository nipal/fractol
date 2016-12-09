/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_leek.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 01:19:32 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/09 10:00:39 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef	ANTI_LEAKS
# define ANTI_LEAKS

# include "fractol.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

# define NB_MALLOC 17
# define PATH_DEBUG "debug2/"


# define RESET  0
# define ADD 1


typedef struct	s_garbage t_garbage;

struct					s_garbage
{
	void				*ptr;		
	t_garbage			*next;
};

int		g_leaks[NB_MALLOC];

int						init_debug(int nb_malloc);
void					close_all_debug(int nb_malloc);
void					push_malloc_turn(int turn, int nb_malloc);
void					push_addr(int id, char *message, void *ptr);

void					garbage_node(void *adrr, int mode);
void					free_all_adrr(t_garbage *beg);
void					adrr_push_front(t_garbage **beg, t_garbage *new);
t_garbage				*new_adrr(void	*adrr);
#endif
