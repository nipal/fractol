# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2018/01/09 03:59:11 by fjanoty          ###   ########.fr        #
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
			ovaloide.c					\
			print_rectangle.c			\
			user_interface.c			\
			ellipsoide.c				\
			serveur.c					\
			client.c					\
			exit.c						\
			animation.c					\
			draw_ifs_iteratif.c			\
			ocl_init.c					\
			ocl_init_ifs.c				\
			ocl_calcul_ifs_point.c		\
			ocl_define_colore.c			\
			ocl_draw_line.c				\
			read_file.c					\
			error_opencl.c				\
			client_data.c


OBJ			= $(SRC:.c=.o)

SPACE		=
SPACE		+= 

PRELIB		= -I $(SPACE)

LIB_DIR		= -L ../libft -L ../c_maths -L ../vec_math -L ../minilibx_macos

LIB_NAME	= -lft -lc_maths  -lmlx

FRAMEWORK	= -framework OpenGl -framework AppKit -framework opencl



# CFLAGS =  -Wall -Wextra -Werror

#FLAGS-DEBUG = -g3 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS)  -o $(NAME) $(OBJ) $(LIB_DIR) $(LIB_NAME) $(FRAMEWORK)

#		-L /usr/lib/ -lmlx -lm -lX11 -lXext



%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $< -I ../includes -I ../c_maths  


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
