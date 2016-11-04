/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_mecanique.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 04:37:12 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/04 18:37:46 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	ici on va gere comment se consrtuit et se deconstruit notre super triangle
//
//

	if (button == 1)
		complet_polygone(w);
	if (button == 2 && !ft_strcmp(w->name, "param"))
	{
		if (mouse_in_border(&(w->e->border_b), w->mouse))
		{
			if ((w->e->base_add++) % 2 == 0)
				polygone_forget_last(&(w->e->base_model));
		}
//		else if ((w->e->base_add % 2) == 0)
//			polygone_push_back(&(w->e->base_model), w->e->actif);

		if (mouse_in_border(&(w->e->border_t), w->mouse))
		{
			if ((w->e->trans_add++) % 2 == 0)
				polygone_forget_last(&(w->e->trans_model));
		}
//		else if ((w->e->trans_add % 2) == 0)
//			polygone_push_back(&(w->e->trans_model), w->e->actif);
		dprintf(1, "base:%d	trans:%d\n", w->e->base_add, w->e->trans_add);
	}

//	BUTTON [1]
//		quand on clique (si on est dans un cadre b/t ) on peu: 
//			-fixer un node entre deux (si l'option espace st activer)
//				(rajouter un node en mode branch)
//			-rajouter a la fin
//	
//	BUTTON [2]
//		quand on clique on peu (si on est dans une fenetre):
//			-changer le mode ajout_fin/ajout_mid(si epace)
//	
//	pour ajouter entre deux il faut savoie quel segment est le plus pret

//	quand on se deplace hors du cadre on peu
//
//	LE NODE MOUSE ==> lvl = void		set_2d_landmark_incpy(double x, double y, t_matrix *dx, t_matrix *dy)
{
void		set_2d_landmark_incpy(t_matrix *diff, t_matrix *dx, t_matrix *dy)
{
	double	dist;

	if (!vect || !dx || !dy)
		return ;
	dist = sqrt(matrix_scalar_product(diff, diff));
	matrix_scalar_product(diff, 1.0 / dist);
	dy->m[0] = dx->m[1];
	dy->m[1] = -dx->m[0];
}

double		set_dist_sepc(double *data, t_matrix *dx, t_matrix *dy, t_polygone *node)
{
	t_matrix	*pos;
	t_matrix	*inter;
	double		dist;

	if (!data || !dx || !dy || !node || !node->next
			|| !(pos = vect_new_vertfd(data[2], data[3], 0))
			|| !(inter = matrix_sub(pos, nde->pos)))
		return ;
	data[0] = matrix_dot_product(dx, inter);
	data[1] = matrix_dot_product(dy, inter);
	if (!matrix_free(&inter) || !(inter = matrix_sub(pos, node->next->pos)))
	data[0] = MIN(data[0], matrix_dot_product(dx, inter));
	data[1] = MIN(data[1], matrix_dot_product(dy, inter));
	matrix_free(&pos);
	matrix_free(&inter);
	dist = sqrt(data[0] * data[0] + data[1] * data[1]);
	return (dist);
}

t_polygone	*get_cluster_seg(t_polygone *begin, double x, double y)
{
	t_matrix	*dx;
	t_matrix	*dy;
	t_polygone	*closer;
	double		data[6];
	t_matrix	*diff;
	
	data[5] = -1;
	data[2] = x;
	data[3] = y;
	closer = NULL;
	if (!begin || !(dx = matrix_init(1, 3)
			|| !(dy = matrix_init(1, 3)))
			|| !(diff = matrix_init(1, 3)))
		return (NULL);
	while (begin->next)
	{
		matrix_subin(node->pos, node->next->pos, diff); 
		set_2d_landmark_incpy(diff, dx, dy);
		data[4] = set_dist_sepc(data, dx, dy, node);
		closer = (data[4] < data[5] || data[5] < 0) ? node: closer;
		data[5] = (data[4] < data[5] || data[5] < 0) ? data[4]: data[5];
		begin = begin->next;
	}
	(42) ? matrix_free(&dx) + matrix_free(dy) + matrix_free(diff) : -42;
	return (closer);
}

//	On pourrait faire une fonction qui defini une base em malloc || copy
