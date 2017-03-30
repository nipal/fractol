# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjanoty <fjanoty@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2017/03/30 22:20:33 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re

#-fsanitize=address -g3
NAME	=	../fractol
NAME_SAVE = ../fractol_save
DEPS = ../includes/fractol.h

SRC		= 	main.c						\
			draw_line.c					\
			koch_generalise.c 			\
			segment_manipule_basic.c 	\
			calcul_madelbrot.c 			\
			mlx_env.c 			 		\
			print_somthing.c 			\
			hook.c 					 	\
			polygone_new.c 			 	\
			polygone_destroy.c 			\
			polygone_transfrom.c 		\
			creat_insert_polygone.c		\
			polygone_maj.c 			 	\
			polygone_adapte.c			\
			polygone_describe.c			\
			modify_model.c 				\
			color_transpose.c 			\
			new_printing.c 			 	\
			init_win.c 					\
			new_hook.c 					\
			hook_button_koch.c 			\
			param_koch.c 				\
			border.c 					\
			base_ifs.c 					\
			segment_mecanique.c 		\
			polygone_manip_node.c 		\
			printing_koch_final.c 		\
			init_printing_koch.c 		\
			sliding_button.c 			\
			manage_sliding_button.c		\
			drawing_button.c 			\
			zoom_koch.c 				\
			actu_polygone.c 			\
			init_param_koch.c 			\
			test.c						\
			ovaloide.c					\
			print_rectangle.c			\
			user_interface.c			\
			ellipsoide.c				\
			serveur.c					\
			client.c					\
			exit.c 


OBJ		= $(SRC:.c=.o)

# CFLAGS =  -Wall -Wextra -Werror

#FLAGS-DEBUG = -g3 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS)  -o $(NAME) $(OBJ) -L ../libft/ -lft \
		-L ../c_maths -lc_maths \
		-L  minilibx_macos/ \
		-lmlx -framework OpenGL -framework AppKit  

#		-L /usr/lib/ -lmlx -lm -lX11 -lXext



%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $< -I ../includes -I ../c_maths

	# -I /usr/includes/

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

gdb: fclean
		$(CC) -c $(FLAGS-DEBUG) $(SRC) -I ../includes -I ../c_maths
		$(CC) -o $(NAME) $(FLAGS-DEBUG) $(OBJ) -L ../libft/ -lft \
		-L ../c_maths -lc_maths \
		-L /usr/lib/ -lmlx -lm -lX11 -lXext

#		-L /usr/lib/ -lmlx -lm -lX11 -lXext
#		 cp -f $(NAME) $(NAME_SAVE) 


