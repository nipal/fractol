# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2017/06/15 22:48:39 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re

#-fsanitize=address -g3
NAME	=	../fractol
NAME_SAVE = ../fractol_save
DEPS = ../includes/fractol.h

SRC		= 	main.c						\
			draw_line.c					\
			segment_manipule_basic.c 	\
			koch_generalise.c 			\
			mlx_env.c 			 		\
			hook.c 					 	\
			polygone_new.c 			 	\
			polygone_destroy.c 			\
			polygone_transfrom.c 		\
			creat_insert_polygone.c		\
			polygone_maj.c 			 	\
			polygone_adapte.c			\
			polygone_describe.c			\
			segment_mecanique.c 		\
			polygone_manip_node.c 		\
			modify_model.c 				\
			color_transpose.c 			\
			new_printing.c 			 	\
			init_win.c 					\
			new_hook.c 					\
			hook_button_koch.c 			\
			param_koch.c 				\
			border.c 					\
			base_ifs.c 					\
			sliding_button.c 			\
			manage_sliding_button.c		\
			drawing_button.c 			\
			zoom_koch.c 				\
			actu_polygone.c 			\
			init_param_koch.c 			\
			print_rectangle.c			\
			user_interface.c			\
			ellipsoide.c				\
			animation.c					\
			init_printing_koch.c 		\
			printing_koch_final.c 		\
			ocl_init.c					\
			ocl_init_ifs.c				\
			ocl_calcul_ifs_point.c		\
			ocl_define_colore.c			\
			ocl_draw_line.c				\
			read_file.c					\
			error_opencl.c				\
			exit.c						\


OBJ			= $(SRC:.c=.o)
LIB_DIR		= -L ../libft -L ../c_maths -L ../vec_math -L ../minilibx_macos
#		-L /usr/lib/ -lmlx -lm -lX11 -lXext

LIB_NAME	= -lft -lc_maths -lvec_math -lmlx

FRAMEWORK	= -framework OpenGl -framework AppKit -framework opencl

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS)  -o $(NAME) $(OBJ) $(LIB_DIR) $(LIB_NAME) $(FRAMEWORK)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $< -I ../includes -I ../c_maths  


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
