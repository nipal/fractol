/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_to_add.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 17:41:17 by fjanoty           #+#    #+#             */
/*   Updated: 2017/03/28 01:08:51 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	La on va mettre tout les prototype qu'on a rnvie d'avoir et toute les structure.
**	Comme ca on va pourovi rabattre tout plein de code
*/



void	paint_rectangle(t_win *w, t_matrix *col, t_border *rec);
void	draw_rectangle(t_win *w, t_matrix *col, t_border *rec);

/*
**		C'est une fonciton qui va me tracer des courbe de bezier sur un t_polygone
**		et ca va aussi gerer les different lvl
**
**	INPUT::
**	w		->	la denetre ou on dessine
**	deg		->	le degrer de courbe de bezier que l'on veux (degre 1 grosomodo on suit les ligne)
**	ctrl_pt	->	les point de controle de la courbe de bezier
**	nbp		->	le nombre de point entre lesquel on va tracer de ligne droite
**					engros c;est une peu la precision mais ca aurra un lien avec
**					la maniere de parcourire une anime...
*/

void		print_bezier_curve(t_win *w, t_polygone *ctrl_pt, int deg, int nbp);
t_matrix	*get_bezier_pt_at(t_polygone *ctrl_pt, int deg, float at);
double		**init_binomial_coef(int max_deg);

/*
//	est-ce qu'on travialle avec des vecteur pour reutiliser les truc danmark?? hum on va juste eiseiller frome scratch si non trop de fonction
typedef	struct	s_ellipsoide
{
	double	cx;	//centre
	double	cy;	//centre
	double	ux;	
	double	uy;
	double	vx;
	double	vy;
}				t_ellipsoide;
*/


/*
**	Il faut les donner de parametrage de l'allipsoide
**	on va juste considerer les 3 premier pt::
**	
**	y1 est toutjours a 90 deg horaire de x1
**	la modification de la nomre de x1 affecte proportionelement la norme de y1
**	Mais y1 n'affect QUE l'orientation de x1 pck si non on ne peu jamais bouger les truc de machin
**	bouger le centre ne fait que tout translater

**	il faudra pensser a ou est-ce qu'on place l'offset
*/
void		draw_ellipsoide_(t_win *w, t_polygone *pt);

/*
 * Il faudrait savoir quel point a changer
*/

void		ellipsoid_modify_centre(t_polygone *pt, t_polygone *new_pnode);
void		ellipsoid_modify_ux(t_polygone *pt, t_polygone *new_pnode);
void		ellipsoid_modify_uy(t_polygone *pt, t_polygone *new_pnode);

//	L'offset on le met ou. L'ider c'est d'avoir un truc qui fait que oui a partir de bezier
float		adapt_time(double input_time, t_polygone *ctrl_pt, int deg);

//	Il faut aussi gerer les fonction d'evenement



//		USER_INTERFACE

/*
 *	La c'est pour les truc de user interface
 *
 * 	- On dessine auttan de rectangle (anime_box) que de de point du t_polygone (donc aussi le premier et le dernier)
 * */

# define ELLIPSOID 1
# define 

typedef	struct	s_anime
{
	int		anime_nb;	//	c'est le numerot du type d'anime
}				t_anime;



void	print_anime_box(t_win *w, t_polygone *poly, t_anime *anime, t_border *b);


//	la on va genre initialiser des truc
t_anime	*creat_anime_box(t_polygone *init_poly);

//	on va se debrouyer pour destroy avec un free...
void	destroy_anime_box(t_anim **anime_box);
void	add_anime_box(t_anime **anime_box, t_polygone *new_node, int pos);


