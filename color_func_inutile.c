/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_func_inutile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 18:04:15 by fjanoty           #+#    #+#             */
/*   Updated: 2016/11/19 00:05:47 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_matrix	*rgb_to_tsl_new(double r, double g, double b);
void		rgb_to_tsl_mod(t_matrix *color);

t_matrix	*rgb_to_tsl_new(double r, double g, double b)
{
	double		max;
	double		min;
	double		croma;
	t_matrix	*tsl;

	r /= 255.0;
	g /= 255.0;
	b /= 255.0;
	if (!(tsl = matrix_init(1, 3)))
		return (NULL);
	max = MAX(r, g);
	max = MAX(max, b);
	min = MIN(r, g);
	min = MIN(min, b);
	croma = max - min;
	if ((!croma && !(tsl->m[0] = 0))
		|| (max == r && ((tsl->m[0] = 60 * modulo((((g - b) / croma) + 6.0),  6.0)) > -1))
		|| ((max == g) && ((tsl->m[0] = 60 * (((b - r) / croma) + 2.0) > -1)))
		|| ((tsl->m[0] = 60 * (((r - g) / croma) + 4.0)) > -1 ))
	tsl->m[2] = max;
	tsl->m[1] = (max == 0) ? 0 : croma / max;
	return (tsl);
}

void		rgb_to_tsl_mod(t_matrix *rgb)
{
	double		max;
	double		min;
	double		croma;
	t_matrix	*tsl;

	rgb->m[0] /= 255.0;
	rgb->m[1] /= 255.0;
	rgb->m[2] /= 255.0;
	if (!(tsl = matrix_init(1, 3)))
		return ;
	max = MAX(rgb->m[0], rgb->m[1]);
	max = MAX(max, rgb->m[2]);
	min = MIN(rgb->m[0], rgb->m[1]);
	min = MIN(min, rgb->m[2]);
	croma = max - min;
	if ((!croma && !(tsl->m[0] = 0))
		|| (max == rgb->m[0] && ((tsl->m[0] = 60 * (modulo((((rgb->m[1] - rgb->m[2]) / croma) + 6.0),  6.0))) > -1))
		|| ((max == rgb->m[1]) && ((tsl->m[0] = 60 * (((rgb->m[2] - rgb->m[0]) / croma) + 2.0) > -1)))
		|| ((tsl->m[0] = 60 * (((rgb->m[0] - rgb->m[1]) / croma) + 4.0)) > -1 ))
	tsl->m[2] = max;
	tsl->m[1] = (max == 0) ? 0 : croma / max;
	rgb->m[0] = tsl->m[0];
	rgb->m[1] = tsl->m[1];
	rgb->m[2] = tsl->m[2];
}
