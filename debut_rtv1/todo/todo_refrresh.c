

"En fait le .c c'est juste pour se demander comment est ce qu'on pourrai initialiser les kernel opencl de manier automatiser"

Du coup soit on fait des fonction en dure, soit on stoaue ca dans un fichier de configuration.
Ou en tout cas dans un structure qui represente les different alication possible.

Si on automatise un peu les truc il faudrait avoir une forme de gestion de la memoir. Et ca c'est particulierement chiant, genre pas tout de suite.
Une autre solution serrai d'avoir un langage de scripte qui puisse faire une genre d'interface adaptable. En fait compiler a la voler c'est un paradigme 
de programation haut niveau. du coup pour le manipuler aussi souplement qu ' on le voudrai reviendrai a emuler certain mecanisme d'un os.



Bon dans les 20 provchaine tu va faire quoi avant d'aller en pose






La j 'aimerai bien un peu mieux me poser la question COMMENT AUTOMATISER LE FIT LE FAIT DE SET DES ARGUMENT

-Est ce que ca serra un truc facilement reutilisable.
-Est ce qur ca serra un truc chiant a faire?

Ah mon avis le mieu c'est de parir sur un petit truc a base de liste chainer.
En gros il faut quelaue part stauer de l'information en dure.

Pout les nom de kernel il faudrait que je fasse des petites fonction de getteur et d'accesseur.
genre un truc un peu dans l'esprit d'une table de hashe: {clef, valeur}  OU {cahr *str, int id}

On pourrai un peu voir ca comme une api. C'est a dire que on a des fonction qui font le taf de l'initialiation
Et des fonction qui les utilise


la liste chainer assossier serrai genre:


#define SET_KERNEL_ARG_AUTO
(il faudrait aussi init les liste d'initialisation)

	liste: Pour chaque kernel:
		nb_arg
		liste: Pour chaque argument
			(addr, size) 


#define SET_KERNEL_ARG_MANO
bha genre un truc a la mano comme je l'ai deja fait

Si on on peu voir les chose comme ca: /* IL manque quoi pour que l'algo soit fonctionel */
	
	- Il faudrait voir si il y a beacoup a ajouter pour tout refare depuis le debut	

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	On va deja regqrder comment on initialise le debut:
		- soit on peu recupere ce qu'il se passe et updtate pour que ca marche
		- tout re coder (mais de toute fasson ca ne serra pas un grosse partie)

	- avoir une interface ineressante en evenemtn pour binder le tout
	
	- Au lieu de faire un truc un peu compiquer a initialiser avec des liste chainer
		on pourrai peu etre faire ca avec des tableau ... ou pas


	- Bon il faudrait quand meme tout remanier les fonction pour regrouper ce aui est logique d'etre regrouper
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef	struct	s_arg_info
{
	int			id;
	size_t		size;
	cl_mem		adrr;
	t_arg_info	*next;
}				t_arg_info;

typedef	struct	s_ker_args
{
	int			nb_arg;
	t_arg_info	*firts_arg;
	t_ker_args	*next;	
}				t_ker_args;



+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	Il  faudrait reflechir aussi a une 
	- separation inteligente des .h
	- integrer la lecture de fichier dans la libft (probablement pout tout ce qui serra parcing)
	- reflechir a toute la partie opencl (initialisation etc)
