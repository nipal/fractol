## truc a faire avant d aller dormir

	(15) -> (15)		- debuguer le .cl
	(10) -> (20)		- teser un kernel avec des structure
	
[c]	(10) -> (30)		- retrouver/redefinir "UNE" fasson de formuler les objet !!+la strucuture du buffer!!
	 (45) ->(11h20)		- re structure la memoir et les kernel pour fonctionner avec des buffer structure:
								(obj) + (buffer)
			(10) -> () 	-En gros la il faut voir ou est ce que la memoir est allouer	(CPU + GPU)
			(10) -> () 	- malloc: cote CPU et cote GPU
			(10) -> () 	- ecrire un kernel qui ressoit le buffer
			(10) -> () 	- verifier que le pading fontionne

	(15) -> ()		- (CPU) travailler le preprossessing a faire sur les obj+cam => (changement de reper sur les rayon)
	(10) -> ()		- eventuellement rajouter les deplacement en translation avec les toucheles deplacement en translation avec les touchess
	(15) -> ()		- voir si on precalcul tout (les chanegement de repere pour chaque objet)
	(10) -> ()		- kernel de mise a jour du {z_buffer,id_obj} (maj de l objet le plus proche)
	(15) -> ()		- lors de la resolution d intersection avec le cylindre et le conne on stoque aussi le resulta dans la changement de repere (calculer facielment la normal)
	(20) -> ()		- definir les calcul de (distance (cam, obj), vecteur (cam, obj) [&&]  distance (obj, lum) , vecteur (obj, lum) [&&] couleur obj, couleur lum)
	(20) -> ()		- calcul de lumiere (globale, difuse etc)
	(25) -> ()		- regarder a quoi correspond le truc de lumiere phong
	(15) -> ()		- additioner plusieur limiere entre elle
	(30) -> ()		- definir des multi spot
	(30) -> () 		- faire un genre de "makfile/concateneur" de .cl

300 minute
	- youpi trop bien


		================== 
		La je devrai avoir fait une bonne partie du taf.


*****************	tactique d'approche'	***************** 

	
[c]
	(10) -> (10) 	-En gros la il faut voir ou est ce que la memoir est allouer	
	(10) -> (5) 	- malloc: cote CPU et cote GPU
		GPU ok		CPU pas besoin (buffer statique)
	(10) -> () 	- ecrire un kernel qui ressoit le buffer
	(5) ->	()	- linker  les argument au kernel
	(5) ->	()	- ecrire sur le buffer
			la l'enjeu c'est de bien comprendre la taille qu;il faut
	(5) ->	()	- lire sur le buffer
	(10) -> () 	- verifier que le pading fontionne


//	la on est daccor que c'est un kernerl de test pour tester les structure et le pading
//	il se peu que en suite je m'inspire de cette structure pour fairles kernel qui
//	mette a jour la distance et tout ce qu'il faut pour


****->	les kernel:
	On va faire calculer les objet un par un ? liste d'objet par liste d'objet?

	En gros il faur le moins d'echange possible de la memoir donc que un truc d'ecriture au debut et un truc de lecture a la fin
	- On doit apporter en parametre: Tout les objet, la liste d'index de la forme, (la forme est deerminer par )
		--> tab_obj, tab_index, vecteur directeur


alors alors... limite il faudrait que je reprenne tout de zero. Main le truc qyui me chagrine un brin
c'est que je voulais faire ca pour rt


MAIS SINON. En gros il faudrait re pensser un systeme complet qui automatise tout
qui separe bien chque etape d'initialisation en etape differente. Bon la j'aurrai un peu envis de m'ecouter et de 
rentrer meintenant mais non. je reste encore iune heure et je fais le maximum. pck c'etait bien partie
