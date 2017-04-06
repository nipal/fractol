/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 23:48:33 by fjanoty           #+#    #+#             */
/*   Updated: 2017/01/04 04:42:58 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
**	-On lit le fichier par buffeur que l'on stoque dans des liste chainer
**	-On allou une chaine a la bonne taille et on copie tout dedans.
*/

int		open_file(char *name)
{
	int		fd;
	char	c;
	int		ret;

	fd = open(name, O_RDONLY);
	if (fd < 0 || ((ret = read(fd, &c, 0)) < 0))
		return (-1);
	return (fd);
}

t_buff_file	*get_next(int fd)
{
	t_buff_file	*node;

	if (fd <= 0 || !(node = (t_buff_file*)malloc(sizeof(t_buff_file))))
		return (NULL);
	node->next = NULL;
	if ((node->size = read(fd, node->buff, BUFF_FILE_SIZE)) <= 0)
		return (NULL);
	return (node);
}

t_buff_file	*stack_buff_file(int fd, int *total_size, int *nb_buff)
{
	t_buff_file	*beg_stack;
	t_buff_file	*node;
	int			size_last;

	if (!total_size || !nb_buff)
		return (NULL);
	beg_stack = NULL;
	size_last = 0;
	*nb_buff = 0;
	size_last = -1;
	while ((node = get_next(fd)))
	{
		node->next = beg_stack;
		beg_stack = node;
		size_last = node->size;
		(*nb_buff)++;
	}
	if (nb_buff <= 0)
		return (NULL);
	*total_size = (*nb_buff - 1) * BUFF_FILE_SIZE + size_last;
	return(beg_stack);
}

int	destroy_buff_file_stack(t_buff_file **beg)
{
	t_buff_file	*node;
	t_buff_file	*tmp;

	if (!beg || !*beg)
		return (1);
	node = *beg;
	while (node)
	{
		tmp = node->next;
		if (node)
			free(node);
		node = tmp;
	}
	*beg = NULL;
	return (1);
}

int		copy_stack_in_str(t_buff_file *beg, int nb_buff, int size, char *str)
{
	t_buff_file	*node;
	int			i;
	int			diff;

	if (!beg || nb_buff <= 0 || !str)
		return (0);
	node = beg;
	diff = (nb_buff * BUFF_FILE_SIZE) - size;
	if (diff < 0 || diff > BUFF_FILE_SIZE)
		return (0);
	while (node && nb_buff > 0)
	{
		ft_memmove((str + (nb_buff - 1) * BUFF_FILE_SIZE), node->buff, node->size);
		node = node->next;
		--nb_buff;
	}
	return (1);
}

char	*read_file(const char *name, size_t *str_size)
{
	char	*str_file;
	int		fd;
	int		size;
	int		nb_buff;
	t_buff_file	*beg_stack;

	str_file = NULL;
	if (!str_size || (fd = open_file(name)) < 0)
		return (NULL);
	if (!(beg_stack = stack_buff_file(fd, &size, &nb_buff)))
		return (NULL);
	close(fd);
	if (size <= 0 || !(str_file = (char*)ft_strnew(size)))
		return (NULL);
	if (!copy_stack_in_str(beg_stack, nb_buff, size, str_file))
		return (NULL);
	destroy_buff_file_stack(&beg_stack);
	*str_size = size;
	return (str_file);
}
