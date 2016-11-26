/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 01:26:10 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/26 18:00:10 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft.h"
#include "fractol.h"

/*
**	void	draw_point_old(t_env *e);
**	void	main_work(t_env *e);
*/

/*
 * Evènement de type "KeyPress":
 *
 * int funct(int keycode, void *param);
 * Evènement de type "KeyRelease":
 *
 * int funct(int keycode, void *param);
 * Evènement de type "ButtonPress" (souris):
 *
 * int funct(int button, int x, int y, void *param);
 * Evènement de type "MotionNotify" (mouvement de la souris):
 *
 * int funct(int x, int y, void *param);
 * Tous les autres évènements:
 *
 * int funct(void *param);
 *
 * */

int		mouse_in(int x, int y)
{
	if (x < 0 || x >= SIZE_X || y < 0 || y >= SIZE_Y)
		return (0);
	return (1);
}

void	set_key(int key_code, t_env *e, const int on, const int off)
{
	(void)key_code;
	(void)e;
	(void)on;
	(void)off;
//	e->echap = (key_code == 53) ? on : off;
}

int	key_press(int key_code, t_env *e)
{
//	set_key(key_code, e, 1, 0);
	(key_code == 53) ? ft_exit(e) : (void)e;
	dprintf(1, "key_press ~~>	code:   %d\n", key_code);
	(key_code == 36) ? ++(e->iter_koch) : (void)e;
	(key_code == 51 && e->iter_koch > 0) ? --(e->iter_koch): (void)e;
//	(key_code == 15) ? /*reset_koch(e)*/: (void)e;
	return (1);
}

int	key_release(int key_code, t_env *e)
{
	(void)e;
	dprintf(1, "key_release ~~>	code:   %d\n", key_code);
	return (1);
}


void	size_window_copy(double pos_low[4], double pos_height[4])
{
	int	i;

	i = 0;
	while (i < 4)
	{
		pos_height[i] = pos_low[i];
		i++;
	}
}

void	play_mandel(int x, int y, t_env *e)
{
	e->zoom_finished = 0;
	e->zoom_on = 1;
	e->zoom_x = x;
	e->zoom_y = y;
}

int mouse_motion(int x, int y, t_env *e)
{
	char	*position;

	position = (mouse_in(x, y) ? "in " : "out");
	move_last(x - SIZE_X * 0.5, y - SIZE_Y * 0.5, e);
	if (!(e->mouse))
		e->mouse = matrix_init(1, 3);
	if (e->mouse)
	{
		if (!(e->prev_mouse))
			e->prev_mouse = matrix_copy(e->mouse);
		if (e->prev_mouse)
		{
			e->prev_mouse->m[0] = e->mouse->m[0];
			e->prev_mouse->m[1] = e->mouse->m[1];
		}
		e->mouse->m[0] = x;
		e->mouse->m[1] = y;
		if (e->mouse && e->prev_mouse && e->left)
			translate_node(e, e->trans_model);
	}
	dprintf(1, "mouse motion 	(%s)-->		x:%d	y:%d\n", position, x, y);
	return (1);
}


int mouse_press(int button, int x, int y, t_env *e)
{
	char	*position;

	position = (mouse_in(x, y) ? "in " : "out");
	dprintf(1, "mousse press	(%s)--> button:%d	x:%d	y:%d\n", position, button, x, y);
	if (mouse_in(x, y) && e->zoom_finished)
	{
	//	play_mandel(x, y, e);
		if (button == 1 &&  (e->draw_base || e->draw_transform))
		{
			ft_putstr("BASE || PLYGONE\n");
			increm_polygone(x - SIZE_X * 0.5, y - SIZE_Y * 0.5, e);
		}
		else if (button == 2)
		{
			if (e->draw_base)
				end_base(e);
			else if (e->draw_transform)
				end_transform(e);
		}
		else if (button == 1)
			e->left = 1;
		else if (button == 2)
			e->right = 1;
	}
	return (1);
}

int mouse_release(int button, int x, int y, t_env *e)
{
	char	*position;

	position = (mouse_in(x, y) ? "in " : "out");
	dprintf(1, "mousse release  (%s) ==>button:%d	x:%d	y:%d\n", position, button, x, y);
	(void)e;	
	if (button == 1)
		e->left = 0;
	else if (button == 2)
		e->right = 0;
	return (1);
}

int mouse_other(int x, int y, t_env *e)
{
	(void)e;
	dprintf(1, "other-->		x:%d	y:%d\n", x, y);
	return (1);
}

void		init_pos_ecr(t_env *e)
{
	e->pos_low[0] = -2;
	e->pos_low[1] = -2;
	e->pos_low[2] = 2;
	e->pos_low[3] = 2;
	e->pos_height[0] = -2;
	e->pos_height[1] = -2;
	e->pos_height[2] = 2;
	e->pos_height[3] = 2;
}

void		print_map(double **img, int size_x, int size_y)
{
	int	i;
	int	j;

	j = 0;
	dprintf(1, "size_x:%d, size_y:%d\n", size_x, size_y);
	while (j < size_y)
	{
		i = 0;
		while (i < size_x)
		{
			printf("%.1f ", img[j][i]);
			i++;
		}
		j++;
		printf("\n");
	}
	printf("\n");
	printf("\n");
}

int			main_work()
{
	static	t_env	*e = NULL;
	t_polygone		*to_color;

	if (!(e = get_env(NULL)))
		return (0);
	to_color = NULL;
	draw_the_2_border(e);
	draw_simple_polygone(e->param, e->trans_model);
	draw_simple_polygone(e->param, e->base_model);
	if (mouse_in_border(&(e->border_b), e->param->mouse) && e->base_add > 0)
		to_color = get_closer_node(e->base_model, e->param->mouse, e->r_select);
	if (mouse_in_border(&(e->border_t), e->param->mouse) && e->trans_add > 0)
		to_color = get_closer_node(e->trans_model, e->param->mouse, e->r_select);
	if (to_color)
		print_circle2(to_color->pos, NULL, e->r_select, e->param);
	if (e->id_scrol >= 0)
		scroling_button(e->param, e->sliders[e->id_scrol / 2], e->id_scrol % 2);
	draw_the_sliders(e->param, e->sliders);
	(e->add_point && e->base_add && e->trans_add) ? draw_prewiew(e->param) : (void)e;
	actu_win_rest(e->param);
	return (1);
}


/*
**	
**	
**	
**	
*/
