/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_leak.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 21:15:24 by fjanoty           #+#    #+#             */
/*   Updated: 2016/12/09 10:03:50 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "anti_leak.h"
#include "fractol.h"

/*
**	ouverture des fichier
*/

int		init_debug(int nb_malloc)
{
	int	i;
	char	*name;

	if (!(name = malloc(100)))
		return (0);
	i = 0;
	while (i < nb_malloc)
	{
		sprintf(name, "%smaloc_%d", PATH_DEBUG, i);
		if ((g_leaks[i] = open(name, O_WRONLY | O_CREAT, 0666)) < 0)
		{
			printf("open_fail:[%d]:{%s}\n	->%s\n", i, name, strerror(errno));
			return (0);
		}
		else if (g_leaks[i] <= 2)
		{
	printf("STANDAAAARRR	--->:[%d]:{%s}\n	->%d\n", i, name, g_leaks[i]);
			return (0);
		}
		i++;
	}
	free(name);
	return (1);
}

/*
**	fermeturer des fichier
*/

void	close_all_debug(int nb_malloc)
{
	int	i;

	i = 0;
	while (i < nb_malloc)
	{
		close(g_leaks[i]);
		i++;
	}
}

/*
**	insertion d'une ligne (delimiter des ation repetitive)
*/

void	push_malloc_turn(int turn, int nb_malloc)
{
	int	i;

	i = 0;
	while (i < nb_malloc)
	{
		turn++;
	//	dprintf(g_leaks[i], "\n		--------- turn:%d ---------\n\n", turn);
		i++;
	}
}

/*
**	on insert un message
*/

void	push_addr(int id, char *message, void *ptr)
{
	return ;
	if (id >= 0)
	{
		if (g_leaks[id] < 0)
			printf("ERRROR --->:[%d]%d::%p\n", id, g_leaks[id], ptr);
		else if (g_leaks[id] <= 2)
			printf("STANDAAAARRR	--->:[%d]%d::%p\n", id, g_leaks[id], ptr);
		else
			dprintf(g_leaks[id], "%s%p\n", message, ptr);
	}
}


t_garbage		*new_adrr(void	*adrr)
{
	t_garbage	*new;

	if (!(new = (t_garbage *)malloc(sizeof(t_garbage))))
		return (NULL);
	new->ptr = adrr;
	new->next = NULL;
	return (new);
}

void		adrr_push_front(t_garbage **beg, t_garbage *new)
{
	if (!beg || !new)
		return ;
	new->next = *beg;
	*beg = new;
}

void		free_all_adrr(t_garbage *beg)
{
	t_garbage	*tmp;
	t_polygone	*tmp2;
	int	i;

	i = 0;
	while (beg)
	{
		tmp = beg->next;
		tmp2 = (t_polygone*)beg->ptr;
		polygone_destroy_one(&tmp2);
		free(beg);
		beg = tmp;
		i++;
	}
	printf("node_cleaned:%d\n", i);
}

void							garbage_node(void *adrr, int mode)
{
	static	t_garbage	*beg = NULL;
	t_garbage			*tmp;

	if (mode == ADD)
	{
		if ((tmp = new_adrr(adrr)))
			adrr_push_front(&beg, tmp);
		else
			ft_putstr("error  memorry\n");
	}
	else if (beg && mode == RESET)
	{
		free_all_adrr(beg);
		beg = NULL;
	}
	else
		ft_putstr("unknow mode\n");
}
